#pragma once
#include "afxcmn.h"
#include "afxdtctl.h"
#include "sqlite3.h"
#include "numberedit.h"

typedef struct _CFCD_INFO
{
	int iId;
	int iPeriod;
	int iStartHour;
	int iStartMinute;
	int iStopHour;
	int iStopMinute;
	int iSoc;
	int iCurrent;
	int iStatus;
}CFCD_INFO;

typedef CArray<CFCD_INFO> CCFCDArray;

class CCFCDDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CCFCDDlg)

public:
	CCFCDDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCFCDDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_CFCD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	//void ReadConfig(void);
	//void WriteConfig(void);
	CCFCDArray   m_arCache[4];
	BOOL			   m_bModify;
	int				   m_iCurrentIndex;

public:
	virtual BOOL  OnInitDialog();
	
	CListCtrl          m_listCFCD;
	int                   m_iPeriod;
	int                   m_iStartHour;
	int                   m_iStartMinute;
	int                   m_iStopHour;
	int                   m_iStopMinute;
	CString            m_strSOC;
	CString            m_strCurrent;
	CNumberEdit  m_edtSOC;
	CNumberEdit  m_edtCurrent;
	BOOL              m_bCFCDEnable;
	BOOL              m_bCarPrioty;
	afx_msg void  OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void  OnBnClickedCheckCfcdenable();
	afx_msg void  OnBnClickedButtonCfcdexit();
	afx_msg void  OnBnClickedButtonCfcdsave();
	afx_msg void  OnDestroy();
	afx_msg void  OnBnClickedButtonCfcddelete();
	afx_msg void  OnCbnSelchangeComboPeriod();
	afx_msg void  OnNMDblclkListCfcd(NMHDR *pNMHDR, LRESULT *pResult); afx_msg void OnBnClickedButtonCfcdadd();
};
