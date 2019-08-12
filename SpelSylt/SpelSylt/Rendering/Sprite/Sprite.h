#pragma once
#include <SFML/Graphics/Sprite.hpp>

namespace sf
{
	class Texture;
	class RenderTarget;
	class RenderStates;
}

namespace SpelSylt
{
	struct STextureAsset;
	
	class CSprite
		: public sf::Sprite
	{
	public:
		CSprite();

		void operator=(const CSprite& InRHS);
		void operator=(const STextureAsset& InRHS);

		//This function is deleted due to SS::CSprite working with SS::STextureAssets instead
		void setTexture(const sf::Texture& texture, bool resetRect) = delete;
		
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		const STextureAsset* TextureAsset;
	};

}

namespace SS = SpelSylt;