#pragma once
#include "afxcmn.h"

// CAcMeterSettingDlg dialog

typedef struct _ACMETER_SCALE 
{
	int			iCanAddr;
	CString		strScale;
}ACMETER_SCALE;

typedef CMap<int, int, ACMETER_SCALE*, ACMETER_SCALE*> CAcMeterScaleMap;

class CAcMeterSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAcMeterSettingDlg)

public:
	CAcMeterSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAcMeterSettingDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_AcMeterSetting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL ReadConfig(void);
	BOOL WriteConfig(void);

	bool					m_bModify;
	CAcMeterScaleMap		m_mapAcMeter;

public:
	virtual BOOL OnInitDialog();

	int				m_iCanAddr;
	CString			m_strScale;
	BOOL			m_bAcMeterEnable;
	CListCtrl			m_listAcMeter;
	afx_msg void OnBnClickedCheckAcmeter();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnClickListAcmeter(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedCancel();
	afx_msg void OnDestroy();
};
