#pragma once

#define SMALL_STRING_LEN 16 

namespace SpelSylt
{
	class CSmallString
	{
	public:
		CSmallString();
		CSmallString(const CSmallString& InOther);
		CSmallString(const char* InCStr);

		void operator=(const CSmallString& InRHS);
		void operator=(const char* InRHS);
		bool operator==(const CSmallString& InRHS) const;

		const char* CStr() const;

		short GetLength() const;
	private:
		short Len;
		char Buffer[SMALL_STRING_LEN + 1]; //+1 to allow for null termination after the 16 characters
	};
}

namespace SS = SpelSylt;