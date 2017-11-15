#pragma once

// CSecondSettingDlg dialog

class CSecondSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSecondSettingDlg)

public:
	CSecondSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSecondSettingDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_SecondSetting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	BOOL ReadConfig(void);
	BOOL WriteConfig(void);

	afx_msg void OnBnClickedButtonKeytranslate();
	afx_msg void OnBnClickedButtonFhys();
	afx_msg void OnBnClickedButtonPhase();
	afx_msg void OnBnClickedButtonEnvironment();
	afx_msg void OnBnClickedButtonMultigun();
	afx_msg void OnBnClickedButtonAmmeterrangeset();
	afx_msg void OnBnClickedButtonAcmetersetting();
	afx_msg void OnBnClickedButtonCfcd();
	afx_msg void OnBnClickedButtonRelaysetting();
	afx_msg void OnSelchangeComboChargetype();
	int m_iChargeType;
	int m_iLocalChargeType;
	int m_iLightOpenHour;
	int m_iLightOpenMinute;
	int m_iLightCloseHour;
	int m_iLightCloseMinute;
	BOOL m_bOutageByDoor;
	BOOL m_bLightOpen;
	CString m_strLocalChargePassword;

	//DECLARE_MESSAGE_MAP()
	//afx_msg void OnBnClickedCancel();
};
