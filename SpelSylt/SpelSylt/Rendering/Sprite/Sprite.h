#pragma once
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct STextureAsset;

namespace sf
{
	class Texture;
	class RenderTarget;
	class RenderStates;
}

namespace SpelSylt
{
	class CSprite
		: public sf::Sprite
	{
	public:
		CSprite();

		void SetTextureAsset(const STextureAsset& Asset);
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		const STextureAsset* TextureAsset;
	};

}

namespace SS = SpelSylt;