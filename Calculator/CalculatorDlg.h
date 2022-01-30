
// CalculatorDlg.h : header file
//

#pragma once
#include <string>
typedef VOID(WINAPI* LPSetInput)(const TCHAR* input);
typedef bool(WINAPI* LPCheckSyntax)();
typedef long double(WINAPI* LPCompute)();

using namespace std;

// CCalculatorDlg dialog
class CCalculatorDlg : public CDialogEx
{
// Construction
public:
	CCalculatorDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	LPSetInput fnpSetInput;
	LPCheckSyntax fnpCheckSyntax;
	LPCompute fnpCompute;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	HMODULE dll_handle;
private:
	CEdit m_ctrlEditInput;
	CEdit m_ctrlEditOutput;
public:
	afx_msg void OnBnClickedButtonAns();
	afx_msg void OnEnChangeEditInput();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButtonPlus();
	afx_msg void OnBnClickedButtonMinus();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonOpenbrace();
	afx_msg void OnBnClickedButtonClosebrace();
};
