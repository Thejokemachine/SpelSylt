#pragma once

#include "SpelSylt/Rendering/Sprite/Sprite.h"
#include "SpelSylt/Rendering/Animation/SpriteAnimation.h"

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Shader.hpp>

namespace SpelSylt
{
	enum class ECommandType
	{
		None, //Should never be used!
		Sprite,
		Animation,
	};

	struct SRenderState
	{
		sf::BlendMode BlendMode = sf::BlendAlpha;
		sf::Shader* Shader = nullptr;
	};

	struct IRenderCommand
	{
		virtual ECommandType GetCommandType() const = 0;
		virtual const sf::Drawable& GetRaw() const = 0;

		SRenderState RenderState;
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

	private:
		SS::CSprite Sprite;
	};

	struct SSpriteAnimationRenderCommand final
		: public IRenderCommand
	{
		SSpriteAnimationRenderCommand()
			: Animation()
		{
		}

		explicit SSpriteAnimationRenderCommand(const SS::CSpriteAnimation& InAnimation)
			: Animation(InAnimation)
		{
		}

		virtual ECommandType GetCommandType() const override
		{
			return ECommandType::Animation;
		};

		virtual const sf::Drawable& GetRaw() const override
		{
			return Animation;
		}

	private:
		SS::CSpriteAnimation Animation;
	};
}

namespace SS = SpelSylt;