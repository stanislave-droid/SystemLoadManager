#pragma once
#include <windows.h>
#include <thread>
#include <cstring>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

class CPU_M
{
public:
	struct CPULoad {
		double cpu_load = 0.0;
		double cpu_base_speed = 0.0;
		unsigned int cpu_cores = 0;
		unsigned int availableThreads = 1;
	};

	struct Measurement {
		__int64 idleTime = 0;
		__int64 kernelTime = 0;
		__int64 userTime = 0;
	};
private:
	void FileTimeToInt64(const FILETIME& ft, __int64& int64);
	void GetMeasurements(Measurement& measurement);
	void CalculateCPULoad();
	void RoundToDecimal(double& value, int decimals);
	void GetCPUCoresCount();
	void GetCPUBaseSpeed();
	Measurement firstMeasurement;
	Measurement secondMeasurement;
public:

	std::shared_ptr<CPULoad> cpuLoad;
	CPU_M();
	static std::string DoubleToString(double value, int precision = 1);
	void RunFirstMeasurements();
	void RunSecondMeasurements();
	
};