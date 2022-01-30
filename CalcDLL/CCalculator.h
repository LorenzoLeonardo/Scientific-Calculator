#pragma once

#include <stack>
#include <string>
#include <tchar.h>
#include <vector>
using namespace std;


#ifdef _UNICODE
#define _tstring	wstring 
#define	to_tstring	to_wstring

#else
#define _tstring string 
#define	to_tstring	to_string
#endif

//Highest Priorty is Zero
typedef enum
{
	ZERO,
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE

}PRIORITY;
class CItems
{
	long double m_number;
	_tstring m_soperation;
	PRIORITY m_priority;
	bool     m_isOperator;
	bool     m_bIsDigit;
	bool     m_bIsOpenBrace;
	bool     m_bIsCloseBrace;

public:
	CItems();
	CItems(long double, _tstring oper, PRIORITY prio);
	~CItems();
	bool IsBrace(_tstring s);
	void SetPriority(PRIORITY prio)
	{
		m_priority = prio;
	}
	long double GetNumber()
	{
		return m_number;
	}
	PRIORITY GetPriority()
	{
		return m_priority;
	}
	bool IsOpenBrace()
	{
		return m_bIsOpenBrace;
	}
	bool IsCloseBrace()
	{
		return m_bIsCloseBrace;
	}
	bool IsAnOperator()
	{
		return m_isOperator;
	}
	bool IsADigit()
	{
		return m_bIsDigit;
	}
	bool IsOperator(_tstring s);

	void SetOperation(_tstring op)
	{
		m_soperation = op;
	}

	_tstring GetOperation()
	{
		return m_soperation;
	}

	CItems operator=(const CItems& b)
	{
		this->m_number = b.m_number;
		this->m_soperation = b.m_soperation;
		this->m_priority = b.m_priority;
		this->m_isOperator = b.m_isOperator;
		this->m_bIsDigit = b.m_bIsDigit;
		this->m_bIsOpenBrace = b.m_bIsOpenBrace;
		this->m_bIsCloseBrace = b.m_bIsCloseBrace;
		return *this;
	}
	CItems operator+=(const CItems& b)
	{
		this->m_number = this->m_number + b.m_number;
		return *this;
	}
	CItems operator-=(const CItems& b)
	{
		this->m_number = this->m_number - b.m_number;
		return *this;
	}
	CItems operator*=(const CItems& b)
	{
		this->m_number = this->m_number * b.m_number;
		return *this;
	}
	CItems operator/=(const CItems& b)
	{
		this->m_number = this->m_number / b.m_number;
		return *this;
	}
	CItems operator+(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number + b.m_number;
		return ans;
	}

	CItems operator-(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number - b.m_number;
		return ans;
	}
	CItems operator*(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number * b.m_number;
		return ans;
	}
	CItems operator/(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number / b.m_number;
		return ans;
	}
};


class CCalculator
{
private:
	stack<CItems> m_stack;
	vector<CItems> m_postfix;
	vector<CItems> m_infix;

	_tstring m_input;
	bool m_bCorrectSyntax;
	
	inline _tstring RemoveSpaces(_tstring sMain);
	inline _tstring InsertWithin(_tstring sMain, _tstring substring, _tstring c);
	inline _tstring InsertBothEnd(_tstring sMain, _tstring c, _tstring d);
	inline PRIORITY GetPriorityNumber(TCHAR c);
	void ParseInput();
	bool IsBalanced(_tstring s);
	bool IsOperator(TCHAR s);
	bool IsAlphaNumBrace(_tstring s);
	void ConvertInfixToPostFix();
	_tstring ToString(TCHAR x);

	
public:
	CCalculator();
	CCalculator(CONST TCHAR *input);
	bool IsSyntaxCorrect();
	long double Compute();
	void SetInput(CONST TCHAR* input);
};

