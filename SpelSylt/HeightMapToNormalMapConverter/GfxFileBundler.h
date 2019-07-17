#pragma once
#include <array>
#include <vector>
#include <string>
#include <filesystem>

enum EFileType
{
	AlbedoMap,
	NormalMap,
	HeightMap,
	Count,
};

class CFileBundler
{
public:
	using FFileBundle = std::pair<std::string, std::string>;
	using FBundledFiles = std::vector<FFileBundle>;

	CFileBundler();

	void BundleFiles(FBundledFiles& OutBundledFiles, const std::string& InDirectoryPath, const EFileType InFirstType, const EFileType InSecondType);
private:
	EFileType GetFileType(const std::string& InFileName) const;
	bool FileIsOfType(const std::string& InFileName, const EFileType InType) const;
	FFileBundle BundleFile(const std::filesystem::path& InFullPathToBundle, const EFileType InBundleWith);

	std::array<std::string, EFileType::Count> SuffixLookup;
};
