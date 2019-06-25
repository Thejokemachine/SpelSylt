#include "NetMessageManager.h"

#include "NetMessage.h"

#include "NetMessageString.h"

Network::CNetMessageManager::CNetMessageManager(sf::UdpSocket & aSocket) : mySocket(aSocket)
{
}

void Network::CNetMessageManager::AddReceiver(sf::IpAddress aAddress, unsigned short aPort)
{
	SReceiverPair rp;
	rp.myAddress = aAddress;
	rp.myPort = aPort;
	myAddresses.insert(std::make_pair(aAddress.toInteger(), rp));
}

unsigned int Network::CNetMessageManager::Flush()
{
	unsigned int bytesSent = 0;

	for (CNetMessage*& msg : myMessages)
	{
		if (myAddresses.find(msg->GetBaseData().myTargetID) == myAddresses.end())
		{
			continue;
		}

		msg->Pack();

		SReceiverPair& rp = myAddresses[msg->GetBaseData().myTargetID];

		mySocket.send(msg->GetPacket(), rp.myAddress, rp.myPort);

		delete msg;
	}

	myMessages.clear();

	return 0;
}
