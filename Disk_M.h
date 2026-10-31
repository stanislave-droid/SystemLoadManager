#pragma once
#include <memory>
#include <vector>
#include <Windows.h>
#include <iostream>

class Disk_M
{
public:
	struct DiskInfo
	{
		std::wstring disk_name = L"C:/";
		unsigned long long total_free = 0;
		unsigned long long total_size = 0;
		unsigned long long total_used = 0;
		char disk_measurement[2] = { 'G','B' };
	};
private:
	void GetDiskCount();
	void GetDiskInfo();
	void BytesToGB(unsigned long long bytes, unsigned long long& gb);
public:
	std::vector<std::shared_ptr<DiskInfo>> disksInfo;
	std::vector<std::wstring> drives;
	Disk_M();
};

