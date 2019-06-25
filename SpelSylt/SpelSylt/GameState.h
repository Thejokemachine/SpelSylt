#pragma once

#include "State.h"
#include "AudioManager.h"

class GameState : public CState
{
public:
	GameState();
	~GameState();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow* aRenderWindow);

private:
	AudioManager myAudioManager;
};

