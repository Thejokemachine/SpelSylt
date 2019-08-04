#pragma once

#include "SpelSylt/Rendering/Sprite/Sprite.h"
#include "SpelSylt/Rendering/Animation/SpriteAnimation.h"
#include "SpelSylt/Rendering/Text/Text.h"

#include <SFML/Graphics/BlendMode.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Texture.hpp>

namespace SpelSylt
{
	enum class ECommandType
	{
		None, //Should never be used!
		Sprite,
		Text,
		Animation,
		SFTexture,
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

	struct STextRenderCommand final
		: public IRenderCommand
	{
		STextRenderCommand()
			: Text()
		{
		}

		explicit STextRenderCommand(const SS::CText& InText)
			: Text(InText)
		{
		}

		virtual ECommandType GetCommandType() const override
		{
			return ECommandType::Text;
		};

		virtual const sf::Drawable& GetRaw() const override
		{
			return Text;
		}

	private:
		SS::CText Text;
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

	//HAX REMOVE AFTER JAM
	struct SSFSpriteRenderCommand final
		: public IRenderCommand
	{
		SSFSpriteRenderCommand()
			: Sprite()
		{
		}

		explicit SSFSpriteRenderCommand(const sf::Texture& InTexture)
			: Sprite()
		{
			Sprite.setTexture(InTexture);
			Sprite.setOrigin(1920.f / 2.f, 1080.f / 2.f);
		}

		virtual ECommandType GetCommandType() const override
		{
			return ECommandType::SFTexture;
		};

		virtual const sf::Drawable& GetRaw() const override
		{
			return Sprite;
		}

	private:
		sf::Sprite Sprite;
	};

}

namespace SS = SpelSylt;