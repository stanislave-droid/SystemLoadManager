#include "Disk_M.h"

void Disk_M::GetDiskCount()
{
	auto diskInfo = this->disksInfo;
	DWORD bufferSize = GetLogicalDriveStringsW(0, NULL);
	
	if (bufferSize == 0) {
		diskInfo.clear();
		std::cerr << "Failed to get buffer size." << std::endl;
		return;
	}

	std::vector<wchar_t> buffer(bufferSize);

	if (GetLogicalDriveStringsW(bufferSize, buffer.data()) == 0) {
		diskInfo.clear();
		std::cerr << "Failed to get drives." << std::endl;
		return;
	}

	auto drives = buffer.data();
	while (*drives) {
		std::wstring drive(drives);
		this->drives.push_back(drive);
		drives += drive.length() + 1;
	}
}

void Disk_M::GetDiskInfo()
{
	auto drives = this->drives;

	for (const auto& drive: drives) {
		auto info = std::make_shared<DiskInfo>();
		ULARGE_INTEGER freeBytes, totalBytes, totalFreeBytes;

		info->disk_name = drive;

		if (GetDiskFreeSpaceExW(drive.c_str(), &freeBytes, &totalBytes, &totalFreeBytes)) {
			BytesToGB(totalBytes.QuadPart, info->total_size);
			BytesToGB(totalFreeBytes.QuadPart, info->total_free);
			info->total_used = info->total_size - info->total_free;
			this->disksInfo.push_back(info);
		}
		else {
			std::wcerr << L"Failed to get disk info of: " << drive << std::endl;
		}

	}
}

void Disk_M::BytesToGB(unsigned long long bytes, unsigned long long& gb)
{
	gb = bytes / (1024ULL * 1024 * 1024);
}

Disk_M::Disk_M()
{
	auto diskInfo = this->disksInfo;
	GetDiskCount();
	GetDiskInfo();
}
