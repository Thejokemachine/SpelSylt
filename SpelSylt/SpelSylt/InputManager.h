#pragma once
#include "KeyCodes.h"
#include "InputEventGetter.h"
#include <map>
#include "SFML\Window\Window.hpp"
#include "SFML\System\Vector2.hpp"

class CInputManager final
	: public IInputEventGetter
{
public:
	CInputManager();
	~CInputManager();

	void Init(sf::Window* aClientWindow);
	void Update(const sf::Event& aWindowsMessage);
	void UpdateKeys(const sf::Event& aWindowsMessage);
	void UpdateMouse(const sf::Event& aWindowsMessage);
	void OncePerFrameUpdate();

	//Begin IInputEventGetter
	virtual bool IsKeyPressed(EKeyCode aKey) override;
	virtual bool IsKeyDown(EKeyCode aKey) override;
	virtual bool IsKeyReleased(EKeyCode aKey) override;

	virtual int GetScrollWheelDelta() override;
	virtual sf::Vector2f GetMousePosFloat() override;
	virtual sf::Vector2i GetMousePosInt() override;

	virtual std::string GetTextInput() override;
	//End IInputEventGetter

private:
	std::map<EKeyCode, EKeyState> myKeyStates;
	std::map<EKeyCode, EKeyState> myPreviousKeyStates;

	std::map<EKeyCode, EKeyState> myMouseButtonStates;
	std::map<EKeyCode, EKeyState> myPreviousMouseButtonStates;

	float myWheelDelta;

	std::string myTextInput;

	sf::Window* myHWND;
};

