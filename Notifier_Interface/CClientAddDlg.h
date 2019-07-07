#pragma once


// CTryClientAdd dialog

class CClientAddDlg : public CDialog
{
	DECLARE_DYNAMIC(CClientAddDlg)

public:
	CClientAddDlg(CWnd* pParent = nullptr);   // standard constructor
	BOOL OnInitDialog();
	virtual ~CClientAddDlg();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_CLIENTS1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	bool m_bClSuccAdded;
	CString m_strNames;
	CString m_strEmail;
	CString m_strPhone;
	CString m_strPinOrBulstat;
	CString m_strCountry;
	CString m_strClientType;
	BOOL m_bIsVerified;
	BOOL m_bMsgsAgreed;

private:
	CComboBox m_CMBCountry;
	int m_nCountryId;
	CComboBox m_CMBClientType;
	int m_nClientTypeId;
	CString m_strIsVerified;
	CString m_strMsgsAgreed;
	afx_msg void OnBnClickedButtonAddClient();
};
