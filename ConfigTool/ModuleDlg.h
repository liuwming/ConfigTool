#pragma once
#include "afxwin.h"

// CModuleDlg dialog
class CModuleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CModuleDlg)

public:
	CModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CModuleDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_Module };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	BOOL WriteConfig(void);
	BOOL ReadConfig(void);
	BOOL m_bCharge;
	BOOL m_bSchedule;
	BOOL m_bSetting;
	BOOL m_bUpdate;
	BOOL m_bReal;
	BOOL m_bCache;
	BOOL m_bDatabase;
	BOOL m_bLog;
	BOOL m_bRemote;
	BOOL m_bLocal;
	BOOL m_bEquipment;
	BOOL m_bAmmeter;
	BOOL m_bHumiture;
	BOOL m_bTicket;
	BOOL m_bCard;
	BOOL m_bScreen;
	BOOL m_bGPIO;
	BOOL m_bDevManager;
	BOOL m_bWebServer;
	BOOL m_bScreenSinglePile;
	BOOL m_bScanner;
	afx_msg void OnBnClickedCheckScreen();
	afx_msg void OnBnClickedCheckScreensinglepile();
};
