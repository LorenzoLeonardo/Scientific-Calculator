#include "pch.h"
#include "CCalculator.h"

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

	if(oper.compare(_T("(")) == 0)
		m_bIsOpenBrace = true;
	else if (oper.compare(_T(")")) == 0)
		m_bIsCloseBrace = true;
	
	if (!m_isOperator && !m_bIsOpenBrace && !m_bIsCloseBrace)
		m_bIsDigit = true;
}
CItems::~CItems()
{

}
bool CItems::IsOperator(_tstring s)
{
	if (s.compare(_T("+")) == 0 ||
		s.compare(_T("-")) == 0 ||
		s.compare(_T("*")) == 0 ||
		s.compare(_T("/")) == 0)
				return true;
	else
				return false;
}
bool CItems::IsBrace(_tstring s)
{
	if (s.compare(_T("(")) == 0 ||
		s.compare(_T(")")) == 0)
		return true;
	else
		return false;
}
CCalculator::CCalculator()
{
	m_input = _T("");
	m_bCorrectSyntax = true;
}

CCalculator::CCalculator(const TCHAR *input)
{
	m_input = input;
	m_bCorrectSyntax = true;

}
bool CCalculator::IsSyntaxCorrect()
{

	return m_bCorrectSyntax;
}

long double CCalculator::Compute()
{

	return 0;
}

void CCalculator::RemoveSpaces()
{
	m_input.erase(std::remove(m_input.begin(), m_input.end(), _T(' ')), m_input.end());
}
bool CCalculator::IsBalanced(_tstring s)
{
	_tstring sStack;
	size_t nLen = s.length();

	for (size_t i = 0; i < nLen; i++)
	{

		if (s[i] == _T('('))
		{
			sStack.push_back(s[i]);
		}
		else if (s[i] == _T('{'))
		{
			sStack.push_back(s[i]);
		}
		else if (s[i] == _T('['))
		{
			sStack.push_back(s[i]);
		}
		else if (s[i] == _T(')'))
		{
			if (!sStack.empty())
			{
				if (sStack[sStack.length() - 1] == _T('('))
					sStack.pop_back();
			}
			else
				sStack.push_back(s[i]);
		}
		else if (s[i] == _T(']'))
		{
			if (!sStack.empty())
			{
				if (sStack[sStack.length() - 1] == _T('['))
					sStack.pop_back();
			}
			else
				sStack.push_back(s[i]);
		}
		else if (s[i] == _T('}'))
		{
			if (!sStack.empty())
			{
				if (sStack[sStack.length() - 1] == _T('{'))
					sStack.pop_back();
			}
			else
				sStack.push_back(s[i]);
		}

	}
	if (sStack.empty())
		return true;
	else
		return false;
};
bool CCalculator::IsOperator(TCHAR s)
{
	if (s == _T('+') ||
		s == _T('-') ||
		s == _T('/') ||
		s == _T('*'))
		return true;
	else
		return false;
}


void CCalculator::ParseInput()
{
	RemoveSpaces();
	m_input = _T("(") + m_input + _T(")");

	m_bCorrectSyntax = IsBalanced(m_input);
	if (!m_bCorrectSyntax)
		return;

	if (!m_input.empty())
	{
		size_t nLen = m_input.size();
		for (size_t i = 0; i < nLen; i++)
		{
			if (m_input[i] == _T('('))
			{
				CItems item(0, _T("("), PRIORITY::ONE);

				m_itemsArray.push_back(item);
			}
			else if (m_input[i] == _T(')'))
			{
				CItems item(0, _T(")"), PRIORITY::ONE);

				m_itemsArray.push_back(item);
			}
			else if (_istxdigit(m_input[i]))
			{
				int nDotCounter = 0;
				_tstring sTemp = _T("");
				while (_istxdigit(m_input[i]) || (m_input[i] == _T('.')))
				{
					if (m_input[i] == _T('.'))
					{
						nDotCounter++;
					}
					if (nDotCounter > 1)
					{
						m_bCorrectSyntax = false;
						break;
					}
					sTemp += m_input[i];
					i++;
				}
				i--;
				long double ldNum = stold(sTemp);
				CItems item(ldNum, _T(""), PRIORITY::ONE);

				m_itemsArray.push_back(item);
			}
			else if (IsOperator(m_input[i]))
			{
				PRIORITY prio = PRIORITY::ONE;

				if (m_input[i] == _T('+') || m_input[i] == _T('-'))
					prio = PRIORITY::THREE;
				else
					prio = PRIORITY::TWO;

				_tstring oper = _T("");
				if(m_input[i] == _T('+'))
					oper = _T("+");
				else if(m_input[i] == _T('-'))
					oper = _T("-");
				else if (m_input[i] == _T('*'))
					oper = _T("*");
				else if (m_input[i] == _T('/'))
					oper = _T("/");

				CItems item(0, oper, prio);

				m_itemsArray.push_back(item);
			}
		}
		m_bCorrectSyntax = true;
		ConvertInfixToPostFix();
	}
	else
	{
		m_bCorrectSyntax = false;
	}
	return;
}

void CCalculator::ConvertInfixToPostFix()
{
	size_t nSize = m_itemsArray.size();

	for (size_t i = 0; i < nSize; i++)
	{
		if (m_itemsArray[i].IsOpenBrace())
		{
			m_stack.push(m_itemsArray[i]);
		}
		else if (m_itemsArray[i].IsCloseBrace())
		{
			CItems item;
			while (!m_stack.empty() && !m_stack.top().IsOpenBrace())
			{
				item = m_stack.top();
				m_postfix.push_back(item);
				m_stack.pop();
			}
			if(!m_stack.empty())
				m_stack.pop();
		}
		else if (m_itemsArray[i].IsADigit())
		{
			m_postfix.push_back(m_itemsArray[i]);
		}
		else if (m_itemsArray[i].IsAnOperator())
		{
			CItems item;
			while (m_stack.top().IsAnOperator() && (m_stack.top().GetPriority() <= m_itemsArray[i].GetPriority()))
			{
				m_postfix.push_back(m_stack.top());
				m_stack.pop();
				//m_stack.push(m_itemsArray[i]);
			}
			m_stack.push(m_itemsArray[i]);
		}
	}


}