#pragma once
#include "UI/Panel.h"

namespace UI
{
	class Button : public Panel
	{
		friend UILayout;

	public:

		Button(UI::UILayout& aLayout, const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement);

		void SetCallback(std::function<void(Button& button)> aOnPressed);

	private:

		std::function<void(Button& button)> myOnPressed;

	};
}