#pragma once
#include <string>
#include "Memory_M.h"
#include <Windows.h>

class Memory_M
{
public:
	struct MemoryLoad {
		int memory_load = 0;
		int memory_free = 0;
		int memory_total = 0;
		char memory_measurement[2] = { 'M','b' };
	};

private:
	MemoryLoad memoryLoad;
	static int GetMemoryLoad();
	static int GetAvailableMemory();
public:
	Memory_M();
	static void RunMemoryMeasurements(int delay, MemoryLoad &memoryLoad);
	MemoryLoad GetMeasurements();
};

