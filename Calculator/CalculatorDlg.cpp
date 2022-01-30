
// CalculatorDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCalculatorDlg dialog



CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	dll_handle = NULL;
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_ctrlEditInput);
	DDX_Control(pDX, IDC_EDIT_OUTPUT, m_ctrlEditOutput);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_ANS, &CCalculatorDlg::OnBnClickedButtonAns)
	ON_EN_CHANGE(IDC_EDIT_INPUT, &CCalculatorDlg::OnEnChangeEditInput)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_PLUS, &CCalculatorDlg::OnBnClickedButtonPlus)
	ON_BN_CLICKED(IDC_BUTTON_MINUS, &CCalculatorDlg::OnBnClickedButtonMinus)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCalculatorDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_OPENBRACE, &CCalculatorDlg::OnBnClickedButtonOpenbrace)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEBRACE, &CCalculatorDlg::OnBnClickedButtonClosebrace)
END_MESSAGE_MAP()


// CCalculatorDlg message handlers

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	dll_handle = LoadLibrary(_T("CalcDLL.dll"));

	if (dll_handle)
	{
		fnpSetInput = (LPSetInput)GetProcAddress(dll_handle, "SetInput");
		fnpCheckSyntax = (LPCheckSyntax)GetProcAddress(dll_handle, "CheckSyntax");
		fnpCompute = (LPCompute)GetProcAddress(dll_handle, "Compute");
	}

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CCalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedButtonAns()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	long double answer;

	fnpSetInput(cs.GetBuffer());
	if (fnpCheckSyntax())
	{
		answer = fnpCompute();
#ifdef _UNICODE
		m_ctrlEditOutput.SetWindowText(to_wstring(answer).c_str());
#else
		m_ctrlEditOutput.SetWindowText(to_string(answer).c_str());
#endif
	
		
	}
	else
		m_ctrlEditOutput.SetWindowText(_T("Invalid Input"));
}


void CCalculatorDlg::OnEnChangeEditInput()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void CCalculatorDlg::OnBnClickedButtonClear()
{
	// TODO: Add your control notification handler code here
	m_ctrlEditInput.SetWindowText(_T("0"));
	m_ctrlEditOutput.SetWindowText(_T(""));
}


void CCalculatorDlg::OnBnClickedButton0()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("0");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton1()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("1");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("2");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton3()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("3");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("4");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton5()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("5");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton6()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("6");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton7()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("7");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("8");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButton9()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("9");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonPlus()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("+");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonMinus()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("-");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("*");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonDivide()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("/");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonOpenbrace()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T("(");
	m_ctrlEditInput.SetWindowText(cs);
}


void CCalculatorDlg::OnBnClickedButtonClosebrace()
{
	// TODO: Add your control notification handler code here
	CString cs;
	m_ctrlEditInput.GetWindowText(cs);
	cs += _T(")");
	m_ctrlEditInput.SetWindowText(cs);
}
