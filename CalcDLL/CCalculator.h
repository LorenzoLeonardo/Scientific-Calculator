#pragma once
/**CCalculator.h
*Created By: Lorenzo Leonardo
*Date : January 30, 2022
*
* CCalculator Class
*   - This is where the parsing and processing of input data
*
*/
#include <stack>
#include <string>
#include <tchar.h>
#include <vector>
#include "CItems.h"
using namespace std;


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

