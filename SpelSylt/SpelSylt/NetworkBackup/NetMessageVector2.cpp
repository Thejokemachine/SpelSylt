#include "NetMessageVector2.h"

void Network::CNetMessageVector2::Create(const SVector2Data & aData)
{
	CNetMessage::Create(aData);
	myData = aData;
}

void Network::CNetMessageVector2::Pack()
{
	CNetMessage::Pack();
	myPacket << myData.myVector2.x;
	myPacket << myData.myVector2.y;
}

void Network::CNetMessageVector2::Unpack()
{
	CNetMessage::Unpack();
	myPacket >> myData.myVector2.x;
	myPacket >> myData.myVector2.y;
}

sf::Vector2f Network::CNetMessageVector2::GetVector2()
{
	return std::move(myData.myVector2);
}
