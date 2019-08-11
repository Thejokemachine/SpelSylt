#include "EngineTestProject/EngineTestApplication.h"

#include "EngineTestProject/EngineTestProjectState.h"

//------------------------------------------------------------------

using namespace testproj;

//------------------------------------------------------------------

void CTestApplication::SetUpWindow()
{
	CreateWindow(800, 800);
	SetWindowTitle("Test Project");
}

//------------------------------------------------------------------

void CTestApplication::PushStartUpStates()
{
	CApplication::PushState(std::make_shared<CTestProjectState>());
}

//------------------------------------------------------------------
