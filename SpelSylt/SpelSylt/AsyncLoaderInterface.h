#pragma once

struct SRawAsset;
struct SLoadRequestTicket;

class IAsyncLoader
{
public:
	virtual const SLoadRequestTicket* LoadAsync(const char* Path) = 0;
	//virtual void ReturnTicket(const SLoadRequestTicket& InTicket) = 0;
	virtual void HandInTicket(const SLoadRequestTicket*& InTicket, SRawAsset& OutLoadedAsset) = 0;
};