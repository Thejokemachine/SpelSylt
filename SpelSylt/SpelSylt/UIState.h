#pragma once
#include "State.h"
#include "UILayout.h"

#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/RenderTexture.hpp"

class UIState : public CState
{
public:
	UIState(unsigned int aWidth, unsigned int aHeight);
	~UIState() = default;

	virtual void Init() override;
	virtual void Update(SGameContext& InGameContext) override;
	virtual void Render(SRenderingContext& InRenderingContext) override;
private:
	
	sf::Sprite mySprite;
	sf::RenderTexture myTexture;

	UI::UILayout myLayout;
};