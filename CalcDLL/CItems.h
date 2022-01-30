#pragma once
/**CItems.h
*Created By: Lorenzo Leonardo
*Email : enzotechcomputersolutions@gmail.com
*Date : January 30, 2022
*
* CItems Class 
*   - It is an encapsulation technique to determine if this particular object is an operator, a number or a brace
*   - It was created to have storage of each items after parsing the input string of the calculator.
*
*/
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
private:

	long double m_number;
	_tstring m_soperation;
	PRIORITY m_priority;
	bool     m_isOperator;
	bool     m_bIsDigit;
	bool     m_bIsOpenBrace;
	bool     m_bIsCloseBrace;

	inline bool IsBrace(_tstring s);
	inline bool IsOperator(_tstring s);

public:
	CItems();
	CItems(long double, _tstring oper, PRIORITY prio);
	~CItems();
	void SetPriority(PRIORITY prio);
	void SetOperation(_tstring op);
	_tstring GetOperation();

	long double GetNumber();
	PRIORITY GetPriority();
	bool IsOpenBrace();
	bool IsCloseBrace();
	bool IsAnOperator();
	bool IsADigit();


	CItems operator=(const CItems& b);
	CItems operator+=(const CItems& b);
	CItems operator-=(const CItems& b);
	CItems operator*=(const CItems& b);
	CItems operator/=(const CItems& b);
	CItems operator^=(const CItems& b);
	CItems operator+(const CItems& b);
	CItems operator-(const CItems& b);
	CItems operator*(const CItems& b);
	CItems operator/(const CItems& b);
	CItems operator^(const CItems& b);
};
