#include "Weapon.h"

tree::IWeapon::IWeapon(SpelSylt::SGameContext& aGameContext) :
	myContext(aGameContext),
	myCanFire(true),
	myAmmo(-1)
{
	myTimer.Init(CTimedEvent::EType::Repeat, 0.f, [this]() {
		myCanFire = true;
	});
	myTimer.Start();
}

void tree::IWeapon::Update(float aDt)
{
	myTimer.Update(aDt);
}

void tree::IWeapon::SetWeaponSystem(CWeaponSystem * aWeaponSystem)
{
	WeaponSystem = aWeaponSystem;
}
