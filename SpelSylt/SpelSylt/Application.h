#pragma once

#include <SpelSylt/Audio/AudioManager.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Contexts/RenderingContext.h>
#include <SpelSylt/Debugging/Rendering/DebugDrawer.h>
#include <SpelSylt/FileHandling/Banks/TextureBank.h>
#include <SpelSylt/FileHandling/Loading/AsyncLoader.h>
#include <SpelSylt/Messaging/MessageQueue.h>
#include <SpelSylt/Rendering/Renderer.h>
#include <SpelSylt/Rendering/RenderQueue.h>
#include <SpelSylt/State/StateStack.h>
#include <SpelSylt/Utility/Input/InputManager.h>
#include <SpelSylt/Utility/Time/Time.h>

#include <thread>
#include <SFML/Graphics/RenderWindow.hpp>

class CApplication
{
public:
	CApplication();
	CApplication(const CApplication&) = delete;
	CApplication(CApplication&&) = delete;
	~CApplication();

	void Initialize();
	bool Run();
	
protected:
	virtual void SetUpWindow() = 0;
	virtual void PushStartUpStates() = 0;

	void CreateWindow(unsigned int InWindowW, unsigned int InWindowH, bool InFullscreen = false);
	void SetWindowTitle(const char* InTitle);
	void PushState(CState* InState);
private:
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