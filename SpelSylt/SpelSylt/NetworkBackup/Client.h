#pragma once
#include "ConnectionBase.h"

namespace Network
{
	class CClient : public CConnectionBase
	{
	public:
		CClient() = default;
		~CClient() = default;

		void Start(unsigned int aPort) override;
		void Update() override;
		void Stop() override;

		void TryToConnect(const std::string& aMyName, sf::IpAddress aAddress, unsigned int aPort);

	private:

		sf::IpAddress myLocalAddress;
		sf::IpAddress myServerAddress;
		unsigned int myServerPort;
	};
}