#pragma once


// CAdminUserDlg dialog

class CAdminUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CAdminUserDlg)

public:
	CAdminUserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAdminUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADMIN_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddClient();
	afx_msg void OnBnClickedButtonAdminNewCampaign();
	afx_msg void OnBnClickedButtonListClients();
};
