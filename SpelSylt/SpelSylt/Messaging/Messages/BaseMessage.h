#pragma once

struct SBaseMessage
{
	void SetMessageHash(size_t InEventHash)
	{
		EventHash = InEventHash;
	}

	size_t GetMessageHash() const
	{
		return EventHash;
	}

private:
	size_t EventHash;
};

#define DEFINE_MSG(NAME) struct NAME : public SBaseMessage { NAME(){} };
#define DEFINE_MSG_ONEPARAM(NAME, PARAMTYPE) struct NAME : public SBaseMessage { NAME(const PARAMTYPE& InParam) : Param(InParam) {} PARAMTYPE Param; };
#define DEFINE_MSG_TWOPARAM(NAME, PARAMTYPE, PARAMTYPETWO) struct NAME : public SBaseMessage { NAME(const PARAMTYPE& InParam, const PARAMTYPETWO& InParamTwo) : Param(InParam), ParamTwo(InParamTwo) {} PARAMTYPE Param; PARAMTYPETWO ParamTwo; };
#define DEFINE_MSG_THREEPARAM(NAME, PARAMTYPE, PARAMTYPETWO, PARAMTYPETHREE) struct NAME : public SBaseMessage { NAME(const PARAMTYPE& InParam, const PARAMTYPETWO& InParamTwo, const PARAMTYPETHREE& InParamThree) : Param(InParam), ParamTwo(InParamTwo), ParamThree(InParamThree) {} PARAMTYPE Param; PARAMTYPETWO ParamTwo; PARAMTYPETHREE ParamThree; };