#include "SpelSyltPCH.h"

#include "FileHandling/Loading/FileLoader.h"

//------------------------------------------------------------------

CFileLoader::CFileLoader(const char* InPath)
	: FileStream(InPath, std::ios::binary)
{
}

//------------------------------------------------------------------

CFileLoader::~CFileLoader()
{
	FileStream.close();
}

//------------------------------------------------------------------

bool CFileLoader::IsValid() const
{
	return FileStream.is_open() && !FileStream.bad();
}

//------------------------------------------------------------------

B CFileLoader::GetFileSize() const
{
	const auto Begin = FileStream.tellg();
	FileStream.seekg(0, std::ios::end);
	const auto End = FileStream.tellg();
	FileStream.seekg(0, std::ios::beg);
	return static_cast<B>(End - Begin);
}

//------------------------------------------------------------------

void CFileLoader::LoadData(char* OutData) const
{
	FileStream.read(OutData, GetFileSize());
}

//------------------------------------------------------------------