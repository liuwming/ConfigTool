// SecondSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "SecondSettingDlg.h"
#include "afxdialogex.h"
#include "FXYSDlg.h"
#include "CFCDDlg.h"
#include "PhaseDlg.h"
#include "EnvironmentDlg.h"
#include "TranslateDlg.h"
#include "MultiGunDlg.h"
#include "AmmeterRangeDlg.h"
#include "AcMeterSettingDlg.h"
#include "RelaySettingDlg.h"

// CSecondSettingDlg dialog

IMPLEMENT_DYNAMIC(CSecondSettingDlg, CDialogEx)

CSecondSettingDlg::CSecondSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSecondSettingDlg::IDD, pParent)
	, m_iChargeType(0)
	, m_iLocalChargeType(-1)
	, m_strLocalChargePassword(_T(""))
	, m_bLightOpen(FALSE)
	, m_iLightOpenHour(0)
	, m_iLightOpenMinute(0)
	, m_iLightCloseHour(0)
	, m_iLightCloseMinute(0)
	, m_bOutageByDoor(FALSE)
{

}

CSecondSettingDlg::~CSecondSettingDlg()
{
}

void CSecondSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_ChargeType, m_iChargeType);
	DDX_CBIndex(pDX, IDC_COMBO_LocalChargeType, m_iLocalChargeType);
	DDX_CBIndex(pDX, IDC_COMBO_LightOpenHour, m_iLightOpenHour);
	DDX_CBIndex(pDX, IDC_COMBO_LightOpenMinute, m_iLightOpenMinute);
	DDX_CBIndex(pDX, IDC_COMBO_LightCloseHour, m_iLightCloseHour);
	DDX_CBIndex(pDX, IDC_COMBO_LightCloseMinute, m_iLightCloseMinute);
	DDX_Text(pDX, IDC_EDIT_LocalChargePassword, m_strLocalChargePassword);
	DDX_Check(pDX, IDC_CHECK_LightOpen, m_bLightOpen);
	DDX_Check(pDX, IDC_CHECK_OutageByDoor, m_bOutageByDoor);
}

BEGIN_MESSAGE_MAP(CSecondSettingDlg, CDialogEx)
	
	ON_BN_CLICKED(IDC_BUTTON_Phase, &CSecondSettingDlg::OnBnClickedButtonPhase)
	ON_BN_CLICKED(IDC_BUTTON_MultiGun, &CSecondSettingDlg::OnBnClickedButtonMultigun)
	ON_BN_CLICKED(IDC_BUTTON_FHYS, &CSecondSettingDlg::OnBnClickedButtonFhys)
	ON_BN_CLICKED(IDC_BUTTON_KeyTranslate, &CSecondSettingDlg::OnBnClickedButtonKeytranslate)
	ON_BN_CLICKED(IDC_BUTTON_Environment, &CSecondSettingDlg::OnBnClickedButtonEnvironment)
	ON_BN_CLICKED(IDC_BUTTON_CFCD, &CSecondSettingDlg::OnBnClickedButtonCfcd)
	ON_CBN_SELCHANGE(IDC_COMBO_ChargeType, &CSecondSettingDlg::OnSelchangeComboChargetype)
	ON_BN_CLICKED(IDC_BUTTON_AmmeterRangeSet, &CSecondSettingDlg::OnBnClickedButtonAmmeterrangeset)
	ON_BN_CLICKED(IDC_BUTTON_AcMeterSetting, &CSecondSettingDlg::OnBnClickedButtonAcmetersetting)
	ON_BN_CLICKED(IDC_BUTTON_RelaySetting, &CSecondSettingDlg::OnBnClickedButtonRelaysetting)
END_MESSAGE_MAP()

// CSecondSettingDlg message handlers

BOOL CSecondSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;

	for (int i = 0; i < 24; i++) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_LightOpenHour))->AddString(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_LightCloseHour))->AddString(str);
	}
	for (int i = 0; i < 60; i++)
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_LightOpenMinute))->AddString(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_LightCloseMinute))->AddString(str);
	}

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				// EXCEPTION: OCX Property Pages should return FALSE
}

void CSecondSettingDlg::OnSelchangeComboChargetype()
{
	UpdateData(TRUE);
	if (m_iChargeType == 0)
		m_iLocalChargeType = -1;
	else if (m_iChargeType == 1)
		m_iLocalChargeType = 0;
	GetDlgItem(IDC_COMBO_LocalChargeType)->EnableWindow(m_iChargeType);
	GetDlgItem(IDC_EDIT_LocalChargePassword)->EnableWindow(m_iChargeType);
	UpdateData(FALSE);
}

