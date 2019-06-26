#pragma once
#include <string>
#include <fstream>

class CTextFileHandler
{
public:
	enum class EFileOpenMode
	{
		None,
		Write,
		Read,
	};
public:
	CTextFileHandler();
	~CTextFileHandler();

	bool OpenFile(const std::string& InRelativeFilePath, EFileOpenMode InOpenMode);
	void CloseFile();

	bool IsOpen() const;

	bool ChangeFileOpenMode(EFileOpenMode InOpenMode);

	bool Write(const std::string& InMessage);
	bool WriteLine(const std::string& InMessage);

private:
	bool OpenWriteFile(const std::string& InRelativePath);

	EFileOpenMode CurrentMode;
	std::ofstream WriteStream;
	std::string CurrentFile;
};