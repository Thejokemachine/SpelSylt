#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Application.h"

#include "SpelSylt/Utility/Time/Time.h"
#include "SpelSylt/Utility/Input/InputManager.h"
#include "SpelSylt/Messaging/Messages/UIMessages.h"
#include "SpelSylt/UI/Base/UIState.h"

#include "Game/HookGame.h"
#include "Game/HookUIState.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

//------------------------------------------------------------------

CApplication::CApplication()
	: StateStack()
	, InputManager()
	, Time()
	, Window()
	, Renderer()
	, TextureBank(AsyncLoader)
	, RenderQueue()
	, MessageQueue()
	, DebugDrawer()
	, AudioManager("Audio")
	, GameContext(InputManager, Time, AsyncLoader, TextureBank, MessageQueue)
	, RenderingContext(RenderQueue, DebugDrawer)
	, AsyncLoader()
{
}

//------------------------------------------------------------------

CApplication::~CApplication()
{
	Window.close();
	AsyncLoader.RequestShutDown();
	while (!AsyncLoader.HasShutDown());
	LoadThread.join();
}

//------------------------------------------------------------------

void CApplication::Initialize()
{
	InputManager.Init(&Window);
	Time.Init();

	AudioManager.Init(MessageQueue);

	AsyncLoader.ProvideThread(LoadThread);

	SetUpWindow();
	PushStartUpStates();
}

//------------------------------------------------------------------

void CApplication::CreateWindow(unsigned int InWindowW, unsigned int InWindowH, bool InFullscreen )
{
	sf::VideoMode vm;
	vm.width = InWindowW;
	vm.height = InWindowH;
	vm.bitsPerPixel = 32;

	Window.create(vm, "SpelSylt Application");
	Window.setFramerateLimit(60u);

	RenderingContext.Camera.setSize(static_cast<float>(vm.width), static_cast<float>(vm.height));
}

//------------------------------------------------------------------

void CApplication::SetWindowTitle(const char* InTitle)
{
	Window.setTitle(InTitle);
}

//------------------------------------------------------------------

void CApplication::PushState(CState* InState)
{
	StateStack.Push(InState, GameContext, RenderingContext);
}

//------------------------------------------------------------------

bool CApplication::Run()
{
	PrepareForNewFrame();
	
	const bool CouldHandleAllEvents = HandleEvents();
	
	StateStack.Update(GameContext);
	MessageQueue.SendAllEvents();

	const bool StateStackValid = StateStack.Size() > 0;

	PublishNewFrame();

	return CouldHandleAllEvents && StateStackValid;
}

//------------------------------------------------------------------

bool CApplication::HandleEvents()
{
	sf::Event e;
	while (Window.pollEvent(e))
	{
		if (e.type == sf::Event::Closed)
		{
			return false;
		}
		else if (e.type == sf::Event::Resized)
		{
			MessageQueue.DispatchEvent<SResizedWindowMessage>(e.size.width, e.size.height);
		}
		else
		{
			InputManager.Update(e);
		}
	}

	return true;
}

//------------------------------------------------------------------

void CApplication::PrepareForNewFrame()
{
	InputManager.OncePerFrameUpdate();
	Time.Update();

	Window.clear(sf::Color::Blue);
	RenderQueue.Clear();
	DebugDrawer.clear();
}

//------------------------------------------------------------------

void CApplication::PublishNewFrame()
{
	Window.setView(RenderingContext.Camera);

	StateStack.Render(RenderingContext);

	Renderer.RunRenderAllLayers(RenderQueue, Window);
	DebugDrawer.draw(Window, sf::RenderStates::Default);

	Window.display();
}

//------------------------------------------------------------------