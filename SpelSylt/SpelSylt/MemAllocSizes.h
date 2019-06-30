#pragma once

struct B
{
public:
	B(unsigned int InAmount)
		: Amount(InAmount)
	{};

	explicit operator unsigned int() const
	{
		return Amount;
	}

	explicit operator unsigned long long() const
	{
		return static_cast<unsigned long long>(Amount);
	}

	B operator -(const B& InRHS) const
	{
		return B(Amount - InRHS.Amount);
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
	unsigned int Amount;
};

static B operator ""_mb(unsigned long long InMegabyte)
{
	return B(static_cast<unsigned int>(InMegabyte << 20));
}

static B operator ""_gb(unsigned long long InGigabyte)
{
	return B(static_cast<unsigned int>(InGigabyte << 30));
}