#pragma once

#include <stack>
#include <string>
#include <tchar.h>
#include <vector>
using namespace std;


#ifdef _UNICODE
#define _tstring wstring 

#else
#define _tstring string 
#endif

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

public:
	CItems();
	CItems(long double, _tstring oper, PRIORITY prio);
	~CItems();

	void SetPriority(PRIORITY prio)
	{
		m_priority = prio;
	}
	PRIORITY GetPriority()
	{
		return m_priority;
	}
	bool IsAnOperator()
	{
		return m_isOperator;
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
		this->m_number = this->m_number + b.m_number;
		this->m_soperation = b.m_soperation;
		this->m_priority = PRIORITY::ZERO;
		return *this;
	}

	CItems operator+(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number + b.m_number;
		ans.m_priority = PRIORITY::ZERO;
		return ans;
	}
	CItems operator+=(const CItems& b)
	{
		this->m_number = this->m_number + b.m_number;
		this->m_priority = PRIORITY::ZERO;
		return *this;
	}
	CItems operator-(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number - b.m_number;
		ans.m_priority = PRIORITY::ZERO;
		return ans;
	}
	CItems operator*(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number * b.m_number;
		ans.m_priority = PRIORITY::ZERO;
		return ans;
	}
	CItems operator/(const CItems& b)
	{
		CItems ans;

		ans.m_number = this->m_number / b.m_number;
		ans.m_priority = PRIORITY::ZERO;
		return ans;
	}
};


class CCalculator
{
private:
	stack<CItems> m_stack;
	vector<CItems> m_postfix;
	vector<CItems> m_itemsArray;

	_tstring m_input;
	bool m_bCorrectSyntax;
	void ParseInput();
	void RemoveSpaces();
	bool IsBalanced(_tstring s);
	bool IsOperator(TCHAR s);
	void ConvertInfixToPostFix();
public:
	CCalculator();
	CCalculator(CONST TCHAR *input);
	bool IsSyntaxCorrect();
	long double Compute();
	void SetInput(CONST TCHAR* input)
	{
		m_input = input;
		ParseInput();
	}

};

