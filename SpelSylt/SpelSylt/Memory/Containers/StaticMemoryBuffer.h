#pragma once
#include <new>
#include "SpelSylt/Memory/MemAllocSizes.h"

typedef unsigned char RawByte;

class CStaticMemoryBuffer
{
public:
	CStaticMemoryBuffer();
	CStaticMemoryBuffer(B InSize);
	~CStaticMemoryBuffer();

	//Removed constructors
	CStaticMemoryBuffer(const CStaticMemoryBuffer& InStaticMemoryBuffer) = delete;
	CStaticMemoryBuffer(CStaticMemoryBuffer&& InStaticMemoryBuffer) = delete;

	void Allocate(B InSize);
	B GetRemainingSize() const;
	void Flush();

	void* AddCustomData(const void* InStart, unsigned short InSize);

	template<typename T>
	bool CanAddType() const;

	template<typename T>
	T& AddToBuffer(const T& InData);

	template<typename T, typename ... TArgs>
	T& EmplaceToBuffer(TArgs ...);

private:
	unsigned int NextSlot;
	B Size;
	RawByte* Buffer;
};

//------------------------------------------------------------------

template<typename T>
inline bool CStaticMemoryBuffer::CanAddType() const
{
	return sizeof(T) <= GetRemainingSize();
}

//------------------------------------------------------------------

template<typename T>
inline T& CStaticMemoryBuffer::AddToBuffer(const T& InData)
{
	memcpy(&Buffer[NextSlot], &InData, sizeof(T));
	T* Added = reinterpret_cast<T*>(&Buffer[NextSlot]);
	NextSlot += sizeof(T);

	return *Added;
}

//------------------------------------------------------------------

template<typename T, typename ...TArgs>
inline T& CStaticMemoryBuffer::EmplaceToBuffer(TArgs ... InArgs)
{
	T* TPtr = new(&Buffer[NextSlot]) T(InArgs...);
	NextSlot += sizeof(T);
	return *TPtr;
}

//------------------------------------------------------------------

