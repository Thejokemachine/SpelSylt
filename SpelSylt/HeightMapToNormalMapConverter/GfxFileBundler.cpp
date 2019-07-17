#include "HeightMapToNormalMapConverter/GfxFileBundler.h"

#include "HeightMapToNormalMapConverter/MessagePrinter.h"
#include "HeightMapToNormalMapConverter/FileMutator.h"


#include <set>

//------------------------------------------------------------------

CFileBundler::CFileBundler()
{
	SuffixLookup[EFileType::AlbedoMap] = "_AL";
	SuffixLookup[EFileType::HeightMap] = "_HM";
	SuffixLookup[EFileType::NormalMap] = "_NM";
}

//------------------------------------------------------------------

void CFileBundler::BundleFiles(FBundledFiles& OutBundledFiles, const std::string& InDirectoryPath, const EFileType InFirstType, const EFileType InSecondType)
{
	if (!std::filesystem::is_directory(InDirectoryPath))
	{
		MessagePrinter::PrintError("Tried to bundle files with directory path set to " + InDirectoryPath + " which is not a directory!");
		return;
	}

	std::set<std::string> FilesAlreadyBundled;

	for (auto&& File : std::filesystem::directory_iterator(InDirectoryPath))
	{
		std::filesystem::path FilePath = File.path();
		const std::string FileName = FilePath.stem().string();
		std::string FileNameNoSuffix = FileMutator::GetFileNameWithoutSuffix(FileName);

		if (FilesAlreadyBundled.find(FileNameNoSuffix) != FilesAlreadyBundled.end())
		{
			//We've already bundled this one.
			continue;
		}

		const EFileType FileType = GetFileType(FileName);
		const EFileType PairWithType = FileType == InFirstType ? InSecondType : InFirstType;
		OutBundledFiles.push_back(BundleFile( FilePath, PairWithType ));

		FilesAlreadyBundled.insert(FileNameNoSuffix);
	}
}

//------------------------------------------------------------------

EFileType CFileBundler::GetFileType(const std::string& InFileName) const
{
	std::string Suffix = FileMutator::GetFileSuffix(InFileName);

	for (int i = 0; i < SuffixLookup.max_size(); ++i)
	{
		if (SuffixLookup[i] == Suffix)
		{
			return static_cast<EFileType>(i);
		}
	}

	return EFileType::Count;
}

//------------------------------------------------------------------

bool CFileBundler::FileIsOfType(const std::string& InFileName, const EFileType InType) const
{
	return FileMutator::GetFileSuffix(InFileName) == SuffixLookup[InType];
}

//------------------------------------------------------------------

const CFileBundler::FFileBundle& CFileBundler::BundleFile(const std::filesystem::path& InFullPathToBundle, const EFileType InBundleWith)
{
	const std::string FileName = InFullPathToBundle.stem().string();
	const std::string FileNameNoSuffix = FileMutator::GetFileNameWithoutSuffix(FileName);
	const std::string FileNameToFind = FileNameNoSuffix + SuffixLookup[InBundleWith];
	const std::string PathToPairWith = InFullPathToBundle.parent_path().string() + "\\" + FileNameToFind + ".png";

	return CFileBundler::FFileBundle(InFullPathToBundle.string(), PathToPairWith);
}

//------------------------------------------------------------------