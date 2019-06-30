#pragma once

typedef unsigned char RawByte;

class CStaticMemoryBuffer
{
public:
	CStaticMemoryBuffer();
	CStaticMemoryBuffer(unsigned short InSize);
	~CStaticMemoryBuffer();

	//Removed constructors
	CStaticMemoryBuffer(const CStaticMemoryBuffer& InStaticMemoryBuffer) = delete;
	CStaticMemoryBuffer(CStaticMemoryBuffer&& InStaticMemoryBuffer) = delete;

	void Allocate(unsigned short InSize);
	unsigned short GetRemainingSize() const;
	void Flush();

	void* AddCustomData(const void* InStart, unsigned short InSize);

	template<typename T>
	bool CanAddType() const;

	template<typename T>
	T& AddToBuffer(const T& InData);

private:
	unsigned short NextSlot;
	unsigned short Size;
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

