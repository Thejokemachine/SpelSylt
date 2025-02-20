#pragma once
#include "SpelSylt/Utility/Input/KeyCodes.h"
#include "SpelSylt/Utility/Input/InputEventGetter.h"

#include <map>
#include "SFML\Window\Window.hpp"
#include "SFML\System\Vector2.hpp"

namespace SpelSylt
{
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
		virtual bool IsKeyPressed(EKeyCode aKey) const override;
		virtual bool IsKeyDown(EKeyCode aKey) const override;
		virtual bool IsKeyReleased(EKeyCode aKey) const override;

		virtual int GetScrollWheelDelta() const override;
		virtual sf::Vector2f GetMousePosFloat() const override;
		virtual sf::Vector2i GetMousePosInt() const override;

		virtual std::string GetTextInput() const override;
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
}

namespace SS = SpelSylt;