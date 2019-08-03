#include "ShotGun.h"
#include "GameJamGame/Gameplay/Weapon/WeaponSystem.h"

#include <SpelSylt/Math/CommonMath.h>
#include <SpelSylt/Contexts/GameContext.h>
#include <SpelSylt/Messaging/MessageQueue.h>
#include <SpelSylt/Messaging/Messages/AudioMessages.h>
#include "GameJamGame/Core/GameMessages.h"

tree::ShotGun::ShotGun(SpelSylt::SGameContext& aGameContext) :
	IHitScanWeapon(aGameContext)
{
	myRange = 500.f;
	myTimer.SetDuration(1.f);
	myAmmo = 100;
}

void tree::ShotGun::PrepareForShoot()
{
	sf::Vector2f p = WeaponSystem->GetPlayerPos();
	sf::Vector2f a = WeaponSystem->GetAimPos();

	auto dir = a - p;
	float l = Math::Length(dir);
	sf::Vector2f spread(dir.y, -dir.x);
	Math::Normalize(spread);
	float s = 250.f * (l / 500.f);

	int shots = Math::Min(myAmmo, 15);
	if (myAmmo < 0)
		shots = 15;
	for (int i = 0; i < shots; ++i)
	{
		float amp = s * (-1.f + 2.f * ((rand() % 100) / 100.f));

		AddShot(p, a + amp * spread);
		if (myAmmo > 0)
			--myAmmo;
	}

	std::string alias = "shotgun";
	if (shots <= 0)
		alias.append("_empty");

	myContext.MessageQueue.DispatchEvent<SSoundMessage>(alias);
	myContext.MessageQueue.DispatchEvent<AmmoMsg>(myAmmo);
}