BOOL CSecondSettingDlg::ReadConfig(void)
{
	CString str;

	m_iChargeType = ::GetPrivateProfileInt(_T("SINGLEPILESys"), _T("MasterMode"), 1, SETTING_CONFIG);
	m_iChargeType -= 1;

	m_iLocalChargeType = ::GetPrivateProfileInt(_T("SINGLEPILESys"), _T("SlaveMode"), 1, SETTING_CONFIG);
	m_iLocalChargeType -= 1;

	::GetPrivateProfileString(_T("SINGLEPILESys"), _T("PwdCharge"), _T("100003"), m_strLocalChargePassword.GetBuffer(MAX_PATH), MAX_PATH, SETTING_CONFIG);
	m_strLocalChargePassword.ReleaseBuffer();

	::GetPrivateProfileString(_T("LIGHTSETTING"), _T("lightcontrol_enable"), _T("false"), str.GetBuffer(MAX_PATH), MAX_PATH, SETTING_CONFIG);
	m_bLightOpen = str == "true" ? TRUE : FALSE;
	str.ReleaseBuffer();

	m_iLightOpenHour = ::GetPrivateProfileInt(_T("LIGHTSETTING"), _T("lightopentime_hour"), 18, SETTING_CONFIG);
	m_iLightOpenMinute = ::GetPrivateProfileInt(_T("LIGHTSETTING"), _T("lightopentime_minute"), 0, SETTING_CONFIG);
	m_iLightCloseHour = ::GetPrivateProfileInt(_T("LIGHTSETTING"), _T("lightclosetime_hour"), 6, SETTING_CONFIG);
	m_iLightCloseMinute = ::GetPrivateProfileInt(_T("LIGHTSETTING"), _T("lightclosetime_minute"), 0, SETTING_CONFIG);

	::GetPrivateProfileString(_T("MAGNETICSWITCH"), _T("bOpenDoorPowerOutages"), _T("false"), str.GetBuffer(MAX_PATH), MAX_PATH, SETTING_CONFIG);
	m_bOutageByDoor = str == "true" ? TRUE : FALSE;
	str.ReleaseBuffer();

	UpdateData(FALSE);
	OnSelchangeComboChargetype();
	return TRUE;
}
BOOL CSecondSettingDlg::WriteConfig(void)
{
	CString str;

	UpdateData(TRUE); //将控件的值赋值给成员变量

	if (m_iChargeType == 1 && m_strLocalChargePassword.IsEmpty()) 
	{
		AfxMessageBox(_T("本地充电密码不能为空！"));
		return FALSE;
	}

	if (m_bLightOpen && m_iLightOpenHour == m_iLightCloseHour && m_iLightOpenMinute == m_iLightCloseMinute) 
	{
		AfxMessageBox(_T("灯条开始时间不能等于结束时间！"));
		return FALSE;
	}

	str.Format(_T("%d"), m_iChargeType + 1);
	::WritePrivateProfileString(_T("SINGLEPILESys"), _T("MasterMode"), str, SETTING_CONFIG);

	str.Format(_T("%d"), m_iLocalChargeType + 1);
	::WritePrivateProfileString(_T("SINGLEPILESys"), _T("SlaveMode"), str, SETTING_CONFIG);

	::WritePrivateProfileString(_T("SINGLEPILESys"), _T("PwdCharge"), m_strLocalChargePassword, SETTING_CONFIG);

	str = m_bLightOpen ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightcontrol_enable"), str, SETTING_CONFIG);

	str.Format(_T("%d"), m_iLightOpenHour);
	::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightopentime_hour"), str, SETTING_CONFIG);

	str.Format(_T("%d"), m_iLightOpenMinute);
	::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightopentime_minute"), str, SETTING_CONFIG);

	str.Format(_T("%d"), m_iLightCloseHour);
	::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightclosetime_hour"), str, SETTING_CONFIG);

	str.Format(_T("%d"), m_iLightCloseMinute);
	::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightclosetime_minute"), str, SETTING_CONFIG);

	str = m_bOutageByDoor ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("MAGNETICSWITCH"), _T("bOpenDoorPowerOutages"), str, SETTING_CONFIG);

	return TRUE;
}

void CSecondSettingDlg::OnBnClickedButtonAcmetersetting()
{
	CAcMeterSettingDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonAmmeterrangeset()
{
	CAmmeterRangeDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonCfcd()
{
	CCFCDDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonEnvironment()
{
	CEnvironmentDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonKeytranslate()
{
	CTranslateDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonRelaysetting()
{
	CRelaySettingDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonFhys()
{
	CFXYSDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonPhase()
{
	CPhaseDlg dlg;
	dlg.DoModal();
}

void CSecondSettingDlg::OnBnClickedButtonMultigun()
{
	CMultiGunDlg dlg;
	dlg.DoModal();
}

