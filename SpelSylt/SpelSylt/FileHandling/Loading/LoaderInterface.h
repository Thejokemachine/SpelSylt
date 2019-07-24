#pragma once

struct SBaseAsset;
struct SLoadRequestTicket;

class ILoader
{
public:
	virtual void Load(const char* Path, SBaseAsset& InTo) = 0;
};