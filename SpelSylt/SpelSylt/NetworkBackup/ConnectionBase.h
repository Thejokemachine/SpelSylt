#pragma once
#include "CommonNetworkIncludes.h"

namespace Network
{
	class CConnectionBase
	{
	public:
		CConnectionBase();

		virtual void Start(unsigned int aPort);
		virtual void Update();
		virtual void Stop();

		bool IsActive();

		CNetMessageManager& GetMessageManager();
	protected:

		struct SReceivedMessage
		{
			sf::Packet myPacket;
			sf::IpAddress myFromAddress;
			unsigned short myFromPort;
		};

		sf::UdpSocket mySocket;

		unsigned int mySentThisSecond;
		float mySentTimer;

		CNetMessageManager myMessageManager;
		std::vector<SReceivedMessage> myReceivedBuffer;
		bool myIsActive;
	};
}