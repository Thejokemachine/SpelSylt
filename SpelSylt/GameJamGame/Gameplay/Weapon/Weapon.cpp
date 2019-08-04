#include "Weapon.h"
#include <SpelSylt/Math/CommonMath.h>

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

int tree::IWeapon::AddAmmo(int aAmmo)
{
	myAmmo = Math::Min(999, myAmmo + aAmmo);
	return myAmmo;
}
