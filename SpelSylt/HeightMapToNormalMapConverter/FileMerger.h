#pragma once
#include <vector>
#include <string>

class CFileMerger
{
public:
	CFileMerger();
	void SetExtension(const std::string& InExtension);
	void AddPathForMerge(const std::string& InFullPath);

	void Merge(const std::string& OutPath);
private:
	unsigned long long GetTotalSize() const;

	unsigned long long GetFileSize(const std::string& InPath) const;
	std::vector<double> HeaderData;
	std::vector<std::string> PathsToMerge;
	std::string Extension;
};