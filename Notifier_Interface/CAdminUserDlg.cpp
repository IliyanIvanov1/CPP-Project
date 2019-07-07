// CAdminUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "CAdminUserDlg.h"
#include "afxdialogex.h"
#include "CClientAddDlg.h"
#include "CAddNewCampaignDlg.h"
#include "ListClientsDlg.h"


// CAdminUserDlg dialog

IMPLEMENT_DYNAMIC(CAdminUserDlg, CDialog)

CAdminUserDlg::CAdminUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_ADMIN_USER, pParent)
{

}

CAdminUserDlg::~CAdminUserDlg()
{
}

void CAdminUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAdminUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CLIENT, &CAdminUserDlg::OnBnClickedButtonAddClient)
	ON_BN_CLICKED(IDC_BUTTON_ADMIN_NEW_CAMPAIGN, &CAdminUserDlg::OnBnClickedButtonAdminNewCampaign)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CLIENTS, &CAdminUserDlg::OnBnClickedButtonListClients)
END_MESSAGE_MAP()


// CAdminUserDlg message handlers


void CAdminUserDlg::OnBnClickedButtonAddClient()
{
	CClientAddDlg* oAddClient=new CClientAddDlg;
	oAddClient->DoModal();
	delete oAddClient;
}

void CAdminUserDlg::OnBnClickedButtonAdminNewCampaign()
{
	CAddNewCampaignDlg* oNewCampaign=new CAddNewCampaignDlg;
	oNewCampaign->DoModal();
	delete oNewCampaign;
}

void CAdminUserDlg::OnBnClickedButtonListClients()
{
	CListClientsDlg* oListClients = new CListClientsDlg;
	oListClients->DoModal();
	delete oListClients;
}
