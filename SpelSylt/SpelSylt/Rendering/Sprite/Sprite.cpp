#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Rendering/Sprite/Sprite.h"

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace SpelSylt;

//------------------------------------------------------------------

CSprite::CSprite()
	: TextureAsset(nullptr)
{

}

//------------------------------------------------------------------

void SpelSylt::CSprite::SetTextureAsset(const STextureAsset& Asset)
{
	TextureAsset = &Asset;
}

//------------------------------------------------------------------

const sf::Texture * SpelSylt::CSprite::GetTexture(int InTextureID) const
{
	switch (InTextureID)
	{
	case 0:
		return TextureAsset;
		break;
	case 1:
		return &TextureAsset->GetNormalMap();
		break;
	default:
		return nullptr;
		break;
	}
}

//------------------------------------------------------------------

void SpelSylt::CSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Drawable* Drawable = nullptr;
	sf::Sprite Sprite;
	sf::RectangleShape RectShape;

	if (TextureAsset->GetLoadStatus() == ELoadRequestStatus::Done)
	{
		Sprite.setTexture(*TextureAsset, true);
		Sprite.setPosition(getPosition());
		Sprite.setOrigin(getOrigin());
		Sprite.setScale(getScale());
		Sprite.setRotation(getRotation());
		Sprite.setColor(sf::Color::White);
		Drawable = &Sprite;
	}
	else
	{
		RectShape.setSize(sf::Vector2f(64.f, 64.f));
		RectShape.setFillColor(sf::Color::Red);
		RectShape.setPosition(getPosition());
		Drawable = &RectShape;
	}

	target.draw(*Drawable, states);
}

//------------------------------------------------------------------
