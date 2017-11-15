#pragma once


// CEnvironmentDlg dialog

class CEnvironmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEnvironmentDlg)

public:
	CEnvironmentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CEnvironmentDlg();

	// Dialog Data
	enum { IDD = IDD_DIALOG_Environment };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	int  m_iAlarm1;
	int  m_iAlarm2;
	int  m_iAlarm3;
	int  m_iAlarm4;
	int  m_iAlarm5;
	int  m_iAlarm6;
	int  m_iAlarm7;
	int  m_iAlarm8;
	int  m_iAlarm9;
	int  m_iAlarm10;
};
