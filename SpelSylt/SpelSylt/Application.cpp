#include "SpelSyltPCH.h"

#include "Application.h"

#include "Utility/Time/Time.h"
#include "Utility/Input/InputManager.h"
#include "Messaging/Messages/UIMessages.h"
#include "UI/Base/UIState.h"

//#include "HookGame.h"
//#include "HookUIState.h"

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

void CApplication::Initialize()
{
	CreateWindow();
	InputManager.Init(&Window);
	Time.Init();

	AudioManager.Init(MessageQueue);

	//StateStack.Push(new HookGame(), GameContext, RenderingContext);
	//StateStack.Push(new UIState(1600,900), GameContext, RenderingContext);
	//StateStack.Push(new CRenderingTestState());

	AsyncLoader.ProvideThread(LoadThread);
}

//------------------------------------------------------------------

void CApplication::CreateWindow()
{
	sf::VideoMode vm;
	vm.width = 1600;
	vm.height = 900;
	vm.bitsPerPixel = 32;

	Window.create(vm, "SpelSylt");
	Window.setFramerateLimit(60u);

	RenderingContext.Camera.setSize(static_cast<float>(vm.width), static_cast<float>(vm.height));
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
			Window.close();

			AsyncLoader.RequestShutDown();
			while (!AsyncLoader.HasShutDown());
			LoadThread.join();

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