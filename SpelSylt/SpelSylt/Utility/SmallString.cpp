#include "SpelSylt/SpelSyltPCH.h"

#include "SpelSylt/Utility/SmallString.h"

//------------------------------------------------------------------

#define NULL_TERMINATOR_CHAR 0x00

//------------------------------------------------------------------

SpelSylt::CSmallString::CSmallString()
	: Len(0)
	, Buffer()
{
	Buffer[0] = NULL_TERMINATOR_CHAR;
}

//------------------------------------------------------------------

SpelSylt::CSmallString::CSmallString(const CSmallString& InOther)
	: Len(0)
	, Buffer()
{
	operator=(InOther);
}

//------------------------------------------------------------------

SpelSylt::CSmallString::CSmallString(const char* InCStr)
	: Len(0)
	, Buffer()
{
	operator=(InCStr);
}

//------------------------------------------------------------------

void SpelSylt::CSmallString::operator=(const CSmallString& InRHS)
{
	Len = InRHS.Len;
	for (short i = 0; i < Len; ++i)
	{
		Buffer[i] = InRHS.Buffer[i];
	}
}

//------------------------------------------------------------------

void SpelSylt::CSmallString::operator=(const char* InRHS)
{
	const short CStrLen = static_cast<short>(strlen(InRHS));
	Len = CStrLen < SMALL_STRING_LEN ? CStrLen : SMALL_STRING_LEN;

	for (short i = 0; i < Len; ++i)
	{
		Buffer[i] = InRHS[i];
	}

	Buffer[Len + 1] = NULL_TERMINATOR_CHAR;
}

//------------------------------------------------------------------

bool SpelSylt::CSmallString::operator==(const CSmallString& InRHS) const
{
	if (Len != InRHS.Len)
	{
		return false;
	}

	for (short i = 0; i < Len; ++i)
	{
		if ((Buffer[0] & InRHS.Buffer[0]) == 0x00)
		{
			return false;
		}
	}

	return true;
}

//------------------------------------------------------------------

const char* SpelSylt::CSmallString::CStr() const
{
	return Buffer;
}

//------------------------------------------------------------------

short SpelSylt::CSmallString::GetLength() const
{
	return Len;
}

//------------------------------------------------------------------
