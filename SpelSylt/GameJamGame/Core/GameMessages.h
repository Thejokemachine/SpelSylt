#pragma once
#include <SpelSylt/Messaging/Messages/BaseMessage.h>
#include <SFML/System/Vector2.hpp>
#include <utility>

DEFINE_MSG(InteractMsg)

// Water messages
DEFINE_MSG(PickedUpWater)
DEFINE_MSG(WaterMsg)
DEFINE_MSG(ShowWaterPrompt)
DEFINE_MSG(HideWaterPrompt)

// Weapon messages
DEFINE_MSG_ONEPARAM(FireWeaponMsg, sf::Vector2f)
DEFINE_MSG_ONEPARAM(SwitchWeaponMsg, int)

DEFINE_MSG_ONEPARAM(AmmoMsg, int)

using FHitscanMessageParam = std::pair<sf::Vector2f, sf::Vector2f>;
DEFINE_MSG_ONEPARAM(HitscanShotMsg, FHitscanMessageParam)


//Enemy messages
DEFINE_MSG(TreeAttackedMsg)
