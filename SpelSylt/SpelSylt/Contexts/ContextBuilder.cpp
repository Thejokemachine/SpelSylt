#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Contexts/ContextBuilder.h"

//------------------------------------------------------------------

CContextBuilder::CContextBuilder()
	: BuiltGameContext(nullptr)
	, BuiltRenderingContext(nullptr)
{
}

//------------------------------------------------------------------

SGameContext* CContextBuilder::BuildGameContext(
	IInputEventGetter& InInputEventGetter,
	ITimeGetter& InTimeGetter,
	IAsyncLoader& InAsyncLoader,
	CMessageQueue& InMessageQueue,
	SS::CAssetManager& InAssetManager )
{
#ifdef _DEBUG
	if (BuiltGameContext)
	{
		LOG_ERROR(ContextBuilder, "Game context already created?");
	}
#endif

	BuiltGameContext = new SGameContext(
		InInputEventGetter,
		InTimeGetter,
		InAsyncLoader,
		InMessageQueue,
		InAssetManager );

	return BuiltGameContext;
}

//------------------------------------------------------------------

SRenderingContext* CContextBuilder::BuildRenderingContext(
	IRenderQueueInput& InRenderQueueInput,
	IDebugDrawerInput& InDebugDrawerInput)
{
#ifdef _DEBUG
	if (BuiltGameContext)
	{
		LOG_ERROR(ContextBuilder, "Rendering context already created?");
	}
#endif

	BuiltRenderingContext = new SRenderingContext(
		InRenderQueueInput,
		InDebugDrawerInput);


	return BuiltRenderingContext;
}

//------------------------------------------------------------------