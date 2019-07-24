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

		//This function is deleted due to SS::CSprite working with SS::STextureAssets instead
		void setTexture(const sf::Texture& texture, bool resetRect) = delete;

		void SetTextureAsset(const STextureAsset& Asset);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		const STextureAsset* TextureAsset;
	};

}

namespace SS = SpelSylt;