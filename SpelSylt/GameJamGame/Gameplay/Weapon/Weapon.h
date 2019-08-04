#pragma once

#include <SpelSylt/Utility/TimedEvent.h>

namespace SpelSylt
{
	class CRenderQueue;
	class CAssetManager;
	struct SGameContext;
}

namespace tree
{
	class CWeaponSystem;

	class IWeapon
	{
	public:
		IWeapon(SpelSylt::SGameContext& aGameContext);

		virtual void Update(float aDt);
		virtual void Render(SpelSylt::CRenderQueue& aRenderQueue) {}
		virtual void Shoot() = 0;

		void SetWeaponSystem(CWeaponSystem* aWeaponSystem);

		int AddAmmo(int aAmmo);
		bool CanFire() const { return myCanFire; };

		virtual void OnActivated() {};

	protected:
		bool myCanFire;
		int myAmmo;
		SpelSylt::SGameContext& myContext;

		CTimedEvent myTimer;
		CWeaponSystem* WeaponSystem = nullptr;
	};
}