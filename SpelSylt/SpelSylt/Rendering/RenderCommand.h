#pragma once

#include "SpelSylt/Rendering/Sprite/Sprite.h"

enum class ECommandType
{
	None, //Should never be used!
	Sprite,
};

struct IRenderCommand
{
	virtual ECommandType GetCommandType() const = 0; 
	virtual const sf::Drawable& GetRaw() const = 0;
	virtual const sf::Texture* GetTexture(int InTextureID) const = 0;
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

	SSpriteRenderCommand(const SS::CSprite& InSFSprite)
		: Sprite(InSFSprite)
	{
	}

	virtual ECommandType GetCommandType() const override
	{
		return ECommandType::Sprite;
	};

	virtual const sf::Drawable& GetRaw() const override
	{
		return Sprite;
	}

	virtual const sf::Texture* GetTexture(int InTextureID) const override
	{
		return Sprite.GetTexture(InTextureID);
	}

private:
	SS::CSprite Sprite;
};