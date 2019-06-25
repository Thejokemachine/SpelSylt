#include "ConnectionBase.h"
#include "Time.h"

Network::CConnectionBase::CConnectionBase() : myMessageManager(mySocket)
{
	myIsActive = false;
}

void Network::CConnectionBase::Start(unsigned int aPort)
{
	sf::Socket::Status error = mySocket.bind(aPort);
	mySocket.setBlocking(false);
	myIsActive = true;
}

void Network::CConnectionBase::Update()
{
	if (myIsActive)
	{
		myReceivedBuffer.clear();

		sf::Packet packet;
		sf::IpAddress from;
		unsigned short port = 0;

		while (mySocket.receive(packet, from, port) == sf::Socket::AnyPort)
		{
			myReceivedBuffer.push_back(SReceivedMessage());
			myReceivedBuffer.back().myPacket = packet;
			myReceivedBuffer.back().myFromAddress = from;
			myReceivedBuffer.back().myFromPort = port;
		}

		mySentThisSecond += myMessageManager.Flush();
		mySentTimer += CTime::GetInstance().GetDeltaTime();

		if (mySentTimer >= 1.0f)
		{
			mySentTimer = 0.f;
			//PRINT SENT THIS SECOND
			mySentThisSecond = 0;
		}
	}
}

void Network::CConnectionBase::Stop()
{
	myIsActive = false;
}

bool Network::CConnectionBase::IsActive()
{
	return myIsActive;
}

Network::CNetMessageManager & Network::CConnectionBase::GetMessageManager()
{
	return myMessageManager;
}
