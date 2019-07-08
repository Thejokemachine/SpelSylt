#pragma once
#include <fstream>
#include "Memory/MemAllocSizes.h"

class CFileLoader
{
public:
	CFileLoader() = delete;
	CFileLoader(const char* InPath);
	~CFileLoader();

	bool IsValid() const;
	B GetFileSize() const;
	void LoadData(char* OutData) const;
private:
	mutable std::ifstream FileStream;
};