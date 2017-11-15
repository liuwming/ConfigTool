// EnvironmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "EnvironmentDlg.h"
#include "afxdialogex.h"


// CEnvironmentDlg dialog

IMPLEMENT_DYNAMIC(CEnvironmentDlg, CDialogEx)

CEnvironmentDlg::CEnvironmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CEnvironmentDlg::IDD, pParent)
{

	m_iAlarm1 = 0;
	m_iAlarm2 = 0;
	m_iAlarm3 = 0;
	m_iAlarm4 = 0;
	m_iAlarm5 = 0;
	m_iAlarm6 = 0;
	m_iAlarm7 = 0;
	m_iAlarm8 = 0;
	m_iAlarm9 = 0;
	m_iAlarm10 = 0;
}

CEnvironmentDlg::~CEnvironmentDlg()
{
}

void CEnvironmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm1, m_iAlarm1);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm10, m_iAlarm10);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm2, m_iAlarm2);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm3, m_iAlarm3);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm4, m_iAlarm4);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm5, m_iAlarm5);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm6, m_iAlarm6);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm7, m_iAlarm7);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm8, m_iAlarm8);
	DDX_CBIndex(pDX, IDC_COMBO_Alarm9, m_iAlarm9);
}


BEGIN_MESSAGE_MAP(CEnvironmentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CEnvironmentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CEnvironmentDlg message handlers


BOOL CEnvironmentDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str, strFile = _T(".\\config.ini");
	m_iAlarm1 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN1"), 0, strFile);
	m_iAlarm2 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN2"), 0, strFile);
	m_iAlarm3 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN3"), 0, strFile);
	m_iAlarm4 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN4"), 0, strFile);
	m_iAlarm5 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN5"), 0, strFile);
	m_iAlarm6 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN6"), 0, strFile);
	m_iAlarm7 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN7"), 0, strFile);
	m_iAlarm8 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN8"), 0, strFile);
	m_iAlarm9 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN9"), 0, strFile);
	m_iAlarm10 = ::GetPrivateProfileInt(_T("IOIN"), _T("DIN10"), 0, strFile);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}


void CEnvironmentDlg::OnBnClickedOk()
{
	CString str, strFile = _T(".\\config.ini");

	UpdateData(TRUE);

	str.Format(_T("%d"), m_iAlarm1);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN1"), str, strFile);

	str.Format(_T("%d"), m_iAlarm2);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN2"), str, strFile);

	str.Format(_T("%d"), m_iAlarm3);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN3"), str, strFile);

	str.Format(_T("%d"), m_iAlarm4);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN4"), str, strFile);

	str.Format(_T("%d"), m_iAlarm5);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN5"), str, strFile);

	str.Format(_T("%d"), m_iAlarm6);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN6"), str, strFile);

	str.Format(_T("%d"), m_iAlarm7);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN7"), str, strFile);

	str.Format(_T("%d"), m_iAlarm8);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN8"), str, strFile);

	str.Format(_T("%d"), m_iAlarm9);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN9"), str, strFile);

	str.Format(_T("%d"), m_iAlarm10);
	::WritePrivateProfileString(_T("IOIN"), _T("DIN10"), str, strFile);

	CDialogEx::OnOK();
}
