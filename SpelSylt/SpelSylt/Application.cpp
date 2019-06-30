#include "SpelSyltPCH.h"

#include "Application.h"

#include "Time.h"
#include "InputManager.h"

#include "HookGame.h"

#include <SFML/Graphics/Color.hpp>
#include <SFML/Window/Event.hpp>

//------------------------------------------------------------------

CApplication::CApplication()
	: StateStack()
	, InputManager()
	, Time()
	, Window()
	, Renderer()
	, RenderQueue()
	, DebugDrawer()
	, GameContext(InputManager, Time)
	, RenderingContext(RenderQueue, DebugDrawer)
{
}

//------------------------------------------------------------------

void CApplication::Initialize()
{
	CreateWindow();
	InputManager.Init(&Window);
	Time.Init();

	StateStack.Push(new HookGame());
	//StateStack.Push(new CRenderingTestState());
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
			return false;
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

	Window.clear(sf::Color::Magenta);
	RenderQueue.Clear();
	DebugDrawer.clear();
}

//------------------------------------------------------------------

void CApplication::PublishNewFrame()
{
	StateStack.Render(RenderingContext);

	Window.setView(RenderingContext.Camera);

	Renderer.RunRenderAllLayers(RenderQueue, Window);
	DebugDrawer.draw(Window, sf::RenderStates::Default);

	Window.display();
}

//------------------------------------------------------------------