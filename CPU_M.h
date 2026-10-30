#pragma once
#include <windows.h>
#include <thread>

class CPU_M
{
	unsigned int availableThreads;

public:
	CPU_M();
	unsigned int GetAvailableCPUThreads();
	double GetCPUUsage();
	
};