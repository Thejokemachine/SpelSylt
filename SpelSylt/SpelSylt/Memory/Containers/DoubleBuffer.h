#pragma once
#include <vector>

namespace SpelSylt
{
	template <typename TElementType>
	class CDoubleBuffer
	{
	public:
		CDoubleBuffer();
		void Swap();

		std::vector<TElementType>& GetReadBuffer();
		std::vector<TElementType>& GetWriteBuffer();
		size_t GetWriteBufferSize() const;
		size_t GetReadBufferSize() const;
	private:
		std::vector<TElementType> Buffers[2];
		std::vector<TElementType> V1;
		std::vector<TElementType> V2;

		unsigned short CurrentWriteBuffer;
		unsigned short CurrentReadBuffer;
	};
}

namespace SS = SpelSylt;

//------------------------------------------------------------------

template <typename TElementType>
SpelSylt::CDoubleBuffer<TElementType>::CDoubleBuffer()
	: CurrentWriteBuffer(0)
	, CurrentReadBuffer(1)
{
	Buffers[0].reserve(200);
	Buffers[1].reserve(200);
}

//------------------------------------------------------------------

template<typename TElementType>
void SpelSylt::CDoubleBuffer<TElementType>::Swap()
{
	const unsigned short PreviousWriteBuffer = CurrentWriteBuffer;
	CurrentWriteBuffer = CurrentReadBuffer;
	CurrentReadBuffer = PreviousWriteBuffer;
}

//------------------------------------------------------------------

template<typename TElementType>
std::vector<TElementType>& SpelSylt::CDoubleBuffer<TElementType>::GetWriteBuffer()
{
	return Buffers[CurrentWriteBuffer];
}

//------------------------------------------------------------------

template<typename TElementType>
std::vector<TElementType>& SpelSylt::CDoubleBuffer<TElementType>::GetReadBuffer()
{
	//return V2;
	return Buffers[CurrentReadBuffer];
}

//------------------------------------------------------------------

template<typename TElementType>
inline size_t SpelSylt::CDoubleBuffer<TElementType>::GetWriteBufferSize() const
{
	return Buffers[CurrentWriteBuffer].size();
}

//------------------------------------------------------------------

template<typename TElementType>
inline size_t SpelSylt::CDoubleBuffer<TElementType>::GetReadBufferSize() const
{
	return Buffers[CurrentReadBuffer].size();
}

//------------------------------------------------------------------
