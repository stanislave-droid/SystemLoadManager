#include <iostream>
#include <Windows.h>
#include "Memory_M.h"
#include "CPU_M.h"
#include "Disk_M.h"
#include <thread>
#include "tabulate.hpp"

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
	auto disksInfo = disk_m.disksInfo;

	using namespace tabulate; {
		Table table;
		table.format().multi_byte_characters(true);
		table.add_row({"Disk name", "Free space", "Used space", "Total space"});

		for (const auto& diskInfo : disksInfo) {
			table.add_row({
				diskInfo->disk_name,
				std::to_string(diskInfo->total_free) + " " + diskInfo->disk_measurement,
				std::to_string(diskInfo->total_used) + " " + diskInfo->disk_measurement,
				std::to_string(diskInfo->total_size) + " " + diskInfo->disk_measurement,
			});

			table[table.size() - 1][1].format().font_background_color(Color::green);
			table[table.size() - 1][2].format().font_background_color(Color::red);
			table[table.size() - 1][3].format().font_background_color(Color::blue);
		}
		cout << table << endl;
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