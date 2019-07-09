#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Memory/Containers/StaticMemoryBuffer.h"

//------------------------------------------------------------------

CStaticMemoryBuffer::CStaticMemoryBuffer()
	: NextSlot(0)
	, Size(0)
	, Buffer(nullptr)
{
}

//------------------------------------------------------------------

CStaticMemoryBuffer::CStaticMemoryBuffer(B InSize)
	: NextSlot(0)
	, Size(0)
	, Buffer(nullptr)
{
	Allocate(InSize);
}

//------------------------------------------------------------------

CStaticMemoryBuffer::~CStaticMemoryBuffer()
{
	delete[Size] Buffer;
}

//------------------------------------------------------------------

void CStaticMemoryBuffer::Allocate(B InSize)
{
	Size = InSize;
	Buffer = new RawByte[static_cast<unsigned int>(Size)];
}

//------------------------------------------------------------------

B CStaticMemoryBuffer::GetRemainingSize() const
{
	return Size - NextSlot;
}

//------------------------------------------------------------------

void CStaticMemoryBuffer::Flush()
{
	NextSlot = 0;
}

//------------------------------------------------------------------

void* CStaticMemoryBuffer::AddCustomData(const void* InStart, unsigned short InSize)
{
	memcpy(&Buffer[NextSlot], InStart, InSize);
	void* Added = reinterpret_cast<void*>(&Buffer[NextSlot]);
	NextSlot += InSize;
	return Added;
}

//------------------------------------------------------------------