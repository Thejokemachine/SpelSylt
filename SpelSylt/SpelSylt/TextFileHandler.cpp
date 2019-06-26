#include "TextFileHandler.h"

#include "DebugLogger.h"

//------------------------------------------------------------------

CTextFileHandler::CTextFileHandler()
	: CurrentMode(EFileOpenMode::None)
	, WriteStream()
	, CurrentFile("")
{
}

//------------------------------------------------------------------

CTextFileHandler::~CTextFileHandler()
{
	if (CurrentMode != EFileOpenMode::None)
	{
		CloseFile();
		LOG_WARNING(TextFileHandler, "Text file handler for file %s was destroyed without closing the file. File automatically closed. Ensure Close is called for all files opened!", CurrentFile.c_str());
	}
}

//------------------------------------------------------------------

bool CTextFileHandler::OpenFile(const std::string& InRelativeFilePath, EFileOpenMode InOpenMode)
{
	if (CurrentMode != EFileOpenMode::None)
	{
		CloseFile();
	}

	switch (InOpenMode)
	{
	case CTextFileHandler::EFileOpenMode::None:
		LOG_ERROR(TextFileHandler, "Tried opening file %s with Open Mode set to None", InRelativeFilePath);
		return false;
		break;
	case CTextFileHandler::EFileOpenMode::Write:
		return OpenWriteFile(InRelativeFilePath);
		break;
	case CTextFileHandler::EFileOpenMode::Read:
		break;
	default:
		break;
	}

	LOG_WARNING(TextFileHandler, "Failed to open file %s", InRelativeFilePath.c_str());
	CurrentMode = EFileOpenMode::None;
	return false;
}

//------------------------------------------------------------------

void CTextFileHandler::CloseFile()
{
	switch (CurrentMode)
	{
	case CTextFileHandler::EFileOpenMode::None:
		break;
	case CTextFileHandler::EFileOpenMode::Write:
		WriteStream.close();
		break;
	case CTextFileHandler::EFileOpenMode::Read:
		break;
	default:
		break;
	}

	CurrentMode = EFileOpenMode::None;
}

//------------------------------------------------------------------

bool CTextFileHandler::IsOpen() const
{
	return CurrentMode != EFileOpenMode::None;
}

//------------------------------------------------------------------


bool CTextFileHandler::ChangeFileOpenMode(EFileOpenMode InOpenMode)
{
	if (InOpenMode != CurrentMode)
	{
		return OpenFile(CurrentFile, InOpenMode);
	}

	LOG_VERBOSE(TextFileHandler, "Tried to change Open Mode for file %s to the same that it was already in", CurrentFile.c_str());
	return false;
}

//------------------------------------------------------------------

bool CTextFileHandler::OpenWriteFile(const std::string& InRelativePath)
{
	CurrentMode = EFileOpenMode::Write;
	WriteStream.open(InRelativePath, std::ofstream::app);
	return WriteStream.is_open();
}

//------------------------------------------------------------------

bool CTextFileHandler::Write(const std::string& InMessage)
{
	if (CurrentMode == EFileOpenMode::Write)
	{
		WriteStream << InMessage;
		return true;
	}
	
	LOG_ERROR(TextFileHandler, "Write called on file %s that was not open for writing", CurrentFile.c_str());
	return false;
}

//------------------------------------------------------------------

bool CTextFileHandler::WriteLine(const std::string& InMessage)
{
	if (Write(InMessage))
	{
		WriteStream << '\n';
		return true;
	}

	return false;
}

//------------------------------------------------------------------
