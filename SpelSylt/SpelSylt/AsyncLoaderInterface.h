#pragma once

struct SBaseAsset;
struct SLoadRequestTicket;

class IAsyncLoader
{
public:
	virtual const SLoadRequestTicket* LoadAsync(const char* Path, SBaseAsset& InTo) = 0;
	//virtual void ReturnTicket(const SLoadRequestTicket& InTicket) = 0;
	virtual void HandInTicket(const SLoadRequestTicket*& InTicket) = 0;
};