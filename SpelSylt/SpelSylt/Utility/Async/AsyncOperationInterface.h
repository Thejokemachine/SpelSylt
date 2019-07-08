#pragma once
#include <thread>

class IAsyncOperation
{
public:
	virtual void ProvideThread(std::thread& Thread) = 0;
	
	virtual void RequestShutDown() = 0;
	virtual bool HasShutDown() const = 0;
};