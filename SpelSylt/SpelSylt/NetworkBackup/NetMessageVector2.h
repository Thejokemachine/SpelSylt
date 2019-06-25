#pragma once
#include "NetMessage.h"

namespace Network
{
	struct SVector2Data : SBaseData
	{
		sf::Vector2f myVector2;
	};

	class CNetMessageVector2 : public CNetMessage
	{
	public:
		void Create(const SVector2Data& aData);

		virtual void Pack() override;
		virtual void Unpack() override;

		sf::Vector2f GetVector2();

	private:
		SVector2Data myData;
	};
}