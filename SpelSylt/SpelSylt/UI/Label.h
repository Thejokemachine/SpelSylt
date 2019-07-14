#pragma once
#include "SpelSylt/UI/Panel.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

namespace tinyxml2 {
	class XMLElement;
}

namespace UI
{
	class UILayout;

	class Label : public Panel
	{

	public:

		Label(UILayout& aLayout, const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement);
		virtual ~Label() = default;

		void SetText(const std::string& aText);

		virtual void onLayout() override;

		virtual void onDraw(sf::RenderTarget& aTarget) const override;

	private:
		sf::Text myText;
		unsigned char myTextAlignFlags = 0;
	};
}