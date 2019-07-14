#pragma once
#include "SpelSylt/UI/Panel.h"

namespace UI
{
	class Button : public Panel
	{
		friend UILayout;

	public:

		Button(UI::UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement);

		void SetCallback(std::function<void(Button& button)> aOnPressed);

	private:

		std::function<void(Button& button)> myOnPressed;

	};
}