#include <iostream>
#include <Windows.h>
#include "Memory_M.h"
#include "CPU_M.h"
#include "Disk_M.h"
#include <thread>

using namespace std;

int main() {
	std::cout << "Hello world" << std::endl;

	/* CPU monitor */

	CPU_M cpu_m;
	auto cpuLoad = cpu_m.cpuLoad;
	cout << "Physical processors: " << cpuLoad->cpu_cores << endl;
	cout << "Available Threads: " << cpuLoad->availableThreads << endl;
	cout << "CPU base speed: " << cpuLoad->cpu_base_speed << "Ghz" << endl;

	/* Memory monitor*/

	Memory_M memory_m;
	auto memoryLoad = memory_m.memoryLoad;

	/* Disk monitor */

	Disk_M disk_m;
	for(const auto& diskInfo : disk_m.disksInfo) {
		wcout << "Disk name: " << diskInfo->disk_name << endl;
		cout << "Total size: " << diskInfo->total_size << diskInfo->disk_measurement << endl;
		cout << "Total free: " << diskInfo->total_free << diskInfo->disk_measurement << endl;
		cout << "Total used: " << diskInfo->total_used << diskInfo->disk_measurement << endl;
	}

	while (true) {
		/* Static measurements */
		memory_m.RunMemoryMeasurements();

		/* Pre-measurements */
		cpu_m.RunFirstMeasurements();

		Sleep(100);

		/* Final measurements */
		cpu_m.RunSecondMeasurements();

		/* Console out */

		cout << memoryLoad->memory_total << " " << memoryLoad->memory_measurement << " "
			<< "(" << memoryLoad->memory_free << "/" <<
			memoryLoad->memory_total <<
			")" << memoryLoad->memory_measurement << " "
			<< memoryLoad->memory_load << "%" << endl;
		cout << "CPU load: " << cpuLoad->cpu_load << "%" << endl;
	}
}