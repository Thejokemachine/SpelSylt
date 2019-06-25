#pragma once

#include "CommonNetworkIncludes.h"

#include <vector>
#include <unordered_map>

namespace Network
{
	class CNetMessage;

	class CNetMessageManager
	{
	public:
		CNetMessageManager(sf::UdpSocket& aSocket);

		template<typename Type, typename TypeData>
		void CreateMessage(TypeData& aMessageData);

		void AddReceiver(sf::IpAddress aAddress, unsigned short aPort);
		unsigned int Flush();

	private:
		sf::UdpSocket& mySocket;

		std::vector<CNetMessage*> myMessages;

		struct SReceiverPair
		{
			sf::IpAddress myAddress;
			unsigned short myPort;
		};
		std::unordered_map<int, SReceiverPair> myAddresses;
	};

	template<typename Type, typename TypeData>
	inline void CNetMessageManager::CreateMessage(TypeData & aMessageData)
	{
		Type* newMessage = new Type();
		newMessage->Create(aMessageData);

		myMessages.push_back(newMessage);
	}
}