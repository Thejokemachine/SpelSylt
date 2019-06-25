#include "InputManager.h"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Window.hpp"

CInputManager::CInputManager()
{
}


CInputManager::~CInputManager()
{
}

CInputManager & CInputManager::GetInstance()
{
	static CInputManager instance;

	return instance;
}

void CInputManager::Init(sf::Window* aClientWindow)
{
	myHWND = aClientWindow;
	CreateKeyStates(myKeyStates);
	myPreviousKeyStates = myKeyStates;

	myMouseButtonStates.insert(std::make_pair(EKeyCode::MouseLeft, EKeyState::Up));
	myMouseButtonStates.insert(std::make_pair(EKeyCode::MouseMiddle, EKeyState::Up));
	myMouseButtonStates.insert(std::make_pair(EKeyCode::MouseRight, EKeyState::Up));
	myPreviousMouseButtonStates = myMouseButtonStates;
}

void CInputManager::Update(const sf::Event& aWindowsMessage)
{
	UpdateKeys(aWindowsMessage);
	UpdateMouse(aWindowsMessage);

	if (aWindowsMessage.type == sf::Event::TextEntered)
	{
		myTextInput += static_cast<char>(aWindowsMessage.text.unicode);
	}
}

void CInputManager::UpdateKeys(const sf::Event & aWindowsMessage)
{
	switch (aWindowsMessage.type)
	{
	case sf::Event::KeyPressed:
	{
		EKeyCode key = static_cast<EKeyCode>(aWindowsMessage.key.code);

		if (myKeyStates.find(key) != myKeyStates.end())
		{
			myKeyStates[key] = EKeyState::Down;
		}

		break;
	}
	case sf::Event::KeyReleased:
	{
		EKeyCode key = static_cast<EKeyCode>(aWindowsMessage.key.code);

		if (myKeyStates.find(key) != myKeyStates.end())
		{
			myKeyStates[key] = EKeyState::Up;
		}

		break;
	}
	case sf::Event::MouseButtonPressed:
	{
		EKeyCode key;
		
		switch (aWindowsMessage.mouseButton.button)
		{
		case sf::Mouse::Left:
			key = EKeyCode::MouseLeft;
			myMouseButtonStates[key] = EKeyState::Down;
			break;
		case sf::Mouse::Right:
			key = EKeyCode::MouseRight;
			myMouseButtonStates[key] = EKeyState::Down;
			break;
		case sf::Mouse::Middle:
			key = EKeyCode::MouseMiddle;
			myMouseButtonStates[key] = EKeyState::Down;
			break;
		}

		break;
	}
	case sf::Event::MouseButtonReleased:
	{
		EKeyCode key;

		switch (aWindowsMessage.mouseButton.button)
		{
		case sf::Mouse::Left:
			key = EKeyCode::MouseLeft;
			myMouseButtonStates[key] = EKeyState::Up;
			break;
		case sf::Mouse::Right:
			key = EKeyCode::MouseRight;
			myMouseButtonStates[key] = EKeyState::Up;
			break;
		case sf::Mouse::Middle:
			key = EKeyCode::MouseMiddle;
			myMouseButtonStates[key] = EKeyState::Up;
			break;
		}
		break;
	}
	}
}

void CInputManager::UpdateMouse(const sf::Event & aWindowsMessage)
{
	if (aWindowsMessage.type == sf::Event::MouseWheelScrolled)
	{
		myWheelDelta = aWindowsMessage.mouseWheelScroll.delta;
	}
}

void CInputManager::OncePerFrameUpdate()
{
	myPreviousKeyStates = myKeyStates;
	myPreviousMouseButtonStates = myMouseButtonStates;
	myWheelDelta = 0.0f;
	myTextInput.clear();
}

bool CInputManager::IsKeyPressed(EKeyCode aKey)
{
	if (static_cast<int>(aKey) - 200 <= 0)
		return myKeyStates[aKey] == EKeyState::Down && myPreviousKeyStates[aKey] == EKeyState::Up;
	else
		return myMouseButtonStates[aKey] == EKeyState::Down && myPreviousMouseButtonStates[aKey] == EKeyState::Up;
}

bool CInputManager::IsKeyDown(EKeyCode aKey)
{
	if (static_cast<int>(aKey) - 200 <= 0)
		return myKeyStates[aKey] == EKeyState::Down;
	else
		return myMouseButtonStates[aKey] == EKeyState::Down;
}

bool CInputManager::IsKeyReleased(EKeyCode aKey)
{
	if (static_cast<int>(aKey) - 200 <= 0)
		return myKeyStates[aKey] == EKeyState::Up && myPreviousKeyStates[aKey] == EKeyState::Down;
	else
		return myMouseButtonStates[aKey] == EKeyState::Up && myPreviousMouseButtonStates[aKey] == EKeyState::Down;
}

int CInputManager::GetScrollWheelDelta()
{
	return static_cast<int>(myWheelDelta);
}

sf::Vector2f CInputManager::GetMousePosFloat()
{
	sf::Vector2i mPos = sf::Mouse::getPosition(*myHWND);
	return sf::Vector2f(static_cast<float>(mPos.x), static_cast<float>(mPos.y));
}

sf::Vector2i CInputManager::GetMousePosInt()
{
	return sf::Mouse::getPosition(*myHWND);
}

std::string CInputManager::GetTextInput()
{
	return std::move(myTextInput);
}
