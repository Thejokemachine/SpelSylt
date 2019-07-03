#pragma once

struct SBaseAsset;
struct SLoadRequestTicket;

class IAsyncLoader
{
public:
	virtual void LoadAsync(const char* Path, SBaseAsset& InTo) = 0;
	//virtual void ReturnTicket(const SLoadRequestTicket& InTicket) = 0;
};