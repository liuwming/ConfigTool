#pragma once
#include "afxcmn.h"
#include "sqlite3.h"

typedef struct _PHASE_INFO
{
	int iAddr;
	int iPhase;
}PHASE_INFO;

typedef CArray<PHASE_INFO*> CPhaseArray;

class CPhaseDlg:public CDialogEx
{
	DECLARE_DYNAMIC(CPhaseDlg)

public:
	CPhaseDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPhaseDlg();

	// Dialog Data
	enum {IDD = IDD_DIALOG_Phase};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	void ReadConfig(void);
	void WriteConfig(void);

	BOOL        m_bModify;
	int         m_iCurrentIndex;
	CPhaseArray m_arPhase;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPhaseexit();
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButtonPhasesave();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnNMDblclkListPhase(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listPhase;
	int       m_iAddr;
	int       m_iPhase;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};