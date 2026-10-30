#pragma once
#include <string>
#include "Memory_M.h"
#include <Windows.h>
#include <memory>

class Memory_M
{
public:
	struct MemoryLoad {
		int memory_load = 0;
		int memory_free = 0;
		int memory_total = 0;
		char memory_measurement[2] = { 'M','b' };
	};
	MEMORYSTATUSEX memStatusEx;
	std::shared_ptr<MemoryLoad> memoryLoad;
private:
	void GetMemoryLoad();
	void GetAvailableMemory();
public:
	Memory_M();
	void RunMemoryMeasurements();
};

