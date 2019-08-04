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
DEFINE_MSG_ONEPARAM(WaterLevelMsg, float)

DEFINE_MSG_ONEPARAM(TreeLevelMsg, int)

// Weapon messages
DEFINE_MSG_ONEPARAM(FireWeaponMsg, sf::Vector2f)
DEFINE_MSG_ONEPARAM(SwitchWeaponMsg, int)

DEFINE_MSG_ONEPARAM(ShotgunAmmoMsg, int)
DEFINE_MSG_ONEPARAM(MinigunAmmoMsg, int)
DEFINE_MSG_ONEPARAM(GrenadeAmmoMsg, int)

using FHitscanMessageParam = std::pair<sf::Vector2f, sf::Vector2f>;
DEFINE_MSG_ONEPARAM(HitscanShotMsg, FHitscanMessageParam)
DEFINE_MSG_TWOPARAM(HitscanExplosionMsg, sf::Vector2f, float)


//Enemy messages
DEFINE_MSG(TreeAttackedMsg)

DEFINE_MSG_TWOPARAM(EnemyKilledMsg, int, sf::Vector2f)
