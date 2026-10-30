#include "CPU_M.h"

void CPU_M::FileTimeToInt64(const FILETIME& ft, __int64& int64)
{
	std::memcpy(&int64, &ft, sizeof(FILETIME));
}

CPU_M::CPU_M()
{
	this->cpuLoad = std::make_shared<CPULoad>();
	auto cpuLoad = this->cpuLoad;

	cpuLoad->availableThreads = std::thread::hardware_concurrency();
	GetCPUCoresCount();
	GetCPUBaseSpeed();
}

void CPU_M::GetMeasurements(Measurement& measurement)
{
	FILETIME idleTime, kernelTime, userTime;

	if (!GetSystemTimes(&idleTime, &kernelTime, &userTime)) {
		measurement.idleTime = 0;
		measurement.kernelTime = 0;
		measurement.userTime = 0;
		return;
	}

	FileTimeToInt64(idleTime, measurement.idleTime);
	FileTimeToInt64(kernelTime, measurement.kernelTime);
	FileTimeToInt64(userTime, measurement.userTime);
}

void CPU_M::CalculateCPULoad()
{
	auto cpuLoad = this->cpuLoad;
	auto firstMeasurement = &this->firstMeasurement;
	auto secondMeasurement = &this->secondMeasurement;

	__int64 idleTimeDiff = secondMeasurement->idleTime - firstMeasurement->idleTime;
	__int64 kernelTimeDiff = secondMeasurement->kernelTime - firstMeasurement->kernelTime;
	__int64 userTimeDiff = secondMeasurement->userTime - firstMeasurement->userTime;

	__int64 totalTimeDiff = kernelTimeDiff + userTimeDiff;

	cpuLoad->cpu_load = (totalTimeDiff - idleTimeDiff) * 100.0 / idleTimeDiff;
	RoundToDecimal(cpuLoad->cpu_load, 1);
}

void CPU_M::RoundToDecimal(double& value, int decimals)
{
	double factor = std::pow(10.0, decimals);
	value = std::round(value * factor) / factor;
}

void CPU_M::GetCPUCoresCount()
{
	DWORD bufferSize = 0;
	auto cpuLoad = this->cpuLoad;

	GetLogicalProcessorInformation(nullptr, &bufferSize);

	std::vector<SYSTEM_LOGICAL_PROCESSOR_INFORMATION> buffer(bufferSize / sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION));

	if (!GetLogicalProcessorInformation(buffer.data(), &bufferSize)) {
		cpuLoad->cpu_cores = 1;
		return;
	}

	for (const auto& info : buffer) {
		if (info.Relationship == RelationProcessorCore) {
			cpuLoad->cpu_cores++;
		}
	}
}

void CPU_M::GetCPUBaseSpeed()
{
	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);
	LARGE_INTEGER firstCounter, secondCounter;
	__int64 fTicks = 0;
	__int64 sTicks = 0;
	auto cpuLoad = this->cpuLoad;

	QueryPerformanceCounter(&firstCounter);
	fTicks = __rdtsc();

	Sleep(100);

	QueryPerformanceCounter(&secondCounter);
	sTicks = __rdtsc();

	auto elapsedTime = (double)(secondCounter.QuadPart - firstCounter.QuadPart) / frequency.QuadPart;
	auto ticksDiff = sTicks - fTicks;
	cpuLoad->cpu_base_speed = ticksDiff / elapsedTime / 1000000000.0;
	RoundToDecimal(cpuLoad->cpu_base_speed, 1);
}

void CPU_M::RunFirstMeasurements()
{
	auto firstMeasurement = &this->firstMeasurement;
	GetMeasurements(*firstMeasurement);
}

void CPU_M::RunSecondMeasurements()
{
	auto secondMeasurement = &this->secondMeasurement;
	GetMeasurements(*secondMeasurement);
	CalculateCPULoad();
}