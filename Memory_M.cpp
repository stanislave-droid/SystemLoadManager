#include "Memory_M.h"

MEMORYSTATUSEX memStatusEx;

Memory_M::Memory_M()
{
	memStatusEx.dwLength = sizeof(MEMORYSTATUSEX);
	if (GlobalMemoryStatusEx(&memStatusEx)) {
		this->memoryLoad.memory_total = memStatusEx.ullTotalPhys / (1024 * 1024);
	}
}

int Memory_M::GetMemoryLoad()
{
	if (GlobalMemoryStatusEx(&memStatusEx)) {
		return memStatusEx.dwMemoryLoad;
	}
	else {
		return 0;
	}
}

int Memory_M::GetAvailableMemory()
{
	if (GlobalMemoryStatusEx(&memStatusEx)) {
		return memStatusEx.ullAvailPhys / (1024 * 1024);
	}

	return 0;
}

void Memory_M::RunMemoryMeasurements(int delay, MemoryLoad &memoryLoad )
{
	while (true) {
		memoryLoad.memory_free = Memory_M::GetAvailableMemory();
		memoryLoad.memory_load = Memory_M::GetMemoryLoad();
		Sleep(delay);
	}
}

Memory_M::MemoryLoad Memory_M::GetMeasurements()
{
	return memoryLoad;
}
