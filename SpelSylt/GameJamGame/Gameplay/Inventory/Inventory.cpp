#include "Inventory.h"

#include <SpelSylt/Messaging/MessageQueue.h>
#include "GameJamGame/Core/GameMessages.h"

#include <SpelSylt/Messaging/Messages/AudioMessages.h>

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
			aMessageQueue.DispatchEvent<SSoundMessage>("water_can");
		}
	}, mySubs);
}

void tree::CInventory::Update(float aDT)
{
	myRefilledThisFrame = false;
}
