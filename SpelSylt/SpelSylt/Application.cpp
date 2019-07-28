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

#include "SpelSylt/FileHandling/FileWatcher.h"

using namespace SpelSylt;

//------------------------------------------------------------------

CApplication::CApplication()
	: Window()
	, StateStack()
	, InputManager()
	, Time()
	, MessageQueue()
	, AssetManager()
	, AudioManager("Audio")
	, GameContext(nullptr)
{
}

//------------------------------------------------------------------

CApplication::~CApplication()
{
	Window.close();

	UtilityThread.RequestStop();
	while (!UtilityThread.HaveStopped());
}

//------------------------------------------------------------------

void CApplication::Initialize()
{
	InputManager.Init(&Window);
	Time.Init();

	AudioManager.Init(MessageQueue);

	SS::CAsyncLoader& AsyncLoader = UtilityThread.EmplaceWorker<SS::CAsyncLoader>();
	UtilityThread.EmplaceWorker<SS::CFileWatcher>();
	UtilityThread.Start();

	//Begin Build Contexts
	GameContext = ContextBuilder.BuildGameContext(
		InputManager,
		Time,
		AsyncLoader,
		SynchronousLoader,
		MessageQueue,
		AssetManager
	);
	//End Build Contexts

	AssetManager.ProvideLoaders(AsyncLoader, SynchronousLoader);

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
}

//------------------------------------------------------------------

void CApplication::SetWindowTitle(const char* InTitle)
{
	Window.setTitle(InTitle);
}

//------------------------------------------------------------------

void CApplication::PushState(std::shared_ptr<CState> InState)
{
	StateStack.Push(InState);
}

//------------------------------------------------------------------

bool CApplication::Run()
{
	PrepareForNewFrame();
	
	const bool CouldHandleAllEvents = HandleEvents();
	
	StateStack.Update(*GameContext);
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
			Window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)e.size.width, (float)e.size.height)));
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

	Window.clear(sf::Color(100, 100, 100, 255));
}

//------------------------------------------------------------------

void CApplication::PublishNewFrame()
{
	//float viewX = RenderingContext->Camera.getCenter().x - Window.getSize().x * 0.5f;
	//float viewY = RenderingContext->Camera.getCenter().y - Window.getSize().y * 0.5f;

	//Window.setView(sf::View(sf::FloatRect(viewX, viewY, (float)Window.getSize().x, (float)Window.getSize().y)));

	StateStack.Render(Window);

	Window.display();
}

//------------------------------------------------------------------