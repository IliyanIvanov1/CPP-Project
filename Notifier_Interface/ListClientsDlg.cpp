// ListClientsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Notifier_Interface.h"
#include "ListClientsDlg.h"
#include "afxdialogex.h"
#include "CClientService.h"
#include "CClientAddDlg.h"
#include "UpdateClientDlg.h"
#include "Functions.h"

using namespace std;
// CListClientsDlg dialog

IMPLEMENT_DYNAMIC(CListClientsDlg, CDialog)

CListClientsDlg::CListClientsDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG_LIST_CLIENTS, pParent)
{

}

BOOL CListClientsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_LSCListClients.SetExtendedStyle(m_LSCListClients.GetExtendedStyle() | LVS_EX_FULLROWSELECT);

	m_LSCListClients.InsertColumn(0, _T("Names"), LVCFMT_LEFT, 120);
	m_LSCListClients.InsertColumn(1, _T("Email"), LVCFMT_LEFT, 170);
	m_LSCListClients.InsertColumn(2, _T("Phone number"), LVCFMT_LEFT, 120);
	m_LSCListClients.InsertColumn(3, _T("PIN or Bulstat"), LVCFMT_LEFT, 120);
	m_LSCListClients.InsertColumn(4, _T("Client type"), LVCFMT_LEFT, 120);
	m_LSCListClients.InsertColumn(5, _T("Verified"), LVCFMT_LEFT, 120);
	m_LSCListClients.InsertColumn(6, _T("Agreed to receive messages"), LVCFMT_LEFT, 150);
	m_LSCListClients.InsertColumn(7, _T("Country"), LVCFMT_LEFT,120);


	if (!InsertItems())
	{
		return false;
	}
	
	return true;
}

bool CListClientsDlg::InsertItems()
{
	CClientService oClientService;
	if (!oClientService.ListClients())
	{
		return false;
	}
	//auto vClientsFullInfo = oClientService.m_vClientsFullInfo;

	m_vClientsFullInfo = oClientService.m_vClientsFullInfo;
	auto itCurrentClientFullInfo = oClientService.m_itCurrentClientFullInfo;

	for (itCurrentClientFullInfo = m_vClientsFullInfo.begin(); itCurrentClientFullInfo < m_vClientsFullInfo.end(); itCurrentClientFullInfo++)
	{
		int nRowNumber = itCurrentClientFullInfo - m_vClientsFullInfo.begin();
		int nIndex = m_LSCListClients.InsertItem(nRowNumber, _T(itCurrentClientFullInfo->szNames));
		int nColumnOrder = 1;
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szEmail));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szPhone));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szPinOrBulstat));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szClientType));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szIsVerified));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder++, _T(itCurrentClientFullInfo->szMsgAgreed));
		m_LSCListClients.SetItemText(nIndex, nColumnOrder, _T(itCurrentClientFullInfo->szCountry));
	}
	return true;
}


CListClientsDlg::~CListClientsDlg()
{
}

void CListClientsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CLIENTS, m_LSCListClients);
}


BEGIN_MESSAGE_MAP(CListClientsDlg, CDialog)
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_CONTEXTMENU_ADD, &CListClientsDlg::OnContextmenuAdd)
	ON_COMMAND(ID_CONTEXTMENU_UPDATE, &CListClientsDlg::OnContextmenuUpdate)
	ON_COMMAND(ID_CONTEXTMENU_DELETE, &CListClientsDlg::OnContextmenuDelete)
END_MESSAGE_MAP()


// CListClientsDlg message handlers


void CListClientsDlg::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	//Load the menu
	CMenu mnuContextMenu;
	mnuContextMenu.LoadMenuA(IDR_CONTEXT_MENU);

	//Get a pointer to the list control
	CListCtrl *pLSCListClients;
	pLSCListClients = reinterpret_cast<CListCtrl*>(GetDlgItem(IDC_LIST_CLIENTS));

	//Find the rectangle around the list control
	CRect rectListControl;
	pLSCListClients->GetWindowRect(&rectListControl);

	//Get a pointer to the first item of the menu
	CMenu *mnuPopupMenu = mnuContextMenu.GetSubMenu(0);
	ASSERT(mnuPopupMenu);

	if (rectListControl.PtInRect(point))
	{
		mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	}
}




