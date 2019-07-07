// UpdateClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "UpdateClientDlg.h"
#include "afxdialogex.h"
#include "CClientTypeService.h"
#include "CCountryService.h"
#include "CClientService.h"


// CUpdateClientDlg dialog

IMPLEMENT_DYNAMIC(CUpdateClientDlg, CDialog)

CUpdateClientDlg::CUpdateClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_UPDATE_CLIENTS, pParent)
	, m_strUpdatedNames(_T(""))
	, m_strUpdatedEmail(_T(""))
	, m_strUpdatedPhone(_T(""))
	, m_strUpdatedPinOrBulstat(_T(""))
	, m_strUpdatedCountry(_T(""))
	, m_bUpdatedIsVerified(FALSE)
	, m_bUpdatedMsgAgreed(FALSE)
	, m_strUpdatedClientType(_T(""))
{

}

BOOL CUpdateClientDlg::OnInitDialog()
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
		strClientType.Format("%s", itCurrentClientType->szClientType);
		m_CMBUpdatedClientType.AddString(strClientType);
	}


	for (itCurrentCountry = vCountries.begin(); itCurrentCountry != vCountries.end(); itCurrentCountry++)
	{
		CString strCountry;
		strCountry.Format("%s", itCurrentCountry->szName);
		m_CMBUpdatedCountry.AddString(strCountry);
	}

	m_CMBUpdatedCountry.SetCurSel(m_CMBUpdatedCountry.FindStringExact(0, m_strUpdatedCountry));
	m_CMBUpdatedClientType.SetCurSel(m_CMBUpdatedClientType.FindStringExact(0, m_strUpdatedClientType));
	return true;
}

CUpdateClientDlg::~CUpdateClientDlg()
{
}

void CUpdateClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_NAMES, m_strUpdatedNames);
	DDX_Text(pDX, IDC_EDIT_UPDATE_EMAIL, m_strUpdatedEmail);
	DDX_Text(pDX, IDC_EDIT_UPDATE_PHONE, m_strUpdatedPhone);
	DDX_Text(pDX, IDC_EDIT_UPDATE_PINORBULSTAT, m_strUpdatedPinOrBulstat);
	DDX_CBString(pDX, IDC_COMBO_UPDATE_COUNTRY, m_strUpdatedCountry);
	DDX_Check(pDX, IDC_CHECK_UPDATE_ISVERIFIED, m_bUpdatedIsVerified);
	DDX_Check(pDX, IDC_CHECK_UPDATE_MSGS_AGREED, m_bUpdatedMsgAgreed);
	DDX_CBString(pDX, IDC_COMBO_UPDATE_CLIENT_TYPE, m_strUpdatedClientType);
	DDX_Control(pDX, IDC_COMBO_UPDATE_COUNTRY, m_CMBUpdatedCountry);
	DDX_Control(pDX, IDC_COMBO_UPDATE_CLIENT_TYPE, m_CMBUpdatedClientType);
}


BEGIN_MESSAGE_MAP(CUpdateClientDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_ADD_CLIENT, &CUpdateClientDlg::OnBnClickedButtonUpdateClient)
END_MESSAGE_MAP()


// CUpdateClientDlg message handlers


void CUpdateClientDlg::OnBnClickedButtonUpdateClient()
{
	UpdateData();

	CClientService oClientService;

	if (m_bUpdatedIsVerified)
	{
		m_strUpdatedIsVerified = "true";
	}
	else
	{
		m_strUpdatedIsVerified = "false";
	}

	if (m_bUpdatedMsgAgreed)
	{
		m_strUpdatedMsgAgreed = "true";
	}
	else
	{
		m_strUpdatedMsgAgreed = "false";
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
		if (itCurrentClientType->szClientType == m_strUpdatedClientType)
		{
			m_nUpdatedClientTypeId = itCurrentClientType->nId;
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
		if (itCurrentCountry->szName == m_strUpdatedCountry)
		{
			m_nUpdatedCountryId = itCurrentCountry->nId;
		}
	}

	bool bClientSuccessfullyAdded = oClientService.Update(m_strUpdatedNames, m_nUpdatedClientTypeId, m_strUpdatedPinOrBulstat, m_nUpdatedCountryId, m_strUpdatedEmail, m_strUpdatedPhone, m_strUpdatedIsVerified, m_strUpdatedMsgAgreed);
	if (bClientSuccessfullyAdded)
	{
		MessageBox("Client successfully updated!");
		m_bClSuccUpdated = true;
		EndDialog(0);
	}
	else
	{
		MessageBox("Failed updating client!");
		m_bClSuccUpdated = false;
	}
}
