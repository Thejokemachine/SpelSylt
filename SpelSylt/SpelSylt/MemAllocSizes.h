#pragma once

struct B
{
public:
	B()
		: Amount(0)
	{}

	B(unsigned long long InAmount)
		: Amount(InAmount)
	{};

	explicit operator unsigned int() const
	{
		return static_cast<unsigned int>(Amount);
	}

	explicit operator long long() const
	{
		return static_cast<long long>(Amount);
	}

	operator unsigned long long() const
	{
		return Amount;
	}

	B operator -(const B& InRHS) const
	{
		return B(Amount - InRHS.Amount);
	}

	B operator -(unsigned int InRHS) const
	{
		return B(Amount - static_cast<B>(InRHS));
	}

	B operator +(const B& InRHS) const
	{
		return B(Amount + InRHS.Amount);
	}

	bool operator ==(const B& InRHS) const
	{
		return Amount == InRHS.Amount;
	}

	bool operator<(const B& InRHS) const
	{
		return Amount < InRHS.Amount;
	}

	bool operator>(const B& InRHS) const
	{
		return !operator<(InRHS);
	}

	bool operator <=(const B& InRHS) const
	{
		return operator<(InRHS) || operator==(InRHS);
	}

	bool operator >=(const B& InRHS) const
	{
		return operator>(InRHS) || operator==(InRHS);
	}

protected:
	unsigned long long Amount;
};

static B operator ""_mb(unsigned long long InMegabyte)
{
	return B(static_cast<unsigned int>(InMegabyte << 20));
}

static B operator ""_gb(unsigned long long InGigabyte)
{
	return B(static_cast<unsigned int>(InGigabyte << 30));
}