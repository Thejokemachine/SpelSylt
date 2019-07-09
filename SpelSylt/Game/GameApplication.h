#pragma once
#include <SpelSylt/Application.h>

class CGameApplication final
	: public CApplication
{
private:
	virtual void SetUpWindow() override;
	virtual void PushStartUpStates() override;
};