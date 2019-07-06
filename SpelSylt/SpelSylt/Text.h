#pragma once
#include "Panel.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"

namespace tinyxml2 {
	class XMLElement;
}

namespace UI
{
	class Text : public Panel
	{
		friend class UILayout;

	public:

		Text(const Panel* aParent, const std::string& aName, float x, float y, float aWidth, float aHeight, unsigned char aDockFlags, tinyxml2::XMLElement& aElement);
		virtual ~Text() = default;

		virtual void onDraw(sf::RenderTarget& aTarget) const override;

	private:
		sf::Text myText;
		sf::Font myFont;
	};
}