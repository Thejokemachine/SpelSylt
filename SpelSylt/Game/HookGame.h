#pragma once
#include "SpelSylt/GameState2D.h"

#include "SFML/System/Vector2.hpp"
#include "SFML/Graphics/View.hpp"

#include "SpelSylt/FileHandling/Asset/Assets.h"

namespace sf {
	class RenderTarget;
}

class CRenderQueue;


class HookGame : public GameState2D 
{
public:
	HookGame();
	~HookGame();

	//Begin CState
	virtual void OnInit(SGameContext& InGameContext) override;
	virtual void OnUpdate(SGameContext& InGameContext) override;
	virtual void OnRender(CRenderQueue& InRenderQueue) override;
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

	float myRotation = 0.f;
	float myTargetRotation = 0.f;

	sf::Sprite myPlayer;
	sf::Sprite myRope;

	STextureAsset myPlayerTexture;
	STextureAsset myPlayerHookedTexture;
	STextureAsset myRopeTexture;
	STextureAsset myHookPointTexture;
	STextureAsset myFloorTexture;
};
