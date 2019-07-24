#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/FileHandling/Loading/SynchronousLoader.h"

#include "SpelSylt/FileHandling/Asset/Asset.h"
#include "SpelSylt/FileHandling/Loading/FileLoader.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CSynchronousLoader::CSynchronousLoader()
{
}

//------------------------------------------------------------------

void CSynchronousLoader::Load(const char* InPath, SBaseAsset& InTo)
{
	CFileLoader FileLoader(InPath);

	if (FileLoader.IsValid())
	{
		const B DataSize = FileLoader.GetFileSize();
		char* LoadDataBuffer = new char[DataSize];

		FileLoader.LoadData(LoadDataBuffer);
		InTo.SetData(LoadDataBuffer, DataSize);

		delete[DataSize] LoadDataBuffer;
		InTo.LoadStatus = ELoadRequestStatus::Done;
	}
	else
	{
		InTo.LoadStatus = ELoadRequestStatus::Fail;
	}
}

//------------------------------------------------------------------
