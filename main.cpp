#include <iostream>
#include <Windows.h>
#include "Memory_M.h"
#include "CPU_M.h"
#include "Disk_M.h"
#include <thread>
#include "tabulate.hpp"

using namespace std;
using namespace tabulate;

void SetCursorPosition(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = { static_cast<SHORT>(x), static_cast<SHORT>(y) };
	SetConsoleCursorPosition(hConsole, pos);
}

void ShowConsoleCursor(bool state) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = state;
	SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void GetColorOnLoad(Color& color, double value) {
	if (value > 70) color = Color::red;
	else if (value < 70 && value > 30) color = Color::yellow;
	else color = Color::green;
}

int main() {
	std::cout << "Hello world" << std::endl;
	cout << "My name is Drochak Stanislav." << endl;
	cout << "It`s my coursework for Software Engineering." << endl;
	cout << "It`s a System Resource Monitor; it shows some properties of your system and some of them in real time," << endl;
	cout << "such as CPU and memory load with a nice and colorful interface." << endl;
	cout << "It`s a console application, but it has a great interface with colorful cells for more information." << endl;
	cout << "To continue, press any key: ";
	cin.get();
	system("cls");

	#pragma region CPU monitor
	/* CPU monitor */

	CPU_M cpu_m;
	auto cpuLoad = cpu_m.cpuLoad;
	Table cpuTable;
	
	cpuTable.add_row({ "CPU load", "CPU Cores", "Available Threads", "CPU Base Speed" });
	cpuTable.add_row({
		CPU_M::DoubleToString(cpuLoad->cpu_load) + "%",
		std::to_string(cpuLoad->cpu_cores),
		std::to_string(cpuLoad->availableThreads),
		CPU_M::DoubleToString(cpuLoad->cpu_base_speed) + "Ghz"
		});
	#pragma endregion

	#pragma region Memory monitor
	/* Memory monitor*/

	Memory_M memory_m;
	auto memoryLoad = memory_m.memoryLoad;
	Table memoryTable;

	memoryTable.add_row({ "Memory load", "Free memory", "Total memory" });
	memoryTable.add_row({
		std::to_string(memoryLoad->memory_load) + "%",
		std::to_string(memoryLoad->memory_free) + memoryLoad->memory_measurement,
		std::to_string(memoryLoad->memory_total) + memoryLoad->memory_measurement,
		});
	#pragma endregion 

	#pragma region Disk monitor
	/* Disk monitor */
	Disk_M disk_m;
	auto disksInfo = disk_m.disksInfo;

	Table diskTable;
	diskTable.format().multi_byte_characters(true);
	diskTable.add_row({ "Disk name", "Free space", "Used space", "Total space" });
	diskTable[0][1].format().font_color(Color::green);
	diskTable[0][2].format().font_color(Color::red);
	diskTable[0][3].format().font_color(Color::blue);

	for (const auto& diskInfo : disksInfo) {
		diskTable.add_row({
			diskInfo->disk_name,
			std::to_string(diskInfo->total_free) + " " + diskInfo->disk_measurement,
			std::to_string(diskInfo->total_used) + " " + diskInfo->disk_measurement,
			std::to_string(diskInfo->total_size) + " " + diskInfo->disk_measurement,
			});

		diskTable[diskTable.size() - 1][1].format().font_background_color(Color::green);
		diskTable[diskTable.size() - 1][2].format().font_background_color(Color::red);
		diskTable[diskTable.size() - 1][3].format().font_background_color(Color::blue);
	}
	#pragma endregion

	ShowConsoleCursor(false);

	while (true) {
		/* Static measurements */
		memory_m.RunMemoryMeasurements();
		auto memoryMeasurements = memoryLoad->memory_measurement;
		memoryTable[1][0].set_text(std::to_string(memoryLoad->memory_load) + "%");
		memoryTable[1][1].set_text(std::to_string(memoryLoad->memory_free) + memoryMeasurements);
		memoryTable[1][2].set_text(std::to_string(memoryLoad->memory_total) + memoryMeasurements);

		Color memoryLoadColor = Color::green;
		GetColorOnLoad(memoryLoadColor, memoryLoad->memory_load);
		memoryTable[1][0].format().font_background_color(memoryLoadColor);

		/* Pre-measurements */
		cpu_m.RunFirstMeasurements();

		Sleep(300);

		/* Final measurements */
		cpu_m.RunSecondMeasurements();
		cpuTable[1][0].set_text(CPU_M::DoubleToString(cpuLoad->cpu_load) + "%");
		
		Color cpuLoadColor = Color::green;
		GetColorOnLoad(cpuLoadColor, cpuLoad->cpu_load);
		cpuTable[1][0].format().font_background_color(cpuLoadColor);

		/* Console out */
		SetCursorPosition(0, 0);
		cout << "SYSTEM RESOURCE MONITOR" << endl;
		cout << cpuTable << endl;
		cout << memoryTable << endl;
		cout << diskTable << endl;
	}

	ShowConsoleCursor(true);
	return 0;
}