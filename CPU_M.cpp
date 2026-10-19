#include "CPU_M.h"

CPU_M::CPU_M()
{
	availableThreads = std::thread::hardware_concurrency();
}

unsigned int CPU_M::GetAvailableCPUThreads()
{
	return availableThreads;
}

double CPU_M::GetCPUUsage()
{


	return 0.0;
}
