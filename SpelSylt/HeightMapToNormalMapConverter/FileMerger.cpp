#include "HeightMapToNormalMapConverter/FileMerger.h"

#include <fstream>

//------------------------------------------------------------------

CFileMerger::CFileMerger()
{

}

//------------------------------------------------------------------

void CFileMerger::SetExtension(const std::string& InExtension)
{
	Extension = InExtension;
}

//------------------------------------------------------------------

void CFileMerger::AddPathForMerge(const std::string& InFullPath)
{
	PathsToMerge.emplace_back(InFullPath);
	HeaderData.push_back(GetFileSize(InFullPath));
}

//------------------------------------------------------------------

void CFileMerger::Merge(const std::string& OutPath)
{
	char* Buffer = new char[GetTotalSize()];
	unsigned long long CurrentBufferOffset = 0ull;

	std::ifstream ReadStream;
	for (auto i = 0ull; i < PathsToMerge.size(); ++i)
	{
		const auto& PathToRead = PathsToMerge[i];
		ReadStream.open(PathToRead, std::ifstream::beg | std::ifstream::binary);
		ReadStream.read(&(Buffer[CurrentBufferOffset]), HeaderData[i]);
		ReadStream.close();

		CurrentBufferOffset += HeaderData[i];
	}

	std::ofstream WriteStream(OutPath + Extension, std::ofstream::trunc | std::ofstream::binary);
	for (auto Data : HeaderData)
	{
		WriteStream << Data;
	}

	WriteStream.write(Buffer, GetTotalSize());
	WriteStream.close();
}

//------------------------------------------------------------------

unsigned long long CFileMerger::GetTotalSize() const
{
	auto TotalSize = 0ull;

	for (auto Size : HeaderData)
	{
		TotalSize += Size;
	}

	return TotalSize;
}

//------------------------------------------------------------------

unsigned long long CFileMerger::GetFileSize(const std::string& InPath) const
{
	std::ifstream FileStream(InPath);
	const auto Begin = FileStream.tellg();
	FileStream.seekg(0, std::ios::end);
	const auto End = FileStream.tellg();
	FileStream.close();
	return static_cast<unsigned long long>(End - Begin);
}

//------------------------------------------------------------------