#include "WeaponSystem.h"
#include <SpelSylt/Messaging/MessageQueue.h>
#include <SpelSylt/Debugging/Rendering/DebugDrawer.h>

#include "GameJamGame/Core/GameMessages.h"

#include <SpelSylt/Contexts/GameContext.h>

#include "GameJamGame/Gameplay/Weapon/ShotGun.h"

tree::CWeaponSystem::CWeaponSystem(SpelSylt::CDebugDrawer & aDebugDrawer, SpelSylt::SGameContext& aGameContext, const CPawn & aPlayerPawn) :
	myDebugDrawer(aDebugDrawer),
	myPlayerPawn(aPlayerPawn),
	myWeapons{ std::make_unique<ShotGun>(aGameContext) }
{
	for (auto& weapon : myWeapons)
		weapon->SetWeaponSystem(this);

	aGameContext.MessageQueue.Subscribe<FireWeaponMsg>([this](const auto& msg) {
		myAimPos = msg.Param - sf::Vector2f(0.5f*1920.f, 0.5f*1080.f);
		if (myWeapons[0]->CanFire())
			myWeapons[0]->Shoot();
		//myDebugDrawer.DrawLine(myPlayerPawn.GetPosition(), msg.Param - sf::Vector2f(0.5f*1920.f,0.5f*1080.f), sf::Color::Red);
	}, mySubs);

	aGameContext.MessageQueue.Subscribe<SwitchWeaponMsg>([this](const auto& msg) {
		SwitchWeapon(msg.Param);
	}, mySubs);
}

void tree::CWeaponSystem::Update(float aDT)
{
	myWeapons[0]->Update(aDT);
}

void tree::CWeaponSystem::Render(SpelSylt::CRenderQueue & aRenderQueue)
{
	myWeapons[0]->Render(aRenderQueue);
}

void tree::CWeaponSystem::SwitchWeapon(int aID)
{

}