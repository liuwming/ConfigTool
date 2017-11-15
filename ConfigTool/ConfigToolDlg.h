// ConfigToolDlg.h : header file

#pragma once
#include "afxcmn.h"
#include "ModuleDlg.h"
#include "FirstSettingDlg.h"
#include "SecondSettingDlg.h"

// CConfigToolDlg dialog
class CConfigToolDlg : public CDialog
{
// Construction
public:
	CConfigToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFIGTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

// Implementation
protected:
    HICON   m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

 private:
	CTabCtrl  m_tabMain;
	BOOL      ExecCommand(CString strCmdLine);
	BOOL      DeleteTempDirectory(CString strPath);
	CModuleDlg        m_dlgModule;
    CFirstSettingDlg  m_dlgFirstSetting;
	CSecondSettingDlg m_dlgSecondSetting;
    
public:
	afx_msg void OnMenuAbout();
	afx_msg void OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClickedButtonGenerate();
	afx_msg void OnClickedButtonExport();
	int WriteDefaultSetting(void);
	int WriteDefaultModule(void);
};
