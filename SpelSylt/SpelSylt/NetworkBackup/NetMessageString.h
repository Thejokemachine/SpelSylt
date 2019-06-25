#pragma once
#include "NetMessage.h"

namespace Network
{
	struct SStringData : SBaseData
	{
		std::string myString;
	};

	class CNetMessageString : public CNetMessage
	{
	public:
		void Create(const SStringData& aData);

		virtual void Pack() override;
		virtual void Unpack() override;

		std::string GetString();

	private:
		SStringData myData;
	};
}