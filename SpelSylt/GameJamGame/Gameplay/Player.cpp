#include "Player.h"

#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

#include "GameJamGame/Core/WindowDefines.h"

#include <SpelSylt/Math/CommonMath.h>

#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/TextureAsset.h>

#include <SpelSylt/Rendering/RenderCommand.h>
#include <SpelSylt/Rendering/RenderQueue.h>

#include <SpelSylt/Utility/Input/InputManager.h>
//------------------------------------------------------------------

using namespace tree;

//------------------------------------------------------------------

CPlayer::CPlayer(SpelSylt::CAssetManager& InAssetManager, SpelSylt::IInputEventGetter& InInputManager)
	: InputManager(InInputManager)
{
	RunningAnimation = InAssetManager.GetAsset<SS::SAnimationAsset>("Graphics/Animations/player_running.anmbndl");
	RunningAnimation.setOrigin({ 32.f, 32.f });

	StandingAnimation = InAssetManager.GetAsset<SS::SAnimationAsset>("Graphics/Animations/player_standing.anmbndl");
	StandingAnimation.setOrigin({ 32.f, 32.f });

	CrosshairAnimation = InAssetManager.GetAsset<SS::SAnimationAsset>("Graphics/Animations/minigun_ch.anmbndl");
	CrosshairAnimation.setOrigin({ 32.f, 32.f });

	ArmSprite.SetTextureAsset(InAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/player_arm.png"));
	ArmSprite.setOrigin({ 3.f, 2.f });

	ShadowSprite.SetTextureAsset(InAssetManager.GetAsset<SS::STextureAsset>("Graphics/Sprites/shadow.png"));
	ShadowSprite.setOrigin({ 32.f, 32.f });
}

//------------------------------------------------------------------

void CPlayer::Tick(float InDT)
{
	CPawn::Tick(InDT);

	auto Velocity = GetController().GetVelocity();
	if (Math::Length2(Velocity) < 0.1f)
	{
		ActiveAnimation = &StandingAnimation;
	}
	else
	{
		ActiveAnimation = &RunningAnimation;
	}

	float halfWidth = 1920.f / 2.f;
	float halfHeight = 1080.f / 2.f;

	Position.x = Math::Clamp(Position.x, -halfWidth, halfWidth);
	Position.y = Math::Clamp(Position.y, -halfHeight, halfHeight);

	CrosshairAnimation.Tick(InDT);

	ActiveAnimation->Tick(InDT);
	ActiveAnimation->setPosition(Position);


	sf::Vector2f MousePos = InputManager.GetMousePosFloat();

	MousePos.x += LEFT_X;
	MousePos.y += TOP_Y;

	CrosshairAnimation.setPosition(MousePos);
	sf::Vector2f Aim = MousePos - Position;

	float RotationRad = atan2f(Aim.y, Aim.x);
	float RotationDeg = Math::ToDegrees(RotationRad);

	ArmSprite.setPosition(Position.x, Position.y - 10.f);
	ArmSprite.setRotation(RotationDeg);

	if (MousePos.x - Position.x < 0.f)
	{
		ActiveAnimation->setScale({ -1.f, 1.f });
		ArmSprite.setScale({ 1.f, -1.f });
	}
	else
	{
		ActiveAnimation->setScale({ 1.f, 1.f });
		ArmSprite.setScale({ 1.f, 1.f });
	}

	ShadowSprite.setPosition(Position.x, Position.y + 5);
}

//------------------------------------------------------------------

void CPlayer::Draw(SpelSylt::CRenderQueue& InRenderQueue)
{
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(ShadowSprite));
	if (ActiveAnimation)
	{
		InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteAnimationRenderCommand(*ActiveAnimation));
	}
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteRenderCommand(ArmSprite));
	InRenderQueue.Enqueue(ERenderLayer::UI, SS::SSpriteAnimationRenderCommand(CrosshairAnimation));
}

//------------------------------------------------------------------