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

void SpelSylt::CSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Drawable* Drawable = nullptr;
	sf::Sprite Sprite;
	sf::RectangleShape RectShape;

	if (TextureAsset && TextureAsset->GetLoadStatus() == ELoadRequestStatus::Done)
	{
		Sprite = *this;
		Sprite.setTexture(*TextureAsset, true);
		//Sprite.setPosition(getPosition());
		//Sprite.setOrigin(getOrigin());
		//Sprite.setScale(getScale());
		//Sprite.setRotation(getRotation());
		//Sprite.setColor(sf::Color::White);
		if (getTextureRect().width > 0) { Sprite.setTextureRect(getTextureRect()); }
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
