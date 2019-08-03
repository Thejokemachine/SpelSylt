#include "Inventory.h"

#include <SpelSylt/Messaging/MessageQueue.h>
#include "GameJamGame/Core/GameMessages.h"

tree::CInventory::CInventory(SpelSylt::CMessageQueue & aMessageQueue)
{
	aMessageQueue.Subscribe<PickedUpWater>([this](const auto& msg) {
		myRefilledThisFrame = true;
		myHasWater = true;
	}, mySubs);

	aMessageQueue.Subscribe<InteractMsg>([this, &aMessageQueue](const auto& msg) {
		if (!myRefilledThisFrame && myHasWater)
		{
			myHasWater = false;
			aMessageQueue.DispatchEvent<WaterMsg>();
		}
	}, mySubs);
}

void tree::CInventory::Update(float aDT)
{
	myRefilledThisFrame = false;
}
