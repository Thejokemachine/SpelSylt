#pragma once
#include "State.h"

#include "RenderCommand.h"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

class CRenderingTestState final
	: public CState
{
public:
	CRenderingTestState();

	//Begin CState
	virtual void Init() override;
	virtual void Update(float InDT) override;
	virtual void Render(SRenderingContext& InRenderingContext) override;
	//End CState
private:
	sf::Texture TestSpriteTexture;
	sf::Sprite TestSprite;
};