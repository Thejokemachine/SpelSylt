#pragma once
#include <SpelSylt/Application.h>

class CGameApplication final
	: public SpelSylt::CApplication
{
private:
	virtual void SetUpWindow() override;
	virtual void PushStartUpStates() override;
};