#pragma once


// CUpdateClientDlg dialog
#include "CClientService.h"
class CUpdateClientDlg : public CDialog
{
	DECLARE_DYNAMIC(CUpdateClientDlg)

public:
	CUpdateClientDlg(CWnd* pParent = nullptr);   // standard constructor
	BOOL OnInitDialog();
	virtual ~CUpdateClientDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_CLIENTS };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool m_bClSuccUpdated;
	CString m_strUpdatedNames;
	CString m_strUpdatedEmail;
	CString m_strUpdatedPhone;
	CString m_strUpdatedPinOrBulstat;
	CComboBox m_CMBUpdatedCountry;
	CString m_strUpdatedCountry;
	int m_nUpdatedCountryId;
	BOOL m_bUpdatedIsVerified;
	CString m_strUpdatedIsVerified;
	BOOL m_bUpdatedMsgAgreed;
	CString m_strUpdatedMsgAgreed;
	CComboBox m_CMBUpdatedClientType;
	CString m_strUpdatedClientType;
	int m_nUpdatedClientTypeId;
	afx_msg void OnBnClickedButtonUpdateClient();
};
