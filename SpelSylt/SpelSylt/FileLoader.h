#pragma once
#include <fstream>
#include "MemAllocSizes.h"

class CFileLoader
{
public:
	CFileLoader() = delete;
	CFileLoader(const char* InPath);
	~CFileLoader();

	bool IsValid() const;
	B GetFileSize() const;
	void LoadData(void* OutData) const;
private:
	mutable std::ifstream FileStream;
};