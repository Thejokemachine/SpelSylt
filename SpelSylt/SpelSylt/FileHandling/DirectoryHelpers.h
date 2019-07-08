#pragma once

#include <filesystem>
#include <functional>

using FFile = std::filesystem::directory_entry;
using FFileIteratorPredicate = std::function<void(const FFile&)>;

struct SDirectoryHelpers
{
	static void CreateDirectoryIfNotExisting(const char* InRelativePath);
	static void VisitDirectory(const char* InRelativePath, const FFileIteratorPredicate& InPredicate);
};