#pragma once

#include "Renderer.h"
#include "RenderingContext.h"
#include "RenderQueue.h"

#include "StateStack.h"

#include <SFML/Graphics/RenderWindow.hpp>

class CTime;
class CInputManager;

class CApplication
{
public:
	CApplication();
	CApplication(const CApplication&) = delete;
	CApplication(CApplication&&) = delete;

	void Initialize();
	bool Run();
private:
	void CreateWindow();

	void PrepareForNewFrame();
	void PublishNewFrame();

	bool HandleEvents();

	CInputManager& InputManager;
	CTime& Time;

	CStateStack StateStack;

	sf::RenderWindow Window;
	CRenderer Renderer;
	CRenderQueue RenderQueue;
	SRenderingContext RenderingContext;
};