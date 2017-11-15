#pragma once
#include "numberedit.h"


// CFXYSDlg dialog

class CFXYSDlg:public CDialogEx
{
	DECLARE_DYNAMIC(CFXYSDlg)

public:
	CFXYSDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFXYSDlg();

	// Dialog Data
	enum {IDD = IDD_DIALOG_FXYS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonFhysexit();
	afx_msg void OnBnClickedButtonFxyssave();
	CString m_strCCUCount;
	CString m_strLimitPower;
	CString m_strSafePower;
	CString m_strLocalLimitPower;
	int		m_iAutoEnable;
	int		m_iRemoteEnable;
	int		m_iLocalEnable;
	BOOL	m_bFHYSEnable;
	CNumberEdit m_edtCCUCount;
	CNumberEdit m_edtLimitPower;
	CNumberEdit m_edtSafePower;
	CNumberEdit m_edtLocalLimitPower;
	void WriteConfig(void);
	void ReadConfig(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedCheckFhysenable();
};
