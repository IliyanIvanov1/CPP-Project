#pragma once


// CNormalUserDlg dialog

class CNormalUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CNormalUserDlg)

public:
	CNormalUserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CNormalUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NORMAL_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonNewCampaign();
	afx_msg void OnBnClickedButtonListCampaigns();
	afx_msg void OnBnClickedButtonEditCampaign();
};
