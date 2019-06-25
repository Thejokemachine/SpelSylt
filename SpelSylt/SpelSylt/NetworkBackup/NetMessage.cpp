#include "NetMessage.h"

void Network::CNetMessage::Create(const SBaseData & aData)
{
	myBaseData = aData;
}

void Network::CNetMessage::Pack()
{
	myPacket << static_cast<short>(myBaseData.myType);
	myPacket << static_cast<short>(myBaseData.myType);
	myPacket << myBaseData.myTimeStamp;
	myPacket << myBaseData.myID;
	myPacket << myBaseData.myTargetID;
}

void Network::CNetMessage::Unpack()
{
	short tempType;
	myPacket >> tempType;
	myBaseData.myType = static_cast<ENetMessageType>(tempType);
	myPacket >> myBaseData.myTimeStamp;
	myPacket >> myBaseData.myID;
	myPacket >> myBaseData.myTargetID;
}

Network::SBaseData & Network::CNetMessage::GetBaseData()
{
	return myBaseData;
}

sf::Packet & Network::CNetMessage::GetPacket()
{
	return myPacket;
}

void Network::CNetMessage::ReceivePacket(const sf::Packet & aPacket)
{
	myPacket = aPacket;
}
