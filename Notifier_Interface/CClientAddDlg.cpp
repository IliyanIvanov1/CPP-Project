// CTryClientAdd.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "CClientAddDlg.h"
#include "afxdialogex.h"
#include "CClientTypeService.h"
#include "CClientService.h"
#include "CCountryService.h"


// CTryClientAdd dialog

IMPLEMENT_DYNAMIC(CClientAddDlg, CDialog)

CClientAddDlg::CClientAddDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_CLIENTS1, pParent)
	, m_strNames(_T(""))
	, m_strEmail(_T(""))
	, m_strPhone(_T(""))
	, m_strPinOrBulstat(_T(""))
	, m_strCountry(_T(""))
	, m_bIsVerified(FALSE)
	, m_bMsgsAgreed(FALSE)
	, m_strClientType(_T(""))
{

}

BOOL CClientAddDlg::OnInitDialog()
{

	CClientTypeService oClientTypeService;
	oClientTypeService.GetClientTypes();
	auto itCurrentClientType = oClientTypeService.m_itClientType;
	auto vClientTypes = oClientTypeService.m_vClientTypes;

	CCountryService oCountryService;
	oCountryService.GetCountries();
	auto itCurrentCountry = oCountryService.m_itCountry;
	auto vCountries = oCountryService.m_vCountries;

	CDialog::OnInitDialog();

	for (itCurrentClientType = vClientTypes.begin(); itCurrentClientType != vClientTypes.end(); itCurrentClientType++)
	{
		CString strClientType;
		strClientType.Format("%s",itCurrentClientType->szClientType);
		m_CMBClientType.AddString(strClientType);
	}


	for (itCurrentCountry = vCountries.begin(); itCurrentCountry != vCountries.end(); itCurrentCountry++)
	{
		CString strCountry;
		strCountry.Format("%s", itCurrentCountry->szName);
		m_CMBCountry.AddString(strCountry);
	}

	return true;
}

CClientAddDlg::~CClientAddDlg()
{
}

void CClientAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NAMES, m_strNames);
	DDX_Text(pDX, IDC_EDIT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_EDIT_PHONE, m_strPhone);
	DDX_Text(pDX, IDC_EDIT_PINORBULSTAT, m_strPinOrBulstat);
	DDX_Control(pDX, IDC_COMBO1, m_CMBCountry);
	DDX_CBString(pDX, IDC_COMBO1, m_strCountry);
	DDX_Check(pDX, IDC_CHECK_ISVERIFIED, m_bIsVerified);
	DDX_Check(pDX, IDC_CHECK_MSGS_AGREED, m_bMsgsAgreed);
	DDX_Control(pDX, IDC_COMBO_CLIENT_TYPE, m_CMBClientType);
	DDX_CBString(pDX, IDC_COMBO_CLIENT_TYPE, m_strClientType);
}


BEGIN_MESSAGE_MAP(CClientAddDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CLIENT,&CClientAddDlg::OnBnClickedButtonAddClient)
END_MESSAGE_MAP()


// CTryClientAdd message handlers


void CClientAddDlg::OnBnClickedButtonAddClient()
{
	UpdateData();

	CClientService oClientService;

	if (m_bIsVerified)
	{
		m_strIsVerified = "true";
	}
	else
	{
		m_strIsVerified = "false";
	}

	if (m_bMsgsAgreed)
	{
		m_strMsgsAgreed = "true";
	}
	else
	{
		m_strMsgsAgreed = "false";
	}

	CClientTypeService oClientTypeService;
	if (!oClientTypeService.GetClientTypes())
	{
		return;
	}
	auto itCurrentClientType = oClientTypeService.m_itClientType;
	auto vClientTypes = oClientTypeService.m_vClientTypes;

	for (itCurrentClientType = vClientTypes.begin(); itCurrentClientType != vClientTypes.end(); itCurrentClientType++)
	{
		if (itCurrentClientType->szClientType==m_strClientType)
		{
			m_nClientTypeId = itCurrentClientType->nId;
		}
	}

	CCountryService oCountryService;

	if (!oCountryService.GetCountries())
	{
		return;
	}

	auto itCurrentCountry = oCountryService.m_itCountry;
	auto vCountries = oCountryService.m_vCountries;

	for (itCurrentCountry = vCountries.begin(); itCurrentCountry != vCountries.end(); itCurrentCountry++)
	{
		if (itCurrentCountry->szName==m_strCountry)
		{
			m_nCountryId = itCurrentCountry->nId;
		}
	}

	bool bClientSuccessfullyAdded = oClientService.Create(m_strNames, m_nClientTypeId, m_strPinOrBulstat, m_nCountryId, m_strEmail, m_strPhone, m_strIsVerified, m_strMsgsAgreed);
	if (bClientSuccessfullyAdded)
	{
		MessageBox("Client successfully added!");
		m_bClSuccAdded = true;
		EndDialog(0);
	}
	else
	{
		MessageBox("Failed adding client!");
		m_bClSuccAdded = false;
	}
}
