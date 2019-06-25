#include "sfml_libs.h"

#include "SFML/Graphics.hpp"

#include "InputManager.h"
#include "StateStack.h"
#include "Time.h"
#include "GameState.h"

int main()
{
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
	stateStack.Push(new GameState());

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
		stateStack.Render(&window);

		window.display();

		if (stateStack.Size() == 0)
		{
			window.close();
		}
	}

	return 0;
}