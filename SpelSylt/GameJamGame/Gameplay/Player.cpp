#include "Player.h"

#include "GameJamGame/Gameplay/Controller/ControllerInterface.h"

#include "GameJamGame/Core/WindowDefines.h"

#include <SpelSylt/Math/CommonMath.h>

#include <SpelSylt/FileHandling/Asset/AssetManager.h>
#include <SpelSylt/FileHandling/Asset/AssetTypes/AnimationAsset.h>

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
}

//------------------------------------------------------------------

void CPlayer::Tick(float InDT)
{
	CPawn::Tick(InDT);

	float halfWidth = 1920.f / 2.f;
	float halfHeight = 1080.f / 2.f;

	Position.x = Math::Clamp(Position.x, -halfWidth, halfWidth);
	Position.y = Math::Clamp(Position.y, -halfHeight, halfHeight);

	RunningAnimation.Tick(InDT);
	RunningAnimation.setPosition(Position);

	float VelocityX = GetController().GetVelocity().x;

	sf::Vector2f MousePos = InputManager.GetMousePosFloat();
	MousePos.x += LEFT_X;
	MousePos.y += TOP_Y;

	if (MousePos.x - Position.x < 0.f)
	{
		RunningAnimation.setScale({ -1.f, 1.f });
	}
	else
	{
		RunningAnimation.setScale({ 1.f, 1.f });
	}
}

//------------------------------------------------------------------

void CPlayer::Draw(SpelSylt::CRenderQueue& InRenderQueue)
{
	InRenderQueue.Enqueue(ERenderLayer::Game, SS::SSpriteAnimationRenderCommand(RunningAnimation));
}

//------------------------------------------------------------------