// CAddNewCampaignDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "CAddNewCampaignDlg.h"
#include "CFilterServices.h"
#include "afxdialogex.h"


// CAddNewCampaignDlg dialog

IMPLEMENT_DYNAMIC(CAddNewCampaignDlg, CDialog)

CAddNewCampaignDlg::CAddNewCampaignDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_NEW_CAMPAIGN, pParent)
	, m_strName(_T(""))
	, m_strFilter(_T(""))
	, m_DTCValidFrom(COleDateTime::GetCurrentTime())
	, m_DTCValidUntil(COleDateTime::GetCurrentTime())
{

}

BOOL CAddNewCampaignDlg::OnInitDialog()
{
	CFilterServices oFilterService;
	oFilterService.GetFilters();
	auto vFilters = oFilterService.m_vFilters;
	auto itCurrentFilter = oFilterService.m_itFilter;

	CDialog::OnInitDialog();
	for  (itCurrentFilter = vFilters.begin(); itCurrentFilter != vFilters.end(); itCurrentFilter++)
	{
		CString strFilter;
		strFilter.Format("%s", itCurrentFilter->szName);
		m_CMBFilter.AddString(strFilter);
	}
	return true;
}

CAddNewCampaignDlg::~CAddNewCampaignDlg()
{
}

void CAddNewCampaignDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAME, m_strName);
	DDX_Control(pDX, IDC_COMBO_FILTER, m_CMBFilter);
	DDX_CBString(pDX, IDC_COMBO_FILTER, m_strFilter);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VALID_FROM, m_DTCValidFrom);
	DDX_Control(pDX, IDC_DATETIMEPICKER_VALID_FROM, m_oValidFrom);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER_VALID_UNTIL, m_DTCValidUntil);
	DDX_Control(pDX, IDC_DATETIMEPICKER_VALID_UNTIL, m_oValidUntil);
}


BEGIN_MESSAGE_MAP(CAddNewCampaignDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CAddNewCampaignDlg::OnBnClickedButtonSubmit)
END_MESSAGE_MAP()


// CAddNewCampaignDlg message handlers


void CAddNewCampaignDlg::OnBnClickedButtonSubmit()
{
	UpdateData();

}
