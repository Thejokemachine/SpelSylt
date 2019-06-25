#pragma once
#include "CommonNetworkIncludes.h"

#include "SFML/Network/Packet.hpp"

namespace Network
{
	struct SBaseData
	{
		ENetMessageType myType;
		unsigned int myTimeStamp;
		unsigned int myID;
		unsigned int myTargetID;
	};

	class CNetMessage
	{
	public:

		void Create(const SBaseData& aData);

		virtual void Pack();
		virtual void Unpack();

		SBaseData& GetBaseData();
		sf::Packet& GetPacket();
		void ReceivePacket(const sf::Packet& aPacket);

	protected:
		sf::Packet myPacket;
		SBaseData myBaseData;
	};
}