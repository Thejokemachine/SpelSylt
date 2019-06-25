#include "Client.h" 
#include "NetMessageString.h" 

void Network::CClient::Start(unsigned int aPort)
{
	CConnectionBase::Start(aPort);
}

void Network::CClient::Update()
{
	CConnectionBase::Update();

	for (SReceivedMessage& rec : myReceivedBuffer)
	{
		short type;
		rec.myPacket >> type;

		switch (static_cast<ENetMessageType>(type))
		{
		case ENetMessageType::Chat:
		{
			CNetMessageString msg;
			msg.ReceivePacket(rec.myPacket);
			msg.Unpack();
			std::cout << "Received: " + msg.GetString() << std::endl;
			break;
		}
		}
	}
}

void Network::CClient::Stop()
{
	CConnectionBase::Stop();
}

void Network::CClient::TryToConnect(const std::string& aMyName, sf::IpAddress aAddress, unsigned int aPort)
{
	myServerAddress = aAddress;
	myServerPort = aPort;

	myMessageManager.AddReceiver(aAddress, aPort);

	SStringData connectMsg;
	connectMsg.myTargetID = aAddress.toInteger();
	connectMsg.myType = ENetMessageType::Connect;
	connectMsg.myString = aMyName;

	myMessageManager.CreateMessage<CNetMessageString>(connectMsg);
}
