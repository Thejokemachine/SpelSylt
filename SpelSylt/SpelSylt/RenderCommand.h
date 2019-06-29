#pragma once

#include <SFML/Graphics/Sprite.hpp>

struct IRenderCommand
{
	virtual const sf::Drawable& GetRaw() const = 0;
};


//Note: For now this is just a pure sf::Sprite
//This might change based on requirements later
struct SSpriteRenderCommand final
	: public IRenderCommand
{
	SSpriteRenderCommand()
		: Sprite()
	{

	}

	SSpriteRenderCommand(const sf::Sprite& InSFSprite)
		: Sprite(InSFSprite)
	{
	}

	virtual const sf::Sprite& GetRaw() const override
	{
		return Sprite;
	}

private:
	sf::Sprite Sprite;
};