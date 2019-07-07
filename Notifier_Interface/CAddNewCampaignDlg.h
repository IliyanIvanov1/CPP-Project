#pragma once


// CAddNewCampaignDlg dialog

class CAddNewCampaignDlg : public CDialog
{
	DECLARE_DYNAMIC(CAddNewCampaignDlg)

public:
	CAddNewCampaignDlg(CWnd* pParent = nullptr);   // standard constructor

	BOOL OnInitDialog();

	virtual ~CAddNewCampaignDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_NEW_CAMPAIGN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strName;
	CComboBox m_CMBFilter;
	CString m_strFilter;
	COleDateTime m_DTCValidFrom;
	CDateTimeCtrl m_oValidFrom;
	COleDateTime m_DTCValidUntil;
	CDateTimeCtrl m_oValidUntil;
	afx_msg void OnBnClickedButtonSubmit();
};
