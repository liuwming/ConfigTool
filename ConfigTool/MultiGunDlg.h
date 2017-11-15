#pragma once
#include "afxcmn.h"

typedef struct _MULTI_GUN_INFO
{
	int iCanAddr;
	int iGunNum;
	int iSingleEnable;
}MULTI_GUN_INFO;

typedef CMap<int, int, MULTI_GUN_INFO*, MULTI_GUN_INFO*> CMultiGunMap;

// CMultiGunDlg dialog

class CMultiGunDlg:public CDialogEx
{
	DECLARE_DYNAMIC(CMultiGunDlg)

public:
	CMultiGunDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CMultiGunDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_MultiGun };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	int       m_iCanAddr;
	int       m_iGunNum;
	BOOL      m_bSingleGunOpen;
	CListCtrl m_listMultiGun;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedOk();

	BOOL ReadConfig();
	BOOL WriteConfig();
private:
	CMultiGunMap m_mapMultiGun;
	BOOL         m_bModify;
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickListMultigun(NMHDR *pNMHDR, LRESULT *pResult);
};
