#pragma once


// CTranslateDlg dialog

class CTranslateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTranslateDlg)

public:
	CTranslateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTranslateDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_Translate }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CString m_strKey1;
	CString m_strKey2;
	afx_msg void OnBnClickedButtonTranslate();
	//	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};
