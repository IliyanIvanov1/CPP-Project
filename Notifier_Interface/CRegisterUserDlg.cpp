// CRegisterUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "CRegisterUserDlg.h"
#include "afxdialogex.h"
#include "CUserService.h"
#include "CPositionService.h"
#include "Functions.h"

#define FIRST_USER 1
#define POSITION_ADMIN "Admin"
// CRegisterUserDlg dialog

IMPLEMENT_DYNAMIC(CRegisterUserDlg, CDialog)

CRegisterUserDlg::CRegisterUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_REGISTER_USER, pParent)
	, m_strRegNames(_T(""))
	, m_strRegUsername(_T(""))
	, m_strRegPassword(_T(""))
	, m_strRegConfPassword(_T(""))
{

}

CRegisterUserDlg::~CRegisterUserDlg()
{
}

void CRegisterUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_REGISTER_NAMES, m_strRegNames);
	DDX_Text(pDX, IDC_EDIT_REGISTER_USERNAME, m_strRegUsername);
	DDX_Text(pDX, IDC_EDIT_REGISTER_PASSWORD, m_strRegPassword);
	DDX_Text(pDX, IDC_EDIT_REGISTER_CONFPASSWORD, m_strRegConfPassword);
}


BEGIN_MESSAGE_MAP(CRegisterUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, &CRegisterUserDlg::OnBnClickedButtonRegister)
END_MESSAGE_MAP()


// CRegisterUserDlg message handlers


void CRegisterUserDlg::OnBnClickedButtonRegister()
{
	UpdateData();

	CUserService oUserService;
	CString strHashedPassword = HashFunction(m_strRegPassword);

	int nPositionId;
	CPositionService oPositionService;
	if (!oPositionService.GetPositions())
	{
		return;
	}	
	auto itCurrentPosition = oPositionService.m_itPosition;
	auto vPositions = oPositionService.m_vPositions;

	for (itCurrentPosition = vPositions.begin(); itCurrentPosition != vPositions.end(); itCurrentPosition++)
	{
		bool bUserIsFirst = oUserService.FindNextId() == FIRST_USER;
		bool bPosIsAdmin = strcmp(itCurrentPosition->szPositionName, POSITION_ADMIN)==0;

		if (bUserIsFirst && bPosIsAdmin)
		{
			nPositionId = itCurrentPosition->nId;
		}
		if (!bUserIsFirst && !bPosIsAdmin)
		{
			nPositionId = itCurrentPosition->nId;
		}
	}
	
	if (m_strRegUsername.GetLength()>4)
	{
		if (m_strRegPassword.GetLength()>6)
		{
			if (m_strRegPassword==m_strRegConfPassword)
			{
				bool bUserSuccessfullyAdded= oUserService.Create(m_strRegNames, m_strRegUsername, strHashedPassword, nPositionId);
				if (bUserSuccessfullyAdded)
				{
					AfxMessageBox("User successfully added!");
				}
				else
				{
					AfxMessageBox("User with such username already exists!");
				}
			}
			else
			{
				AfxMessageBox("Confirm password doesn't match your password!");
			}
		}
		else
		{
			AfxMessageBox("Password must be above 6 characters!");
		}
	}
	else
	{
		AfxMessageBox("Username must be above 4 characters!");
	}
}
