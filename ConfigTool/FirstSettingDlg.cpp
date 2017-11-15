// SettingDlg.cpp : implementation file

#include "stdafx.h"
#include "ConfigTool.h"
#include "FirstSettingDlg.h"
#include "afxdialogex.h"

// CFirstSettingDlg dialog

IMPLEMENT_DYNAMIC(CFirstSettingDlg, CDialogEx)

CFirstSettingDlg::CFirstSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFirstSettingDlg::IDD, pParent)
	, m_strDirect(_T(""))
	, m_strSingle(_T(""))
	, m_strThree(_T(""))
	, m_iPassword(0)
	, m_iTEUIType(0)
	, m_iBoard(1)
	, m_iAbnormal(1)
	, m_iCardType(1)
	, m_iShowButton(1)
	, m_iVinType(0)
	, m_iVinAuto(1)
	, m_strNet1Ip(_T(""))
	, m_strNet1Mask(_T(""))
	, m_strNet1Gateway(_T(""))
	, m_strNet2Ip(_T(""))
	, m_strNet2Mask(_T(""))
	, m_strNet2Gateway(_T(""))
	, m_strDNS(_T(""))
	, m_strCan0Addr(_T(""))
	, m_strCan0Baud(_T(""))
	, m_strCan1Addr(_T(""))
	, m_strCan1Baud(_T(""))
	, m_strRemoteKey(_T(""))
	, m_iRemoteEncrypt(0)
	, m_strRemoteIp(_T(""))
	, m_strRemotePort(_T(""))
	, m_strRemoteStation(_T(""))
	, m_strLocalKey(_T(""))
	, m_iLocalEncrypt(0)
	, m_strLocalIp(_T(""))
	, m_strLocalPort(_T(""))
	, m_strLocalStation(_T(""))
	, m_strWebUrl(_T(""))
	, m_iCardAuto(0)
{
	m_edtDirect.SetTextLength(3);
	m_edtSingle.SetTextLength(3);
	m_edtThree.SetTextLength(3);
	m_edtCan0Addr.SetTextLength(3);
	m_edtCan1Addr.SetTextLength(3);
	m_edtRemotePort.SetTextLength(5);
	m_edtLocalPort.SetTextLength(5);
	m_edtCan0Baud.SetTextLength(7);
	m_edtCan1Baud.SetTextLength(7);
	m_strWebPort = _T("");
	m_strOperatorId = _T("");
	m_strOperatorSecret = _T("");
	m_strDataSecret = _T("");
	m_strWebAesKey = _T("");
	m_strWebAesIV = _T("");
	m_iTicketOpen = 0;
	m_iCardMultiChoose = 1;
	m_iSinglePileGroup = 1;
}

CFirstSettingDlg::~CFirstSettingDlg()
{
}

void CFirstSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_EDIT_Direct, m_strDirect);
	DDX_Text(pDX, IDC_EDIT_Single, m_strSingle);
	DDX_Text(pDX, IDC_EDIT_Three, m_strThree);
	DDX_Text(pDX, IDC_EDIT_Net1Ip, m_strNet1Ip);
	DDX_Text(pDX, IDC_EDIT_Net1Mask, m_strNet1Mask);
	DDX_Text(pDX, IDC_EDIT_Net1Gateway, m_strNet1Gateway);
	DDX_Text(pDX, IDC_EDIT_Net2IP, m_strNet2Ip);
	DDX_Text(pDX, IDC_EDIT_Net2Mask, m_strNet2Mask);
	DDX_Text(pDX, IDC_EDIT_Net2Gateway, m_strNet2Gateway);
	DDX_Text(pDX, IDC_EDIT_DNS, m_strDNS);
	DDX_Text(pDX, IDC_EDIT_Can0Addr, m_strCan0Addr);
	DDX_Text(pDX, IDC_EDIT_Can0Baud, m_strCan0Baud);
	DDX_Text(pDX, IDC_EDIT_Can1Addr, m_strCan1Addr);
	DDX_Text(pDX, IDC_EDIT_Can1Baud, m_strCan1Baud);
	DDX_Text(pDX, IDC_EDIT_RemoteKey, m_strRemoteKey);
	DDX_Text(pDX, IDC_EDIT_RemoteIp, m_strRemoteIp);
	DDX_Text(pDX, IDC_EDIT_RemotePort, m_strRemotePort);
	DDX_Text(pDX, IDC_EDIT_RemoteStation, m_strRemoteStation);
	DDX_Text(pDX, IDC_EDIT_LocalKey, m_strLocalKey);
	DDX_Text(pDX, IDC_EDIT_WebPort, m_strWebPort);
	DDX_Text(pDX, IDC_EDIT_OperatorId, m_strOperatorId);
	DDX_Text(pDX, IDC_EDIT_OperatorSecret, m_strOperatorSecret);
	DDX_Text(pDX, IDC_EDIT_DataSecret, m_strDataSecret);
	DDX_Text(pDX, IDC_EDIT_WebAesIV, m_strWebAesIV);
	DDX_Text(pDX, IDC_EDIT_WebAesKey, m_strWebAesKey);
	DDX_Text(pDX, IDC_EDIT_LocalIp, m_strLocalIp);
	DDX_Text(pDX, IDC_EDIT_LocalPort, m_strLocalPort);
	DDX_Text(pDX, IDC_EDIT_LocalStation, m_strLocalStation);
	DDX_Text(pDX, IDC_EDIT_Password, m_iPassword);
	DDX_CBIndex(pDX, IDC_COMBO_TEUIType, m_iTEUIType);
	DDX_CBIndex(pDX, IDC_COMBO_Board, m_iBoard);
	DDX_CBIndex(pDX, IDC_COMBO_CardType, m_iCardType);
	DDX_CBIndex(pDX, IDC_COMBO_VINType, m_iVinType);
	DDX_Radio(pDX, IDC_RADIO_ButtonOpen, m_iShowButton);
	DDX_Radio(pDX, IDC_RADIO_VINAutoOpen, m_iVinAuto);
	DDX_Radio(pDX, IDC_RADIO_RemoteEncryptOpen, m_iRemoteEncrypt);
	DDX_Radio(pDX, IDC_RADIO_LocalEncryptOpen, m_iLocalEncrypt);
	DDX_Radio(pDX, IDC_RADIO_TicketOpen, m_iTicketOpen);
	DDX_Radio(pDX, IDC_RADIO_CardMultiOpen, m_iCardMultiChoose);
	DDX_Radio(pDX, IDC_RADIO_SinglePileGroupOpen, m_iSinglePileGroup);
	DDX_Radio(pDX, IDC_RADIO_AbnormalOpen, m_iAbnormal);
	DDX_Radio(pDX, IDC_RADIO_CardAutoOpen, m_iCardAuto);
	DDX_Control(pDX, IDC_EDIT_Direct, m_edtDirect);
	DDX_Control(pDX, IDC_EDIT_Single, m_edtSingle);
	DDX_Control(pDX, IDC_EDIT_Three, m_edtThree);
	DDX_Control(pDX, IDC_EDIT_Password, m_edtPassword);
	DDX_Control(pDX, IDC_EDIT_Can0Addr, m_edtCan0Addr);
	DDX_Control(pDX, IDC_EDIT_Can0Baud, m_edtCan0Baud);
	DDX_Control(pDX, IDC_EDIT_Can1Addr, m_edtCan1Addr);
	DDX_Control(pDX, IDC_EDIT_Can1Baud, m_edtCan1Baud);
	DDX_Control(pDX, IDC_EDIT_RemotePort, m_edtRemotePort);
	DDX_Control(pDX, IDC_EDIT_LocalPort, m_edtLocalPort);
	DDX_CBString(pDX, IDC_COMBO_WebUrl, m_strWebUrl);
}

BEGIN_MESSAGE_MAP(CFirstSettingDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_COMBO_WebUrl, &CFirstSettingDlg::OnCbnSelchangeComboWeburl)
END_MESSAGE_MAP()

