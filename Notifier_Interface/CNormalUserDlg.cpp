// CNormalUserDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "CNormalUserDlg.h"
#include "afxdialogex.h"
#include "CAddNewCampaignDlg.h"


// CNormalUserDlg dialog

IMPLEMENT_DYNAMIC(CNormalUserDlg, CDialog)

CNormalUserDlg::CNormalUserDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_NORMAL_USER, pParent)
{
}

CNormalUserDlg::~CNormalUserDlg()
{
}

void CNormalUserDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNormalUserDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_NEW_CAMPAIGN, &CNormalUserDlg::OnBnClickedButtonNewCampaign)
	ON_BN_CLICKED(IDC_BUTTON_LIST_CAMPAIGNS, &CNormalUserDlg::OnBnClickedButtonListCampaigns)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_CAMPAIGN, &CNormalUserDlg::OnBnClickedButtonEditCampaign)
END_MESSAGE_MAP()


// CNormalUserDlg message handlers


void CNormalUserDlg::OnBnClickedButtonNewCampaign()
{
	CAddNewCampaignDlg* oNewCampaign=new CAddNewCampaignDlg;
	oNewCampaign->DoModal();
	delete oNewCampaign;
}


void CNormalUserDlg::OnBnClickedButtonListCampaigns()
{
	// TODO: Add your control notification handler code here
}


void CNormalUserDlg::OnBnClickedButtonEditCampaign()
{
	// TODO: Add your control notification handler code here
}
