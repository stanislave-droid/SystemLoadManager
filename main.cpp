#include <iostream>
#include <Windows.h>
#include "Memory_M.h"
#include "CPU_M.h"
#include <thread>

using namespace std;

int main() {
	std::cout << "Hello world" << std::endl;

	/* CPU monitor */

	CPU_M cpu_m;
	cout << "Physical processors: " << cpu_m.GetAvailableCPUThreads() << endl;

	/* Memory monitor*/

	Memory_M memory_m;
	Memory_M::MemoryLoad memoryLoad = memory_m.GetMeasurements();
	thread thread(Memory_M::RunMemoryMeasurements, 100, ref(memoryLoad));

	/* Console out */

	while (true) {
		cout << memoryLoad.memory_total << " " << memoryLoad.memory_measurement << " "
		<< "(" << memoryLoad.memory_free << "/" << 
			      memoryLoad.memory_total << 
			")" << memoryLoad.memory_measurement << " "
		<< memoryLoad.memory_load << "%" << endl;
		Sleep(100);
	}
}