#include <SpelSylt/EngineStartUp.h>

#include "EngineTestProject/EngineTestApplication.h"


int main()
{
	testproj::CTestApplication App;

	App.Initialize();
	while (App.Run());

	return 0;
}