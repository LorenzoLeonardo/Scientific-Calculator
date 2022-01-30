#include "pch.h"
#include "CCalculator.h"


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
void CCalculator::SetInput(CONST TCHAR* input)
{
	while (!m_stack.empty())
		m_stack.pop();
	m_postfix.clear();
	m_infix.clear();
	m_input = input;
	ParseInput();
}
bool CCalculator::IsSyntaxCorrect()
{

	return m_bCorrectSyntax;
}

long double CCalculator::Compute()
{

	size_t nLen = m_postfix.size();
	size_t index = 0;

	while (m_postfix.size() > 1)
	{
		if (m_postfix[index].IsAnOperator())
		{
			if (m_postfix[index].GetOperation().compare(_T("+")) == 0)
			{
				m_postfix[index - 2]= m_postfix[index - 2] + m_postfix[index - 1];
			}
			else if (m_postfix[index].GetOperation().compare(_T("-")) == 0)
			{
				m_postfix[index - 2] = m_postfix[index - 2] - m_postfix[index - 1];
			}
			else if (m_postfix[index].GetOperation().compare(_T("*")) == 0)
			{
				m_postfix[index - 2] = m_postfix[index - 2] * m_postfix[index - 1];
			}
			else if (m_postfix[index].GetOperation().compare(_T("/")) == 0)
			{
				m_postfix[index - 2] = m_postfix[index - 2] / m_postfix[index - 1];
			}
			else if (m_postfix[index].GetOperation().compare(_T("^")) == 0)
			{
				m_postfix[index - 2] = m_postfix[index - 2] ^ m_postfix[index - 1];
			}
			m_postfix.erase(m_postfix.begin() + index);
			m_postfix.erase(m_postfix.begin() + index-1);
			index-=2;
		}
		else
		{
			index++;
		}
	}
	return m_postfix[0].GetNumber();
}

inline _tstring CCalculator::RemoveSpaces(_tstring sMain)
{
	sMain.erase(std::remove(sMain.begin(), sMain.end(), _T(' ')), sMain.end());
	return sMain;
}
inline _tstring CCalculator::InsertWithin(_tstring sMain, _tstring substring, _tstring c)
{
	while (sMain.find(substring) != _tstring::npos)
		sMain.insert(sMain.find(substring) + 1, c);
	return sMain;
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
		s == _T('*') ||
		s == _T('^'))
		return true;
	else
		return false;
}

inline _tstring CCalculator::InsertBothEnd(_tstring sMain, _tstring cBegin, _tstring cEnd)
{
	return cBegin + sMain + cEnd;
}
_tstring CCalculator::ToString(TCHAR x)
{
	// string class has a constructor
	// that allows us to specify size of
	// string as first parameter and character
	// to be filled in given size as second
	// parameter.
	_tstring s(1, x);

	return s;
}
void CCalculator::ParseInput()
{
	m_bCorrectSyntax = false;

	if (m_input.empty())
		return;

	m_input= RemoveSpaces(m_input);
	m_input = InsertWithin(m_input,_T(")("), _T("*"));
	for (int i = 0; i < 10; i++)
	{
		_tstring sNum(1, i+48);

		m_input = InsertWithin(m_input, sNum+_T("("), _T("*"));
		m_input = InsertWithin(m_input,  _T(")")+ sNum, _T("*"));
	}
	m_input = InsertBothEnd(m_input, _T("("), _T(")"));
	m_bCorrectSyntax = IsBalanced(m_input);
	if (!m_bCorrectSyntax)
		return;
	m_bCorrectSyntax = IsAlphaNumBrace(m_input);
	if (!m_bCorrectSyntax)
		return;

	size_t nLen = m_input.size();
	for (size_t i = 0; i < nLen && m_bCorrectSyntax; i++)
	{
		if (m_input[i] == _T('('))
		{
			CItems item(0, _T("("), PRIORITY::ONE);

			m_infix.push_back(item);
		}
		else if (m_input[i] == _T(')'))
		{
			CItems item(0, _T(")"), PRIORITY::ONE);

			m_infix.push_back(item);
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
				else
				{
					sTemp += m_input[i];
					i++;
				}
			}
			if (sTemp[sTemp.length() - 1] == _T('.'))
				m_bCorrectSyntax = false;

			if (m_bCorrectSyntax)
			{
				i--;
				long double ldNum = stold(sTemp);
				CItems item(ldNum, _T(""), PRIORITY::ONE);

				m_infix.push_back(item);
			}
		}
		else if (IsOperator(m_input[i]))
		{
			CItems item(0, ToString(m_input[i]), GetPriorityNumber(m_input[i]));

			m_infix.push_back(item);
		}
	}
	if(m_bCorrectSyntax)
		ConvertInfixToPostFix();

	return;
}
inline PRIORITY CCalculator::GetPriorityNumber(TCHAR c)
{
	if (c == _T('^'))
		return PRIORITY::TWO;
	else if (c == _T('*') || c == _T('/'))
		return PRIORITY::THREE;
	else if (c == _T('+') || c == _T('-'))
		return PRIORITY::FOUR;
	else
		return PRIORITY::FIVE;
}
void CCalculator::ConvertInfixToPostFix()
{
	size_t nSize = m_infix.size();

	for (size_t i = 0; i < nSize; i++)
	{
		if (m_infix[i].IsOpenBrace())
		{
			m_stack.push(m_infix[i]);
		}
		else if (m_infix[i].IsCloseBrace())
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
		else if (m_infix[i].IsADigit())
		{
			m_postfix.push_back(m_infix[i]);
		}
		else if (m_infix[i].IsAnOperator())
		{
			CItems item;
			//one as the highest priority
			while (m_stack.top().IsAnOperator() && (m_stack.top().GetPriority() <= m_infix[i].GetPriority()))
			{
				m_postfix.push_back(m_stack.top());
				m_stack.pop();
			}
			m_stack.push(m_infix[i]);
		}
	}

}

bool CCalculator::IsAlphaNumBrace(_tstring s)
{
	size_t nLen = s.length();
	bool bFlag = true;
	for (size_t i = 0 ; i < nLen; i++)
	{
		if (!(IsOperator(s[i]) || _istxdigit(s[i]) || s[i] == _T('(') || s[i] == _T(')') || s[i] == _T('.')))
		{
			bFlag = false;
			break;
		}
	}
	return bFlag;
}