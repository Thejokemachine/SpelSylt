#include "sfml_libs.h"

#include "SFML/Graphics.hpp"

#include "InputManager.h"
#include "StateStack.h"
#include "Time.h"

//States
#include "HookGame.h"
#include "RenderingTestState.h"
//States

#include "Renderer.h"
#include "RenderQueue.h"
#include "RenderingContext.h"

#include "DebugLogger.h"

void LoggingSetup()
{
	/*
	Uncomment the log level you want
	Verbose		= Log all logs
	Log			= Log all logs except verbose
	Warning		= Log warnings and errors only
	Error		= Log errors only

	Note: Only the last uncommented log level will be regarded!
	*/
	SET_LOG_LEVEL_VERBOSE;
	//SET_LOG_LEVEL_LOG;
	//SET_LOG_LEVEL_WARNING;
	//SET_LOG_LEVEL_ERROR;

	/* Uncomment this line to output all logs withing the set log level to file */
	//LOG_TO_FILE;
}

int main()
{
	LoggingSetup();

	sf::VideoMode vm;
	vm.width = 1600;
	vm.height = 900;
	vm.bitsPerPixel = 32;

	sf::RenderWindow window(vm, "SpelSylt");

	CInputManager& inputManager = CInputManager::GetInstance();
	inputManager.Init(&window);

	CTime& time = CTime::GetInstance();
	time.Init();

	CStateStack stateStack;
	stateStack.Push(new CRenderingTestState());
	//This one is not yet retargeted to the new rendering infrastructure!
	//stateStack.Push(new HookGame());

	CRenderer Renderer;
	CRenderQueue RenderQueue;
	SRenderingContext RenderingContext(RenderQueue);

	window.setFramerateLimit(60); // Fix when physics

	sf::Event e;
	while (window.isOpen())
	{
		window.clear(sf::Color::Magenta);
		inputManager.OncePerFrameUpdate();
		time.Update();

		while (window.pollEvent(e))
		{
			if (e.type == sf::Event::Closed)
			{
				window.close();
			}
			else
			{
				inputManager.Update(e);
			}
		}

		stateStack.Update(time.GetDeltaTime());
		stateStack.Render(RenderingContext);

		Renderer.RunRenderAllLayers(RenderQueue, window);
		RenderQueue.Clear();

		window.display();

		if (stateStack.Size() == 0)
		{
			window.close();
		}
	}

	return 0;
}