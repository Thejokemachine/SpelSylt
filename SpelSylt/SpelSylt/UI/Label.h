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

		Label(UILayout& aLayout, const Panel* aParent, tinyxml2::XMLElement& aElement);
		virtual ~Label() = default;

		//float GetWidth() const override { return myText.getLocalBounds().width + myText.getLocalBounds().left; }
		//float GetHeight() const override { return myText.getLocalBounds().height + myText.getLocalBounds().top; }
		std::string GetText() const { return myText.getString(); }

		void SetText(const std::string& aText);

		virtual void onLayout() override;

		virtual void onDraw(sf::RenderTarget& aTarget) const override;

	private:
		sf::Text myText;
		unsigned char myTextAlignFlags = 0;
	};
}