#pragma once
#include "afxcmn.h"

typedef struct _AMMETER_RANGE
{
	int          iCanAddr;
	CString  strRange;
	//char  szRange[10];
}AMMETER_RANGE;

typedef CMap<int, int, AMMETER_RANGE*, AMMETER_RANGE*> CAmmeterRangeMap;

// CAmmeterRangeDlg dialog

class CAmmeterRangeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAmmeterRangeDlg)

public:
	CAmmeterRangeDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CAmmeterRangeDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_AmmeterRange };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

private:
	BOOL ReadConfig(void);
	BOOL WriteConfig(void);

	CAmmeterRangeMap m_mapRange;
	BOOL m_bModify;
public:
	int           m_iCanAddr;
	CString   m_strMaxRange;
	CListCtrl  m_listAmmeterRange;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClickListAmmeterrange(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDestroy();
};
