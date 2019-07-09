#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/DirectoryHelpers.h"

//------------------------------------------------------------------

void SDirectoryHelpers::CreateDirectoryIfNotExisting(const char* InRelativePath)
{
	const bool IsDirectory = std::filesystem::is_directory(InRelativePath);
	const bool Exists = std::filesystem::exists(InRelativePath);

	if (!IsDirectory && !Exists)
	{
		std::filesystem::create_directory(InRelativePath);
	}
}

//------------------------------------------------------------------

void SDirectoryHelpers::VisitDirectory(const char* InRelativePath, const FFileIteratorPredicate& InPredicate)
{
	for (auto&& File : std::filesystem::directory_iterator(InRelativePath))
	{
		InPredicate(File);
	}
}

//------------------------------------------------------------------