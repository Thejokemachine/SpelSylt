#pragma once

#include <iostream>
#include <string>

#include "SFML/Network.hpp"

#include "NetMessageManager.h"

#define MAX_BUFFER_SIZE 512

namespace Network
{
	enum class ENetMessageType : short
	{
		Chat,
		Ping,
		Connect
	};

	enum class ENetworkState
	{
		Singleplayer,
		Client,
		Server
	};
}