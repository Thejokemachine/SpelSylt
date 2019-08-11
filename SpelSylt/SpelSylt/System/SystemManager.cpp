#include "SpelSylt/SpelSyltPCH.h"
#include "SpelSylt/System/SystemManager.h"

//------------------------------------------------------------------

using namespace SpelSylt;

//------------------------------------------------------------------

CSystemManager::CSystemManager()
{
	SystemBuffer.Allocate(1_mb);
}

//------------------------------------------------------------------

CSystemManager::CSystemManager(B InTotalSystemsSize)
{
	SystemBuffer.Allocate(InTotalSystemsSize);
}

//------------------------------------------------------------------

CSystemManager::~CSystemManager()
{
	SystemBuffer.Flush();
}

//------------------------------------------------------------------

void CSystemManager::RunSystemsTick(float InDT)
{
	for (ISystem*& System : SystemPtrs)
	{
		System->Tick(InDT);
	}
}

//------------------------------------------------------------------

void CSystemManager::RunSystemsRender(CRenderQueue& InRenderQueue)
{
	for (ISystem*& System : SystemPtrs)
	{
		System->Render(InRenderQueue);
	}
}

//------------------------------------------------------------------