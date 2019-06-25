#include "Server.h"
#include "Time.h"
#include "NetMessageString.h"

void Network::CServer::Start(unsigned int aPort)
{
	CConnectionBase::Start(aPort);
}

void Network::CServer::Update()
{
	CConnectionBase::Update();
	float dt = CTime::GetInstance().GetDeltaTime();

	HandleClients();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		short type;
		rec.myPacket >> type;

		switch (static_cast<ENetMessageType>(type))
		{
		case ENetMessageType::Connect:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			AddClient(rec.myFromAddress.toInteger(), rec.myFromPort, msg.GetString());
			break;
		}
		case ENetMessageType::Chat:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			std::cout << "Received: " << msg.GetString() << std::endl;
			break;
		}
		}
	}
}

void Network::CServer::Stop()
{
	CConnectionBase::Stop();
}

void Network::CServer::SetName(const std::string & aName)
{
	myName = aName;
}

void Network::CServer::SendMessage(const std::string & aMessage)
{
	Network::SStringData msg;
	msg.myString = aMessage;
	msg.myTargetID = 0;
	msg.myType = Network::ENetMessageType::Chat;
	msg.myTimeStamp = 1337;
	msg.myID = 777;

	myMessageManager.CreateMessage<CNetMessageString>(msg);
}

void Network::CServer::AddClient(int aAddress, int aPort, const std::string& aName)
{
	SClient nClient;
	nClient.myConnected = true;
	nClient.myID = aAddress;
	nClient.myName = aName;
	nClient.myTimeSinceLatestPing = 0.f;

	myClients.insert(std::make_pair(aAddress, nClient));
	myMessageManager.AddReceiver(sf::IpAddress(aAddress), aPort);

	std::cout << "Client " << aName << " connected!" << std::endl;
}

void Network::CServer::HandleClients()
{
}

void Network::CServer::DisconnectClient(SClient & aClient)
{
}