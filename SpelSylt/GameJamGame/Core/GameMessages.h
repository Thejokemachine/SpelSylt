#pragma once
#include <SpelSylt/Messaging/Messages/BaseMessage.h>
#include <SFML/System/Vector2.hpp>

DEFINE_MSG(InteractMsg)

// Water messages
DEFINE_MSG(PickedUpWater)
DEFINE_MSG(WaterMsg)
DEFINE_MSG(ShowWaterPrompt)
DEFINE_MSG(HideWaterPrompt)

// Weapon messages
DEFINE_MSG_ONEPARAM(FireWeaponMsg, sf::Vector2f)
DEFINE_MSG_ONEPARAM(SwitchWeaponMsg, int)