BOOL CFirstSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CRect rc, rect;
	int w, h;

	GetWindowRect(rect);
	w = rect.Width();
	h = rect.Height();

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CFirstSettingDlg::ReadConfig(void)
{
	USES_CONVERSION; 

	CString str, strFile = _T(".\\config.ini");

	::GetPrivateProfileString(_T("CSCUSys"), _T("DirectCurrent"), _T(""), m_strDirect.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_strDirect.ReleaseBuffer();
	::GetPrivateProfileString(_T("CSCUSys"), _T("SinglePhase"), _T(""), m_strSingle.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_strSingle.ReleaseBuffer();
	::GetPrivateProfileString(_T("CSCUSys"), _T("ThreePhase"), _T(""), m_strThree.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_strThree.ReleaseBuffer();
	::GetPrivateProfileString(_T("CSCUSys"), _T("Password"), _T("300001"), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	str.ReleaseBuffer();
	_stscanf_s(str, _T("%d"), &m_iPassword);

	m_iTEUIType = ::GetPrivateProfileInt(_T("CSCUSys"), _T("NormalCard"), 1, strFile);
	m_iTEUIType -= 1;
	m_iBoard = ::GetPrivateProfileInt(_T("CSCUSys"), _T("BoardType"), 2, strFile);
	m_iBoard -= 1;
	m_iAbnormal = ::GetPrivateProfileInt(_T("CHARGE"), _T("EnergyFilter"), 0, strFile); 
	m_iAbnormal = !m_iAbnormal;
	m_iCardType =::GetPrivateProfileInt(_T("CHARGE"), _T("CardType"), 2, strFile);  
	m_iCardType -= 1;
	m_iShowButton =::GetPrivateProfileInt(_T("CHARGE"), _T("LocalStop"), 1, strFile);  	
	m_iShowButton = !m_iShowButton;
	m_iVinType = ::GetPrivateProfileInt(_T("CHARGE"), _T("VinType"), 3, strFile);  
	m_iVinType -= 1;
	m_iCardAuto = ::GetPrivateProfileInt(_T("CHARGE"), _T("CardAuto"), 0, strFile); 
	m_iCardAuto = !m_iCardAuto;
	m_iVinAuto = ::GetPrivateProfileInt(_T("CHARGE"), _T("VinAuto"), 0, strFile); 
	m_iVinAuto = !m_iVinAuto;
	m_iTicketOpen = ::GetPrivateProfileInt(_T("CHARGE"), _T("TicketEnable"), 0, strFile); 
	m_iTicketOpen = !m_iTicketOpen;
	m_iCardMultiChoose = ::GetPrivateProfileInt(_T("CHARGE"), _T("SwitpingCardMultChooseMode"), 0, strFile); 
	m_iCardMultiChoose = !m_iCardMultiChoose;
	m_iSinglePileGroup = ::GetPrivateProfileInt(_T("CHARGE"), _T("DevType"), 0, strFile); 
	m_iSinglePileGroup = !m_iSinglePileGroup;

	::GetPrivateProfileString(_T("NET_0"), _T("IP"), _T(""), m_strNet1Ip.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet1Ip.ReleaseBuffer();
	::GetPrivateProfileString(_T("NET_0"), _T("NetMask"), _T(""), m_strNet1Mask.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet1Mask.ReleaseBuffer();
	::GetPrivateProfileString(_T("NET_0"), _T("Gateway"), _T(""), m_strNet1Gateway.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet1Gateway.ReleaseBuffer();
	::GetPrivateProfileString(_T("NET_1"), _T("IP"), _T(""), m_strNet2Ip.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet2Ip.ReleaseBuffer();
	::GetPrivateProfileString(_T("NET_1"), _T("NetMask"), _T(""), m_strNet2Mask.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet2Mask.ReleaseBuffer();
	::GetPrivateProfileString(_T("NET_1"), _T("Gateway"), _T(""), m_strNet2Gateway.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strNet2Gateway.ReleaseBuffer();
	::GetPrivateProfileString(_T("CSCUSys"), _T("DNS"), _T(""), m_strDNS.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strDNS.ReleaseBuffer();
	::GetPrivateProfileString(_T("CAN_0"), _T("CanAddr"), _T("250"), m_strCan0Addr.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strCan0Addr.ReleaseBuffer();
	::GetPrivateProfileString(_T("CAN_0"), _T("Rate"), _T("100000"), m_strCan0Baud.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strCan0Baud.ReleaseBuffer();
	::GetPrivateProfileString(_T("CAN_1"), _T("CanAddr"), _T("250"), m_strCan1Addr.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strCan1Addr.ReleaseBuffer();
	::GetPrivateProfileString(_T("CAN_1"), _T("Rate"), _T("100000"), m_strCan1Baud.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strCan1Baud.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER0"), _T("AesKey"), _T("41414141414141414141414141414141"), str.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strRemoteKey = theApp.HexToString(W2A(str));
	str.ReleaseBuffer();
	str.Empty();
	::GetPrivateProfileString(_T("SERVER0"), _T("Encrypt"), _T("true"), str.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_iRemoteEncrypt = str == "true" ? 0 : 1;
	::GetPrivateProfileString(_T("SERVER0"), _T("ServerIP"), _T("comm.teld.cn"), m_strRemoteIp.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strRemoteIp.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER0"), _T("ServerPort"), _T("8867"), m_strRemotePort.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strRemotePort.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER0"), _T("StationNo"), _T(""), m_strRemoteStation.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strRemoteStation.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER1"), _T("AesKey"), _T("41414141414141414141414141414141"), str.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strLocalKey= theApp.HexToString(W2A(str));
	str.ReleaseBuffer();
	str.Empty();
	::GetPrivateProfileString(_T("SERVER1"), _T("Encrypt"), _T("true"), str.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_iLocalEncrypt = str == "true" ? 0 : 1;
	::GetPrivateProfileString(_T("SERVER1"), _T("ServerIP"), _T("comm.teld.cn"), m_strLocalIp.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strLocalIp.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER1"), _T("ServerPort"), _T("8867"), m_strLocalPort.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strLocalPort.ReleaseBuffer();
	::GetPrivateProfileString(_T("SERVER1"), _T("StationNo"), _T(""), m_strLocalStation.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strLocalStation.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("Url"), _T("https://ctrl.teld.cn"), m_strWebUrl.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strWebUrl.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("Port"), _T("443"), m_strWebPort.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strWebPort.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("DataSecret"), _T("h9ZJ8nevVWdNVcfD"), m_strDataSecret.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strDataSecret.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("AesKey"), _T("0iyYbIL6h33WIafh"), m_strWebAesKey.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strWebAesKey.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("AesIV"), _T("TqwJM4NhCGzmCeda"), m_strWebAesIV.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strWebAesIV.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("OperatorID"), _T("teldrml5alnrv6zuyk7k"), m_strOperatorId.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strOperatorId.ReleaseBuffer();
	::GetPrivateProfileString(_T("WEBSERVER"), _T("OperatorSecret"), _T("eSD2fHUcwPzn1MY2"), m_strOperatorSecret.GetBuffer(MAX_PATH), MAX_PATH, strFile); 
	m_strOperatorSecret.ReleaseBuffer();

	UpdateData(FALSE);  //将成员变量的值赋给控件
	return TRUE;
}

BOOL CFirstSettingDlg::WriteConfig(void)
{
	USES_CONVERSION; 

	CString str, strFile = _T(".\\config.ini");

	UpdateData(TRUE); //将控件的值赋给成员变量

	if(m_strDirect.IsEmpty())
		m_strDirect = _T("0");
	::WritePrivateProfileString(_T("CSCUSys"), _T("DirectCurrent"), m_strDirect, strFile);
	m_strDirect.ReleaseBuffer();
	if(m_strSingle.IsEmpty())
		m_strSingle = _T("0");
	::WritePrivateProfileString(_T("CSCUSys"), _T("SinglePhase"), m_strSingle, strFile);
	m_strSingle.ReleaseBuffer();
	if(m_strThree.IsEmpty())
		m_strThree = _T("0");
	::WritePrivateProfileString(_T("CSCUSys"), _T("ThreePhase"), m_strThree, strFile);
	m_strThree.ReleaseBuffer();
	str.Format(_T("%d"), m_iPassword);
	::WritePrivateProfileString(_T("CSCUSys"), _T("Password"), str, strFile);
	str.Format(_T("%d"), m_iTEUIType + 1);
	::WritePrivateProfileString(_T("CSCUSys"), _T("NormalCard"), str, strFile);
	str.Format(_T("%d"), m_iBoard + 1);
	::WritePrivateProfileString(_T("CSCUSys"), _T("BoardType"), str, strFile);
	str.Format(_T("%d"), !m_iAbnormal);
	::WritePrivateProfileString(_T("CHARGE"), _T("EnergyFilter"), str, strFile);
	str.Format(_T("%d"), m_iCardType + 1);
  	::WritePrivateProfileString(_T("CHARGE"), _T("CardType"), str, strFile);  
	str.Format(_T("%d"), !m_iShowButton);
	::WritePrivateProfileString(_T("CHARGE"), _T("LocalStop"), str, strFile);  	
	str.Format(_T("%d"), m_iVinType + 1);
	::WritePrivateProfileString(_T("CHARGE"), _T("VinType"), str, strFile);  
	str.Format(_T("%d"), !m_iCardAuto);
	::WritePrivateProfileString(_T("CHARGE"), _T("CardAuto"), str, strFile); 
	str.Format(_T("%d"), !m_iVinAuto);
	::WritePrivateProfileString(_T("CHARGE"), _T("VinAuto"), str, strFile); 
	str.Format(_T("%d"), !m_iTicketOpen);
	::WritePrivateProfileString(_T("CHARGE"), _T("TicketEnable"), str, strFile); 
	str.Format(_T("%d"), !m_iCardMultiChoose);
	::WritePrivateProfileString(_T("CHARGE"), _T("SwitpingCardMultChooseMode"), str, strFile); 
	str.Format(_T("%d"), !m_iSinglePileGroup);
	::WritePrivateProfileString(_T("CHARGE"), _T("DevType"), str, strFile); 

	::WritePrivateProfileString(_T("NET_0"), _T("IP"), m_strNet1Ip, strFile); 
	::WritePrivateProfileString(_T("NET_0"), _T("NetMask"), m_strNet1Mask, strFile); 
	::WritePrivateProfileString(_T("NET_0"), _T("Gateway"), m_strNet1Gateway, strFile); 
	::WritePrivateProfileString(_T("NET_1"), _T("IP"), m_strNet2Ip, strFile); 
	::WritePrivateProfileString(_T("NET_1"), _T("NetMask"), m_strNet2Mask, strFile); 
	::WritePrivateProfileString(_T("NET_1"), _T("Gateway"), m_strNet2Gateway, strFile); 
	::WritePrivateProfileString(_T("CSCUSys"), _T("DNS"), m_strDNS, strFile); 
	::WritePrivateProfileString(_T("CAN_0"), _T("CanAddr"), m_strCan0Addr, strFile); 
	::WritePrivateProfileString(_T("CAN_0"), _T("Rate"), m_strCan0Baud, strFile); 
	::WritePrivateProfileString(_T("CAN_1"), _T("CanAddr"), m_strCan1Addr, strFile); 
	::WritePrivateProfileString(_T("CAN_1"), _T("Rate"), m_strCan1Baud, strFile); 
	::WritePrivateProfileString(_T("SERVER0"), _T("AesKey"), theApp.StringToHex(W2A(m_strRemoteKey)), strFile); 
	str = m_iRemoteEncrypt ? "false" : "true";
	::WritePrivateProfileString(_T("SERVER0"), _T("Encrypt"), str, strFile); 
	::WritePrivateProfileString(_T("SERVER0"), _T("ServerIP"), m_strRemoteIp, strFile); 
	::WritePrivateProfileString(_T("SERVER0"), _T("ServerPort"), m_strRemotePort, strFile); 
	::WritePrivateProfileString(_T("SERVER0"), _T("StationNo"), m_strRemoteStation, strFile); 
	::WritePrivateProfileString(_T("SERVER1"), _T("AesKey"), theApp.StringToHex(W2A(m_strLocalKey)), strFile); 
	str = m_iLocalEncrypt ? "false" : "true";
	::WritePrivateProfileString(_T("SERVER1"), _T("Encrypt"), str, strFile); 
	::WritePrivateProfileString(_T("SERVER1"), _T("ServerIP"), m_strLocalIp, strFile); 
	::WritePrivateProfileString(_T("SERVER1"), _T("ServerPort"), m_strLocalPort, strFile); 
	::WritePrivateProfileString(_T("SERVER1"), _T("StationNo"), m_strLocalStation, strFile); 

	::WritePrivateProfileString(_T("WEBSERVER"), _T("Url"), m_strWebUrl, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("Port"), m_strWebPort, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("DataSecret"), m_strDataSecret, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("AesKey"), m_strWebAesKey, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("AesIV"), m_strWebAesIV, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("OperatorID"), m_strOperatorId, strFile); 
	::WritePrivateProfileString(_T("WEBSERVER"), _T("OperatorSecret"), m_strOperatorSecret, strFile); 

	return TRUE;
}

void CFirstSettingDlg::OnCbnSelchangeComboWeburl()
{
	int iIndex;
	UpdateData(TRUE);

	iIndex = ((CComboBox*)GetDlgItem(IDC_COMBO_WebUrl))->GetCurSel();

	((CComboBox*)GetDlgItem(IDC_COMBO_WebUrl))->GetLBText(iIndex, m_strWebUrl);

	switch(iIndex)
	{
		case 0:
		{
			m_strWebPort = _T("8001");
			break;
		}
		case 1:
		{
			m_strWebPort = _T("443");
			break;
		}
		default:
			return;
	}
	UpdateData(FALSE);
}