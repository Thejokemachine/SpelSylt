#pragma once

#include "State.h"

class GameState : public CState
{
public:
	GameState();
	~GameState();

	virtual void Init();
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow* aRenderWindow);
};

