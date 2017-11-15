#pragma once
#include "afxcmn.h"

typedef struct _DEVICE_RELAY_INFO 
{
	int iDevice;
	int iRelay;
}DEVICE_RELAY_INFO;

typedef CMap<int, int, DEVICE_RELAY_INFO*, DEVICE_RELAY_INFO*> CRelaySettingMap;

#define DEVICE_LIGHT_BELT       _T("µÆ´ø")
#define DEVICE_RELAY		 _T("¼ÌµçÆ÷")
#define DEVICE_GREEN_LIGHT    _T("ÂÌµÆ")
#define DEVICE_RED_LIGHT	 _T("»ÆµÆ")
#define RELAY_K1	                 _T("K1")
#define RELAY_K2	                 _T("K2")
#define RELAY_K3	                 _T("K3")
#define RELAY_K4	                 _T("K4")

// CRelaySettingDlg dialog

class CRelaySettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRelaySettingDlg)

public:
	CRelaySettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRelaySettingDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_RelaySetting }; 

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	BOOL   ReadConfig();
	BOOL   WriteConfig();
	CRelaySettingMap  m_mapRelay;
	bool     m_bModify;
public:
	virtual BOOL OnInitDialog();
	int      m_iRelayIndex;
	//	int m_iRelayType;
	CListCtrl m_listRelaySetting;
	afx_msg void OnBnClickedButtonAdd();
	int m_iDeviceType;
	int m_iRelayType;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnClickListRelaysetting(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};
