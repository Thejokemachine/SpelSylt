#include "NetMessageString.h"
#include "NetMessageVector2.h"

void Network::CNetMessageString::Create(const SStringData & aData)
{
	CNetMessage::Create(aData);
	myData = aData;
}

void Network::CNetMessageString::Pack()
{
	CNetMessage::Pack();
	myPacket << myData.myString;
}

void Network::CNetMessageString::Unpack()
{
	CNetMessage::Unpack();
	myPacket >> myData.myString;
}

std::string Network::CNetMessageString::GetString()
{
	return std::move(myData.myString);
}
