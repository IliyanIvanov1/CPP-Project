#pragma once


// CListClientsDlg dialog
#include <vector>
#include "CClientService.h"
class CListClientsDlg : public CDialog
{
	DECLARE_DYNAMIC(CListClientsDlg)

public:
	CListClientsDlg(CWnd* pParent = nullptr);   // standard constructor
	BOOL OnInitDialog();
	bool InsertItems();
	virtual ~CListClientsDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIST_CLIENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_LSCListClients;
	vector<ClientFullInfo> m_vClientsFullInfo;
public:
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnContextmenuAdd();
	afx_msg void OnContextmenuUpdate();
	afx_msg void OnContextmenuDelete();

};
