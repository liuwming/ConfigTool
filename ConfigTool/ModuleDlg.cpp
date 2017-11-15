// ModuleDlg.cpp : implementation file

#include "stdafx.h"
#include "ConfigTool.h"
#include "ModuleDlg.h"
#include "afxdialogex.h"

// CModuleDlg dialog

IMPLEMENT_DYNAMIC(CModuleDlg, CDialogEx)

CModuleDlg::CModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CModuleDlg::IDD, pParent)
	, m_bCharge(FALSE)
	, m_bSchedule(FALSE)
	, m_bSetting(TRUE)
	, m_bUpdate(TRUE)
	, m_bReal(TRUE)
	, m_bCache(TRUE)
	, m_bDatabase(TRUE)
	, m_bLog(TRUE)
	, m_bEquipment(FALSE)
	, m_bAmmeter(FALSE)
	, m_bHumiture(FALSE)
	, m_bTicket(FALSE)
	, m_bCard(FALSE)
	, m_bScreen(FALSE)
	, m_bGPIO(FALSE)
	, m_bWebServer(FALSE)
	, m_bScreenSinglePile(FALSE)
	, m_bScanner(FALSE)
{

}

CModuleDlg::~CModuleDlg()
{
}

void CModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_Charge, m_bCharge);
	DDX_Check(pDX, IDC_CHECK_Schedule, m_bSchedule);
	DDX_Check(pDX, IDC_CHECK_Setting, m_bSetting);
	DDX_Check(pDX, IDC_CHECK_Update, m_bUpdate);
	DDX_Check(pDX, IDC_CHECK_Real, m_bReal);
	DDX_Check(pDX, IDC_CHECK_Cache, m_bCache);
	DDX_Check(pDX, IDC_CHECK_Database, m_bDatabase);
	DDX_Check(pDX, IDC_CHECK_Log, m_bLog);
	DDX_Check(pDX, IDC_CHECK_Remote, m_bRemote);
	DDX_Check(pDX, IDC_CHECK_Local, m_bLocal);
	DDX_Check(pDX, IDC_CHECK_Equipment, m_bEquipment);
	DDX_Check(pDX, IDC_CHECK_Ammeter, m_bAmmeter);
	DDX_Check(pDX, IDC_CHECK_Humiture, m_bHumiture);
	DDX_Check(pDX, IDC_CHECK_Ticket, m_bTicket);
	DDX_Check(pDX, IDC_CHECK_Card, m_bCard);
	DDX_Check(pDX, IDC_CHECK_Screen, m_bScreen);
	DDX_Check(pDX, IDC_CHECK_GPIO, m_bGPIO);

	DDX_Check(pDX, IDC_CHECK_DevManager, m_bDevManager);
	DDX_Check(pDX, IDC_CHECK_WebServer, m_bWebServer);
	DDX_Check(pDX, IDC_CHECK_ScreenSinglePile, m_bScreenSinglePile);
	DDX_Check(pDX, IDC_CHECK_Scanner, m_bScanner);
}

BEGIN_MESSAGE_MAP(CModuleDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_Screen, &CModuleDlg::OnBnClickedCheckScreen)
	ON_BN_CLICKED(IDC_CHECK_ScreenSinglePile, &CModuleDlg::OnBnClickedCheckScreensinglepile)
END_MESSAGE_MAP()

// CModuleDlg message handlers

BOOL CModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CModuleDlg::WriteConfig(void)
{
	CString str, strFile = _T(".\\libconfig.ini");

	UpdateData(TRUE);

	::WritePrivateProfileString(_T("CHARGESERVICE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("CHARGESERVICE"), _T("library"), _T("libChargeService.so"), strFile);
	str = m_bCharge ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("CHARGESERVICE"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SCHEDULE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("SCHEDULE"), _T("library"), _T("libLoadSchedule.so"), strFile);
	str = m_bSchedule ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SCHEDULE"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SERVER0"), _T("type"), _T("remote"), strFile);
	::WritePrivateProfileString(_T("SERVER0"), _T("library"), _T("libIEC104Server.so"), strFile);
	str = m_bRemote ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SERVER0"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SERVER1"), _T("type"), _T("local"), strFile);
	::WritePrivateProfileString(_T("SERVER1"), _T("library"), _T("libIEC104Server.so"), strFile);
	str = m_bLocal ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SERVER1"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("library"), _T("libChargeEquipment.so"), strFile);
	str = m_bEquipment ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("AMMETER"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("AMMETER"), _T("library"), _T("libAmmeter.so"), strFile);
	str = m_bAmmeter ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("AMMETER"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("TEMPHUMI"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("TEMPHUMI"), _T("library"), _T("libTempHumi.so"), strFile);
	str = m_bHumiture ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("TEMPHUMI"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("CARD"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("CARD"), _T("library"), _T("libCard.so"), strFile);
	str = m_bCard ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("CARD"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SCREEN"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("SCREEN"), _T("library"), _T("libSerialScreen.so"), strFile);
	str = m_bScreen ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SCREEN"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("library"), _T("libSerialScreenSinglePile.so"), strFile);
	str = m_bScreenSinglePile ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("GPIO"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("GPIO"), _T("library"), _T("libGPIO.so"), strFile);
	str = m_bGPIO ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("GPIO"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("UPDATE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("UPDATE"), _T("library"), _T("libUpdate.so"), strFile);
	str = m_bUpdate ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("UPDATE"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("library"), _T("libDeviceManage.so"), strFile);
	str = m_bDevManager ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("WEBSERVER"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("WEBSERVER"), _T("library"), _T("libWebServer.so"), strFile);
	str = m_bWebServer ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("WEBSERVER"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("TICKET"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("TICKET"), _T("library"), _T("libTicketDev.so"), strFile);
	str = m_bTicket ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("TICKET"), _T("enable"), str, strFile);

	::WritePrivateProfileString(_T("SCANCODE"), _T("type"), _T("device"), strFile);
	::WritePrivateProfileString(_T("SCANCODE"), _T("library"), _T("libScanCode.so"), strFile);
	str = m_bScanner ? _T("true") : _T("false");
	::WritePrivateProfileString(_T("SCANCODE"), _T("enable"), str, strFile);

	return TRUE;
}

BOOL CModuleDlg::ReadConfig(void)
{
	CString str, strFile = _T(".\\libconfig.ini");

	::GetPrivateProfileString(_T("CHARGESERVICE"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bCharge = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SCHEDULE"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bSchedule = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SERVER0"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bRemote = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SERVER1"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bLocal = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("CHARGEEQUIPMENT"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bEquipment = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("AMMETER"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bAmmeter = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("TEMPHUMI"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bHumiture = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("CARD"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bCard = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SCREEN"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bScreen = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SCREENSINGLEPILE"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bScreenSinglePile = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("GPIO"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bGPIO = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("DEVICEMANAGE"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bDevManager = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("WEBSERVER"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bWebServer = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("TICKET"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bTicket = str == "true" ? TRUE : FALSE;

	::GetPrivateProfileString(_T("SCANCODE"), _T("enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	m_bScanner = str == "true" ? TRUE : FALSE;

	UpdateData(FALSE);

	return TRUE;
}

void CModuleDlg::OnBnClickedCheckScreen()
{
	UpdateData(TRUE);
	if (m_bScreen)
		m_bScreenSinglePile = FALSE;
	UpdateData(FALSE);
}

void CModuleDlg::OnBnClickedCheckScreensinglepile()
{
	UpdateData(TRUE);
	if (m_bScreenSinglePile)
		m_bScreen = FALSE;
	UpdateData(FALSE);
}