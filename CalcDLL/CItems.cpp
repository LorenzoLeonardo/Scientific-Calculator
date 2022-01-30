/**CItems.cpp
*Created By: Lorenzo Leonardo
*Email : enzotechcomputersolutions@gmail.com
*Date : January 30, 2022
*
* CItems Class
*   - It is an encapsulation technique to determine if this particular object is an operator, a number or a brace
*   - It was created to have storage of each items after parsing the input string of the calculator.
*
*/
#include "pch.h"
#include "CItems.h"

CItems::CItems()
{
	m_number = 0;
	m_soperation = _T("");
	m_priority = PRIORITY::ZERO;
	m_isOperator = false;
	m_bIsDigit = false;

}

CItems::CItems(long double num, _tstring oper, PRIORITY prio)
{
	m_number = num;
	m_soperation = oper;
	m_priority = prio;
	m_isOperator = IsOperator(oper);
	m_bIsOpenBrace = false;
	m_bIsCloseBrace = false;
	m_bIsDigit = false;

	if (oper.compare(_T("(")) == 0)
		m_bIsOpenBrace = true;
	else if (oper.compare(_T(")")) == 0)
		m_bIsCloseBrace = true;

	if (!m_isOperator && !m_bIsOpenBrace && !m_bIsCloseBrace)
		m_bIsDigit = true;
}
CItems::~CItems()
{

}
inline bool CItems::IsOperator(_tstring s)
{
	if (s.compare(_T("+")) == 0 ||
		s.compare(_T("-")) == 0 ||
		s.compare(_T("*")) == 0 ||
		s.compare(_T("/")) == 0 ||
		s.compare(_T("^")) == 0)
		return true;
	else
		return false;
}
inline bool CItems::IsBrace(_tstring s)
{
	if (s.compare(_T("(")) == 0 ||
		s.compare(_T(")")) == 0)
		return true;
	else
		return false;
}

void CItems::SetPriority(PRIORITY prio)
{
	m_priority = prio;
}
long double CItems::GetNumber()
{
	return m_number;
}
PRIORITY CItems::GetPriority()
{
	return m_priority;
}
bool CItems::IsOpenBrace()
{
	return m_bIsOpenBrace;
}
bool CItems::IsCloseBrace()
{
	return m_bIsCloseBrace;
}
bool CItems::IsAnOperator()
{
	return m_isOperator;
}
bool CItems::IsADigit()
{
	return m_bIsDigit;
}


void CItems::SetOperation(_tstring op)
{
	m_soperation = op;
}

_tstring CItems::GetOperation()
{
	return m_soperation;
}

CItems CItems::operator=(const CItems& b)
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
CItems CItems::operator+=(const CItems& b)
{
	this->m_number = this->m_number + b.m_number;
	return *this;
}
CItems CItems::operator-=(const CItems& b)
{
	this->m_number = this->m_number - b.m_number;
	return *this;
}
CItems CItems::operator*=(const CItems& b)
{
	this->m_number = this->m_number * b.m_number;
	return *this;
}
CItems CItems::operator/=(const CItems& b)
{
	this->m_number = this->m_number / b.m_number;
	return *this;
}
CItems CItems::operator^=(const CItems& b)
{
	this->m_number = pow(this->m_number, b.m_number);
	return *this;
}
CItems CItems::operator+(const CItems& b)
{
	CItems ans;

	ans.m_number = this->m_number + b.m_number;
	return ans;
}

CItems CItems::operator-(const CItems& b)
{
	CItems ans;

	ans.m_number = this->m_number - b.m_number;
	return ans;
}
CItems CItems::operator*(const CItems& b)
{
	CItems ans;

	ans.m_number = this->m_number * b.m_number;
	return ans;
}
CItems CItems::operator/(const CItems& b)
{
	CItems ans;

	ans.m_number = this->m_number / b.m_number;
	return ans;
}
CItems CItems::operator^(const CItems& b)
{
	CItems ans;

	ans.m_number = pow(this->m_number, b.m_number);
	return ans;
}