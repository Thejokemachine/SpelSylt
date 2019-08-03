#pragma once
#include "SpelSylt/UI/Panel.h"

#include "SpelSylt/Rendering/Text/Font.h"
#include "SpelSylt/Rendering/Text/Text.h"

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
		const sf::Color& GetTextColor() const { return myText.getFillColor(); }

		void SetText(const std::string& aText);
		void SetTextColor(const sf::Color& aColor);

		virtual void onLayout() override;

		virtual void onDraw(sf::RenderTarget& aTarget) const override;

	private:
		SS::CText myText;
		//sf::Text myText;
		unsigned char myTextAlignFlags = 0;
	};
}