#pragma once
#include <SpelSylt/Application.h>

namespace testproj
{
	class CTestApplication
		: public SS::CApplication
	{
	public:
		virtual void SetUpWindow() override;
		virtual void PushStartUpStates() override;
	};
}