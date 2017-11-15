// FXYSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "FXYSDlg.h"
#include "afxdialogex.h"

// CFXYSDlg dialog

IMPLEMENT_DYNAMIC(CFXYSDlg, CDialogEx)

CFXYSDlg::CFXYSDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFXYSDlg::IDD, pParent)
	, m_strCCUCount(_T(""))
	, m_strLimitPower(_T(""))
	, m_strSafePower(_T(""))
	, m_strLocalLimitPower(_T(""))
	, m_iAutoEnable(1)
	, m_iRemoteEnable(1)
	, m_iLocalEnable(1)
	, m_bFHYSEnable(FALSE)
{

}

CFXYSDlg::~CFXYSDlg()
{
}

void CFXYSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CCUCount, m_strCCUCount);
	DDX_Text(pDX, IDC_EDIT_LimitPower, m_strLimitPower);
	DDX_Text(pDX, IDC_EDIT_SafePower, m_strSafePower);
	DDX_Text(pDX, IDC_EDIT_LocalLimitPower, m_strLocalLimitPower);
	DDX_Radio(pDX, IDC_RADIO_Auto, m_iAutoEnable);
	DDX_Radio(pDX, IDC_RADIO_Remote, m_iRemoteEnable);
	DDX_Radio(pDX, IDC_RADIO_Local, m_iLocalEnable);
	DDX_Control(pDX, IDC_EDIT_CCUCount, m_edtCCUCount);
	DDX_Control(pDX, IDC_EDIT_LimitPower, m_edtLimitPower);
	DDX_Control(pDX, IDC_EDIT_SafePower, m_edtSafePower);
	DDX_Control(pDX, IDC_EDIT_LocalLimitPower, m_edtLocalLimitPower);
	DDX_Check(pDX, IDC_CHECK_FHYSEnable, m_bFHYSEnable);
}

BEGIN_MESSAGE_MAP(CFXYSDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_FHYSExit, &CFXYSDlg::OnBnClickedButtonFhysexit)
	ON_BN_CLICKED(IDC_BUTTON_FXYSSave, &CFXYSDlg::OnBnClickedButtonFxyssave)
	ON_BN_CLICKED(IDC_CHECK_FHYSEnable, &CFXYSDlg::OnBnClickedCheckFhysenable)
END_MESSAGE_MAP()

BOOL CFXYSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ReadConfig();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CFXYSDlg::OnBnClickedButtonFhysexit()
{
	CDialogEx::OnCancel();
}

void CFXYSDlg::OnBnClickedButtonFxyssave()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CFXYSDlg::WriteConfig(void)
{
	CString str, strFile = _T(".\\config.ini");

	UpdateData(TRUE);

	str = m_bFHYSEnable ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("PowerLimit_Enable"), str, strFile);
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("CCUCount"), m_strCCUCount, strFile);
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("StationLimitPower"), m_strLimitPower, strFile);
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SafeLimitPower"), m_strSafePower, strFile);
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual"), m_strLocalLimitPower, strFile);
	str = m_iAutoEnable ? _T("false") : _T("true");
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Ammeter_Enable"), str, strFile);
	str = m_iRemoteEnable ? _T("false") : _T("true");
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Server_Enable"), str, strFile);
	str = m_iLocalEnable ? _T("false") : _T("true");
	::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual_Enable"), str, strFile);
}

void CFXYSDlg::ReadConfig(void)
{
	CString str, strFile = _T(".\\config.ini");

	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("PowerLimit_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_bFHYSEnable = str == _T("true") ? 1 : 0;
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("CCUCount"), _T(""), m_strCCUCount.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("StationLimitPower"), _T(""), m_strLimitPower.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("SafeLimitPower"), _T(""), m_strSafePower.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual"), _T(""), m_strLocalLimitPower.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Ammeter_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_iAutoEnable = str == _T("true") ? 0 : 1;
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Server_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_iRemoteEnable = str == _T("true") ? 0 : 1;
	::GetPrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_iLocalEnable = str == _T("true") ? 0 : 1;

	UpdateData(FALSE);

	OnBnClickedCheckFhysenable();
}

void CFXYSDlg::OnBnClickedCheckFhysenable()
{
	UpdateData(TRUE);

	GetDlgItem(IDC_EDIT_CCUCount)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_EDIT_LimitPower)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_EDIT_SafePower)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_EDIT_LocalLimitPower)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Auto)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Auto_Close)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Remote)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Remote_Close)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Local)->EnableWindow(m_bFHYSEnable);
	GetDlgItem(IDC_RADIO_Local_Close)->EnableWindow(m_bFHYSEnable);
}
