#pragma once 
#include "ConnectionBase.h" 
#include <unordered_map> 

namespace Network
{
	class CServer : public CConnectionBase
	{
	public:
		CServer() = default;
		~CServer() = default;

		void Start(unsigned int aPort) override;
		void Update() override;
		void Stop() override;

		void SetName(const std::string& aName);
		void SendMessage(const std::string& aMessage);

	private:
		struct SClient
		{
			std::string myName;
			unsigned short myID;
			float myTimeSinceLatestPing;
			bool myConnected;
		};

		void AddClient(int aAddress, int aPort, const std::string& aName);
		void HandleClients();
		void DisconnectClient(SClient& aClient);

		std::string myName;
		sf::IpAddress myAddress;
		std::unordered_map<unsigned short, SClient> myClients;
	};
}