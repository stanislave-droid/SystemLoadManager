#include "Memory_M.h"



Memory_M::Memory_M()
{
	this->memoryLoad = std::make_shared<MemoryLoad>();
	auto memoryLoad = this->memoryLoad;
	auto memStatusEx = &this->memStatusEx;

	memStatusEx->dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(memStatusEx)) {
		memoryLoad->memory_total = memStatusEx->ullTotalPhys / (1024 * 1024);
	}
}

void Memory_M::GetMemoryLoad()
{
	auto memoryLoad = this->memoryLoad;
	auto memStatusEx = &this->memStatusEx;

	if (GlobalMemoryStatusEx(memStatusEx)) {
		memoryLoad->memory_load = memStatusEx->dwMemoryLoad;
	}
	else {
		memoryLoad->memory_load = 0;
	}
}

void Memory_M::GetAvailableMemory()
{
	auto memoryLoad = this->memoryLoad;
	auto memStatusEx = &this->memStatusEx;

	if (GlobalMemoryStatusEx(memStatusEx)) {
		memoryLoad->memory_free = memStatusEx->ullAvailPhys / (1024 * 1024);
		return;
	}

	memoryLoad->memory_free = 0;
}

void Memory_M::RunMemoryMeasurements()
{
	GetAvailableMemory();
	GetMemoryLoad();
}