void CListClientsDlg::OnContextmenuAdd()
{
	CClientAddDlg* oAddClient = new CClientAddDlg;
	oAddClient->DoModal();

	if (oAddClient->m_bClSuccAdded)
	{
		int nItem = m_vClientsFullInfo.size();

		int nIndex = m_LSCListClients.InsertItem(nItem, _T(oAddClient->m_strNames));

		int nColumnOrder = 1;
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oAddClient->m_strEmail));
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oAddClient->m_strPhone));
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oAddClient->m_strPinOrBulstat));
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oAddClient->m_strClientType));
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(BoolToString(oAddClient->m_bIsVerified)));
		m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(BoolToString(oAddClient->m_bMsgsAgreed)));
		m_LSCListClients.SetItemText(nItem, nColumnOrder, _T(oAddClient->m_strCountry));

	}

	delete oAddClient;

}


void CListClientsDlg::OnContextmenuUpdate()
{
	POSITION pos = m_LSCListClients.GetFirstSelectedItemPosition();
	
	if (pos!=NULL)
	{
		int nItem = m_LSCListClients.GetNextSelectedItem(pos);
		auto recSelectedClient = m_vClientsFullInfo.at(nItem);

		CUpdateClientDlg oUpdateClient = new CUpdateClientDlg;
		oUpdateClient.m_strUpdatedNames = recSelectedClient.szNames;
		oUpdateClient.m_strUpdatedEmail = recSelectedClient.szEmail;
		oUpdateClient.m_strUpdatedPhone = recSelectedClient.szPhone;
		oUpdateClient.m_strUpdatedPinOrBulstat = recSelectedClient.szPinOrBulstat;
		oUpdateClient.m_strUpdatedCountry = recSelectedClient.szCountry;
		oUpdateClient.m_bUpdatedIsVerified = atoi(recSelectedClient.szIsVerified);
		oUpdateClient.m_bUpdatedMsgAgreed = atoi(recSelectedClient.szMsgAgreed);
		oUpdateClient.m_strUpdatedClientType = recSelectedClient.szClientType;
		oUpdateClient.DoModal();

		if (oUpdateClient.m_bClSuccUpdated)
		{
			int nColumnOrder = 0;
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oUpdateClient.m_strUpdatedNames));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oUpdateClient.m_strUpdatedEmail));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oUpdateClient.m_strUpdatedPhone));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oUpdateClient.m_strUpdatedPinOrBulstat));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(oUpdateClient.m_strUpdatedClientType));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(BoolToString(oUpdateClient.m_bUpdatedIsVerified)));
			m_LSCListClients.SetItemText(nItem, nColumnOrder++, _T(BoolToString(oUpdateClient.m_bUpdatedMsgAgreed)));
			m_LSCListClients.SetItemText(nItem, nColumnOrder, _T(oUpdateClient.m_strUpdatedCountry));

			strcpy_s(m_vClientsFullInfo[nItem].szNames, (const char*)oUpdateClient.m_strUpdatedNames);
			strcpy_s(m_vClientsFullInfo[nItem].szEmail, (const char*)oUpdateClient.m_strUpdatedEmail);
			strcpy_s(m_vClientsFullInfo[nItem].szPhone, (const char*)oUpdateClient.m_strUpdatedPhone);
			strcpy_s(m_vClientsFullInfo[nItem].szPinOrBulstat, (const char*)oUpdateClient.m_strUpdatedPinOrBulstat);
			strcpy_s(m_vClientsFullInfo[nItem].szClientType, (const char*)oUpdateClient.m_strUpdatedClientType);
			strcpy_s(m_vClientsFullInfo[nItem].szIsVerified, BoolToString(oUpdateClient.m_bUpdatedIsVerified));
			strcpy_s(m_vClientsFullInfo[nItem].szMsgAgreed, BoolToString(oUpdateClient.m_bUpdatedMsgAgreed));
			strcpy_s(m_vClientsFullInfo[nItem].szCountry, (const char*)oUpdateClient.m_strUpdatedCountry);
		}
		
		delete oUpdateClient;
	}
}


void CListClientsDlg::OnContextmenuDelete()
{
	POSITION pos = m_LSCListClients.GetFirstSelectedItemPosition();
	if (pos!=NULL)
	{
		int nItem = m_LSCListClients.GetNextSelectedItem(pos);

		auto recSelectedClient = m_vClientsFullInfo.at(nItem);

		CClientService oClientService;
		if (!oClientService.Delete(recSelectedClient.szPinOrBulstat))
		{
			return;
		}

		m_LSCListClients.DeleteItem(nItem);
	}
}
