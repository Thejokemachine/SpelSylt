#pragma once

#include "Debugging/Rendering/DebugDrawer.h"

#include "Rendering/Renderer.h"
#include "Contexts/RenderingContext.h"
#include "Rendering/RenderQueue.h"

#include "Utility/Input/InputManager.h"
#include "Utility/Time/Time.h"
#include "Contexts/GameContext.h"

#include "State/StateStack.h"

#include "FileHandling/Loading/AsyncLoader.h"
#include <thread>

#include "Audio/AudioManager.h"
#include "FileHandling/Banks/TextureBank.h"
#include "Messaging/MessageQueue.h"

#include <SFML/Graphics/RenderWindow.hpp>

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

	CInputManager InputManager;
	CTime Time;

	CStateStack StateStack;

	sf::RenderWindow Window;
	
	CRenderer Renderer;
	CDebugDrawer DebugDrawer;

	CAudioManager AudioManager;

	CTextureBank TextureBank;

	CRenderQueue RenderQueue;

	CMessageQueue MessageQueue;

	//Contexts
	SGameContext GameContext;
	SRenderingContext RenderingContext;

	CAsyncLoader AsyncLoader;
	std::thread LoadThread;
};