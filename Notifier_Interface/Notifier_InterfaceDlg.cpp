
// Notifier_InterfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "Notifier_InterfaceDlg.h"
#include "afxdialogex.h"
#include "Functions.h"
#include "DBContext.h"
#include "CNormalUserDlg.h"
#include "CUserService.h"
#include "CRegisterUserDlg.h"
#include "CAdminUserDlg.h"

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


// CNotifierInterfaceDlg dialog



CNotifierInterfaceDlg::CNotifierInterfaceDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_NOTIFIER_INTERFACE_DIALOG, pParent)
	, m_strUsername(_T(""))
	, m_strPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNotifierInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USERNAME, m_strUsername);
	DDX_Text(pDX, IDC_EDIT_PASSWORD, m_strPassword);
}

BEGIN_MESSAGE_MAP(CNotifierInterfaceDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CNotifierInterfaceDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CNotifierInterfaceDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CNotifierInterfaceDlg message handlers

BOOL CNotifierInterfaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNotifierInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNotifierInterfaceDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNotifierInterfaceDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CNotifierInterfaceDlg::OnBnClickedButtonLogin()
{
	UpdateData();

	CUserService userService;
	bool bUserLogedIn=userService.Login(m_strUsername, m_strPassword);

	if (bUserLogedIn)
	{
		AfxMessageBox("Welcome " + m_strUsername);
		if (userService.IsAdmin(userService.recLoggedUser.szUsername))
		{
			CAdminUserDlg* oAdminUserDlg= new CAdminUserDlg;
			oAdminUserDlg->DoModal();
			delete oAdminUserDlg;
		}
		else
		{
			CNormalUserDlg* oNormalUserDlg = new CNormalUserDlg;
			oNormalUserDlg->DoModal();
			delete oNormalUserDlg;
		}
	}
	else
	{
		AfxMessageBox("Invalid credentials!");
	}
}




void CNotifierInterfaceDlg::OnBnClickedButtonRegister()
{
	CRegisterUserDlg* oRegisterUserDlg=new CRegisterUserDlg;
	oRegisterUserDlg->DoModal();
	delete oRegisterUserDlg;
}
