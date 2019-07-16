#pragma once
#include "SpelSylt/State/State.h"

#include "SpelSylt/Debugging/Rendering/DebugDrawer.h"
#include "SpelSylt/UI/Base/UILayout.h"

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/View.hpp"

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

#include "SpelSylt/FileHandling/Asset/Assets.h"

#include <SpelSylt/Rendering/Renderer.h>
#include <SpelSylt/Rendering/RenderQueue.h>

class HookGame : public CState 
{
public:
	HookGame();
	~HookGame();

	//Begin CState
	virtual void Init(SGameContext& InGameContext) override;
	virtual void Update(SGameContext& InGameContext) override;
	virtual void Render(sf::RenderTarget& InTarget) override;
	//End CState
private:

	sf::Vector2f myPlayerPos;
	sf::Vector2f myVelocity;
	bool myIsGrounded;
	bool myIsHooked = false;
	float myRopeLength = 300.f;

	std::vector<sf::Vector2f> myHookPoints;
	sf::Vector2f myHookPoint;
	sf::Vector2f Anchor;

	//UILayout myUI;
	bool SetTexture;
	STextureAsset TestTexture;
	sf::Sprite TestSprite;

	CRenderer myRenderer;
	CRenderQueue myRenderQueue;
	CDebugDrawer myDebugDrawer;
	sf::View myCamera;
};
