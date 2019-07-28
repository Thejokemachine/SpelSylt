#pragma once
#include <SFML/Graphics/Text.hpp>
#include <string>

namespace sf
{
	class Texture;
	class RenderTarget;
	class RenderStates;
}

namespace SpelSylt
{
	struct SFontAsset;

	class CText
		: public sf::Text
	{
	public:
		CText();

		//This function is deleted due to SS::CText working with SS::SFontAssets instead
		void setFont(const sf::Font& font) = delete;
		void setString(const sf::String& string) = delete;

		void SetString(const char* InString);

		void SetFontAsset(const SFontAsset& Asset);

		virtual void draw(sf::RenderTarget& InTarget, sf::RenderStates InStates) const override;
	private:
		const SFontAsset* FontAsset;
		std::string TextString;
	};
}

namespace SS = SpelSylt;
