#pragma once


// CRegisterUserDlg dialog

class CRegisterUserDlg : public CDialog
{
	DECLARE_DYNAMIC(CRegisterUserDlg)

public:
	CRegisterUserDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CRegisterUserDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_REGISTER_USER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_strRegNames;
	CString m_strRegUsername;
	CString m_strRegPassword;
	CString m_strRegConfPassword;
	afx_msg void OnBnClickedButtonRegister();
};
