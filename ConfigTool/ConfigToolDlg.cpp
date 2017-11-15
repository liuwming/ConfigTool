
// ConfigToolDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "ConfigToolDlg.h"
#include "afxdialogex.h"

//#pragma comment(lib, "version.lib")

#ifdef  _DEBUG
#define new DEBUG_NEW
#endif

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
#if 0
	TCHAR   szFullPath[MAX_PATH];
	DWORD dwVerInfoSize = 0;
	DWORD dwVerHnd;
	VS_FIXEDFILEINFO   *pFileInfo;

	GetModuleFileName(NULL, szFullPath, sizeof(szFullPath)); //获取当前进程已加载模块的文件的完整路径，该模块必须由当前进程加载
	dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd); //判断容纳文件版本信息需要一个多大的缓冲区
	if (dwVerInfoSize)
	{
		// If we were able to get the information, process it:
		HANDLE  hMem;
		LPVOID   lpvMem;
		unsigned int uInfoSize = 0;

		hMem    = GlobalAlloc(GMEM_MOVEABLE, dwVerInfoSize);
		lpvMem = GlobalLock(hMem);
		GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, lpvMem); //从支持版本标记的一个模块里获取文件版本信息

		::VerQueryValue(lpvMem, (LPTSTR)_T("\\"), (void**)&pFileInfo, &uInfoSize);//VerQueryValue这个函数用于从版本资源中获取信息。调用这个函数前，

		int ret = GetLastError();
		WORD m_nProdVersion[4];

		// Product version from the FILEVERSION of the version info resource 
		m_nProdVersion[0] = HIWORD(pFileInfo->dwProductVersionMS); 
		m_nProdVersion[1] = LOWORD(pFileInfo->dwProductVersionMS);
		m_nProdVersion[2] = HIWORD(pFileInfo->dwProductVersionLS);
		m_nProdVersion[3] = LOWORD(pFileInfo->dwProductVersionLS); 

		CString strVersion ;
		strVersion.Format(_T("The file's version : %d.%d.%d.%d"),m_nProdVersion[0],
		m_nProdVersion[1],m_nProdVersion[2],m_nProdVersion[3]);

		GlobalUnlock(hMem);
		GlobalFree(hMem);

		AfxMessageBox(strVersion);
	}
#endif
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CConfigToolDlg dialog

CConfigToolDlg::CConfigToolDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigToolDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	//m_hIcon = AfxGetApp()->LoadIcon(IDB_BITMAP_App);
}

void CConfigToolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_Main, m_tabMain);
}

BEGIN_MESSAGE_MAP(CConfigToolDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_Main, &CConfigToolDlg::OnSelchangeTabMain)
	ON_BN_CLICKED(IDC_BUTTON_Generate, &CConfigToolDlg::OnClickedButtonGenerate)
	ON_BN_CLICKED(IDC_BUTTON_Export, &CConfigToolDlg::OnClickedButtonExport)
END_MESSAGE_MAP()

// CConfigToolDlg message handlers

BOOL CConfigToolDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu *pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL    bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	WriteDefaultSetting();

	CMenu menu;
	//menu.LoadMenu(IDR_MENU_Main);
	SetMenu(&menu);
	menu.Detach();

	m_tabMain.InsertItem(0, _T("功能模块"));
	m_tabMain.InsertItem(1, _T("配置选项一"));
	m_tabMain.InsertItem(2, _T("配置选项二"));
	m_dlgModule.Create(IDD_DIALOG_Module, &m_tabMain);
	m_dlgFirstSetting.Create(IDD_DIALOG_FirstSetting, &m_tabMain);
	m_dlgSecondSetting.Create(IDD_DIALOG_SecondSetting, &m_tabMain);
	
	CRect rc, rect, rcHead;
	int   iWidth, iHeight;
	int   w, h;

	//GetDlgItem(IDC_STATIC_Head)->GetClientRect(rcHead);
	iWidth  = rcHead.Width();
	iHeight = rcHead.Height();

	m_tabMain.GetItemRect(0, rc);
	m_dlgFirstSetting.GetClientRect(rect);
	rect += CRect(-5, -5 - iHeight, 10, rc.Height() + iHeight + 10);
	m_tabMain.MoveWindow(rect);

	m_tabMain.GetClientRect(rect);
	rect += CRect(0, 0, 15, rc.Height() + 90 + iHeight);

	GetWindowRect(rc);
	rc.right	= rc.left + rect.Width();
	rc.bottom	= rc.top + rect.Height();
	MoveWindow(rc);

	m_tabMain.GetClientRect(rc);
	m_tabMain.GetItemRect(0, rect);
	w			= rc.Width();
	h			= rc.Height();
	rc.left		= rc.left + 1;
	rc.top		= rc.top + rect.Height() + 3;
	rc.right	= rc.left + w - 4;
	rc.bottom   = rc.top + h - 23;

	m_dlgModule.MoveWindow(rc);
	m_dlgFirstSetting.MoveWindow(rc);
	m_dlgSecondSetting.MoveWindow(rc);
	m_dlgModule.ShowWindow(SW_SHOW);

	m_tabMain.GetClientRect(rect);
	GetDlgItem(IDC_BUTTON_Export)->GetClientRect(rc);
	w		    = rc.Width();
	h		    = rc.Height();
	rc.top	    = rect.bottom + iHeight + 15;
	rc.bottom	= rc.top + h;
	rc.right	= rect.right-50;
	rc.left		= rc.right - w;
	GetDlgItem(IDC_BUTTON_Export)->MoveWindow(rc);

	GetDlgItem(IDC_BUTTON_Generate)->GetClientRect(rect);
	w			= rect.Width();
	h			= rect.Height();
	rect.top	= rc.top;
	rect.bottom = rc.top + h;
	rect.right	= rc.left - 10;
	rect.left	= rect.right - w;
	GetDlgItem(IDC_BUTTON_Generate)->MoveWindow(rect);

	//GetDlgItem(IDC_BUTTON_Generate)->GetClientRect(rect);
	//w = rect.Width();
	//h = rect.Height();
	//rect.top = rc.top;
	//rect.bottom = rc.top + h;
	//rect.right = rc.left - 10-1000;
	//rect.left = rect.right - w+1000;
	//GetDlgItem(IDC_BUTTON_Generate)->MoveWindow(rect);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfigToolDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CConfigToolDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width()  - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		m_tabMain.RedrawWindow();
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CConfigToolDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

BOOL CConfigToolDlg::ExecCommand(CString strCmdLine)
{
	PROCESS_INFORMATION processInformation = {0};
	STARTUPINFO         startupInfo = {0};
	startupInfo.cb    = sizeof(startupInfo);
	int nStrBuffer    = strCmdLine.GetLength() + 50;
	BOOL bRet;
	DWORD dwCode      = 0;

	bRet = CreateProcess(NULL, strCmdLine.GetBuffer(nStrBuffer), 
		NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW, 
		NULL, NULL, &startupInfo, &processInformation);

	if(!bRet)
	{
		AfxMessageBox(_T("Createprocess failed!"));
		return FALSE;
	}
	
	WaitForSingleObject(processInformation.hProcess, INFINITE);

	bRet = GetExitCodeProcess(processInformation.hProcess, &dwCode);
	if(!bRet)
	{
		AfxMessageBox(_T("Get exitcode failed!"));
		CloseHandle( processInformation.hProcess );
		CloseHandle( processInformation.hThread );
		return FALSE;
	}
	CloseHandle( processInformation.hProcess );
	CloseHandle( processInformation.hThread );

	if(dwCode != 0)
	{
		AfxMessageBox(_T("Invalid file execute failed!"));
		return FALSE;
	}
	return TRUE;
}

void CConfigToolDlg::OnMenuAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

BOOL CConfigToolDlg::DeleteTempDirectory(CString strPath)
{
	CFileFind  finder;  
	CString    path;  
	BOOL       bFind = FALSE;

	if(strPath.IsEmpty())
		return FALSE;

	path.Format(_T("%s/*.*"), strPath);  
	bFind = finder.FindFile(path);  
	while(bFind)
	{  
		bFind = finder.FindNextFile();  
		if(finder.IsDirectory() && !finder.IsDots())
		{
			DeleteTempDirectory(finder.GetFilePath());
			RemoveDirectory(finder.GetFilePath());  
		}  
		else
		{
			DeleteFile(finder.GetFilePath());  
		}  
	} 
	RemoveDirectory(strPath);
	return TRUE;
}

int CConfigToolDlg::WriteDefaultSetting(void)
{
	CString   strFile = _T(".\\config.ini");
	CFileFind find;
	if(!find.FindFile(strFile))
	{
		::WritePrivateProfileString(_T("CSCUSys"), _T("DirectCurrent"), _T("0"), strFile);
		::WritePrivateProfileString(_T("CSCUSys"), _T("SinglePhase"), _T("0"), strFile);
		::WritePrivateProfileString(_T("CSCUSys"), _T("ThreePhase"), _T("0"), strFile);
		::WritePrivateProfileString(_T("CSCUSys"), _T("Password"), _T("300001"), strFile);
		::WritePrivateProfileString(_T("CSCUSys"), _T("NormalCard"), _T("1"), strFile);
		::WritePrivateProfileString(_T("CSCUSys"), _T("BoardType"), _T("2"), strFile);
		::WritePrivateProfileString(_T("CHARGE"), _T("EnergyFilter"), _T("0"), strFile);
		::WritePrivateProfileString(_T("CHARGE"), _T("CardType"), _T("2"), strFile);  
		::WritePrivateProfileString(_T("CHARGE"), _T("MeterType"), _T("0"), strFile);  
		::WritePrivateProfileString(_T("CHARGE"), _T("LocalStop"), _T("1"), strFile);  	
		::WritePrivateProfileString(_T("CHARGE"), _T("VinType"), _T("3"), strFile);  
		::WritePrivateProfileString(_T("CHARGE"), _T("CardAuto"), _T("0"), strFile); 
		::WritePrivateProfileString(_T("CHARGE"), _T("VinAuto"), _T("0"), strFile); 
		::WritePrivateProfileString(_T("CHARGE"), _T("TicketEnable"), _T("0"), strFile); 
		::WritePrivateProfileString(_T("CHARGE"), _T("SwitpingCardMultChooseMode"), _T("0"), strFile); 
		::WritePrivateProfileString(_T("CHARGE"), _T("DevType"), _T("0"), strFile); 

		::WritePrivateProfileString(_T("NET_0"), _T("IP"), _T(""), strFile); 
		::WritePrivateProfileString(_T("NET_0"), _T("NetMask"), _T(""), strFile); 
		::WritePrivateProfileString(_T("NET_0"), _T("Gateway"), _T(""), strFile); 
		::WritePrivateProfileString(_T("NET_1"), _T("IP"), _T(""), strFile); 
		::WritePrivateProfileString(_T("NET_1"), _T("NetMask"), _T(""), strFile); 
		::WritePrivateProfileString(_T("NET_1"), _T("Gateway"), _T(""), strFile); 
		::WritePrivateProfileString(_T("CSCUSys"), _T("DNS"), _T(""), strFile); 
		::WritePrivateProfileString(_T("CAN_0"), _T("CanAddr"), _T("250"), strFile); 
		::WritePrivateProfileString(_T("CAN_0"), _T("Rate"), _T("100000"), strFile); 
		::WritePrivateProfileString(_T("CAN_1"), _T("CanAddr"), _T("250"), strFile); 
		::WritePrivateProfileString(_T("CAN_1"), _T("Rate"), _T("100000"), strFile); 
		::WritePrivateProfileString(_T("SERVER0"), _T("AesKey"), _T("41414141414141414141414141414141"), strFile); 
		::WritePrivateProfileString(_T("SERVER0"), _T("Encrypt"), _T("true"), strFile); 
		::WritePrivateProfileString(_T("SERVER0"), _T("ServerIP"), _T("comm.teld.cn"), strFile); 
		::WritePrivateProfileString(_T("SERVER0"), _T("ServerPort"), _T("8867"), strFile); 
		::WritePrivateProfileString(_T("SERVER0"), _T("StationNo"), _T(""), strFile); 
		::WritePrivateProfileString(_T("SERVER1"), _T("AesKey"), _T("41414141414141414141414141414141"), strFile); 
		::WritePrivateProfileString(_T("SERVER1"), _T("Encrypt"), _T("true"), strFile); 
		::WritePrivateProfileString(_T("SERVER1"), _T("ServerIP"), _T("comm.teld.cn"), strFile); 
		::WritePrivateProfileString(_T("SERVER1"), _T("ServerPort"), _T("8867"), strFile); 
		::WritePrivateProfileString(_T("SERVER1"), _T("StationNo"), _T(""), strFile); 
		
		/*WebApi*/
		::WritePrivateProfileString(_T("WEBSERVER"), _T("Url"), _T("http://api.teld.cn"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("Port"), _T("8001"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("DataSecret"), _T("h9ZJ8nevVWdNVcfD"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("AesKey"), _T("0iyYbIL6h33WIafh"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("AesIV"), _T("TqwJM4NhCGzmCeda"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("OperatorID"), _T("teldrml5alnrv6zuyk7k"), strFile); 
		::WritePrivateProfileString(_T("WEBSERVER"), _T("OperatorSecret"), _T("eSD2fHUcwPzn1MY2"), strFile); 
		
		/*负荷约束*/
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("PowerLimit_Enable"), _T("false"), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("CCUCount"), _T(""), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("StationLimitPower"), _T(""), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SafeLimitPower"), _T(""), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual"), _T(""), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Ammeter_Enable"), _T("false"), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Server_Enable"), _T("false"), strFile);
		::WritePrivateProfileString(_T("POWER_LIMIT"), _T("SumPower_Manual_Enable"), _T("false"), strFile);
		
		/*错峰充电*/
		::WritePrivateProfileString(_T("SMART_CHARGE"), _T("SmartCharge_Enable"), _T("false"), strFile); 
		::WritePrivateProfileString(_T("SMART_CAR"), _T("SmartCar_Enable"), _T("false"), strFile); 
		
		/*子站环境参数*/
		::WritePrivateProfileString(_T("IOIN"), _T("DIN1"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN2"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN3"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN4"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN5"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN6"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN7"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN8"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN9"), _T("0"), strFile);
		::WritePrivateProfileString(_T("IOIN"), _T("DIN10"), _T("0"), strFile);

		/*充电模式*/
		::WritePrivateProfileString(_T("SINGLEPILESys"), _T("MasterMode"), _T("1"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("SINGLEPILESys"), _T("SlaveMode"), _T("0"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("SINGLEPILESys"), _T("PwdCharge"), _T("100003"), SETTING_CONFIG);

		/*灯条参数*/
		::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightcontrol_enable"), _T("false"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightopentime_hour"), _T("18"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightopentime_minute"), _T("0"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightclosetime_hour"), _T("6"), SETTING_CONFIG);
		::WritePrivateProfileString(_T("LIGHTSETTING"), _T("lightclosetime_minute"), _T("0"), SETTING_CONFIG);

		/*开门断电*/
		::WritePrivateProfileString(_T("MAGNETICSWITCH"), _T("bOpenDoorPowerOutages"), _T("false"), SETTING_CONFIG); 
	}
	return 0;
}

int CConfigToolDlg::WriteDefaultModule(void)
{
	CString   strFile = _T(".\\libconfig.ini");
	CFileFind find;

	if(!find.FindFile(strFile))
	{
		::WritePrivateProfileString(_T("CHARGESERVICE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("CHARGESERVICE"), _T("library"), _T("libChargeService.so"), strFile);
		::WritePrivateProfileString(_T("CHARGESERVICE"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SCHEDULE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("SCHEDULE"), _T("library"), _T("libLoadSchedule.so"), strFile);
		::WritePrivateProfileString(_T("SCHEDULE"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SERVER0"), _T("type"), _T("remote"), strFile);
		::WritePrivateProfileString(_T("SERVER0"), _T("library"), _T("libIEC104Server.so"), strFile);
		::WritePrivateProfileString(_T("SERVER0"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SERVER1"), _T("type"), _T("local"), strFile);
		::WritePrivateProfileString(_T("SERVER1"), _T("library"), _T("libIEC104Server.so"), strFile);
		::WritePrivateProfileString(_T("SERVER1"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("library"), _T("libChargeEquipment.so"), strFile);
		::WritePrivateProfileString(_T("CHARGEEQUIPMENT"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("AMMETER"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("AMMETER"), _T("library"), _T("libAmmeter.so"), strFile);
		::WritePrivateProfileString(_T("AMMETER"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("TEMPHUMI"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("TEMPHUMI"), _T("library"), _T("libTempHumi.so"), strFile);
		::WritePrivateProfileString(_T("TEMPHUMI"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("CARD"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("CARD"), _T("library"), _T("libCard.so"), strFile);
		::WritePrivateProfileString(_T("CARD"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SCREEN"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("SCREEN"), _T("library"), _T("libSerialScreen.so"), strFile);
		::WritePrivateProfileString(_T("SCREEN"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("library"), _T("libSerialScreenSinglePile.so"), strFile);
		::WritePrivateProfileString(_T("SCREENSINGLEPILE"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("GPIO"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("GPIO"), _T("library"), _T("libGPIO.so"), strFile);
		::WritePrivateProfileString(_T("GPIO"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("UPDATE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("UPDATE"), _T("library"), _T("libUpdate.so"), strFile);
		::WritePrivateProfileString(_T("UPDATE"), _T("enable"), _T("true"), strFile);

		::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("library"), _T("libDeviceManage.so"), strFile);
		::WritePrivateProfileString(_T("DEVICEMANAGE"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("WEBSERVER"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("WEBSERVER"), _T("library"), _T("libWebServer.so"), strFile);
		::WritePrivateProfileString(_T("WEBSERVER"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("TICKET"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("TICKET"), _T("library"), _T("libTicketDev.so"), strFile);
		::WritePrivateProfileString(_T("TICKET"), _T("enable"), _T("false"), strFile);

		::WritePrivateProfileString(_T("SCANCODE"), _T("type"), _T("device"), strFile);
		::WritePrivateProfileString(_T("SCANCODE"), _T("library"), _T("libScanCode.so"), strFile);
		::WritePrivateProfileString(_T("SCANCODE"), _T("enable"), _T("false"), strFile);
	}
	return 0;
}

void CConfigToolDlg::OnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
		int iSel = m_tabMain.GetCurSel();
		switch(iSel)
		{
			case 0:
			{
				m_dlgModule.ShowWindow(SW_SHOW);
				m_dlgFirstSetting.ShowWindow(SW_HIDE);
				m_dlgSecondSetting.ShowWindow(SW_HIDE);
				break;
			}
			case 1:
			{
				m_dlgModule.ShowWindow(SW_HIDE);
				m_dlgFirstSetting.ShowWindow(SW_SHOW);
				m_dlgSecondSetting.ShowWindow(SW_HIDE);
				break;
			}
			case 2:
			{
				m_dlgModule.ShowWindow(SW_HIDE);
				m_dlgFirstSetting.ShowWindow(SW_HIDE);
				m_dlgSecondSetting.ShowWindow(SW_SHOW);
				break;
			}
			default:
				break;
		}
		*pResult = 0;
}

void CConfigToolDlg::OnClickedButtonGenerate()
{
	// TODO: 在此添加控件通知处理程序代码
	if (!m_dlgModule.WriteConfig() ||
		!m_dlgFirstSetting.WriteConfig() ||
		 !m_dlgSecondSetting.WriteConfig())
	{
		return;
	}
	AfxMessageBox(_T("配置文件生成成功!"));
}

void CConfigToolDlg::OnClickedButtonExport()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile, strPath, strTar, strConfig, strLibConfig;
	CString strCmd,  strDll,  strCmdLine;
	CString strDirMnt, strDirNandflash, strDirDatabase;
	TCHAR   szPath[MAX_PATH];
	memset(szPath, 0, MAX_PATH);
	::GetCurrentDirectory(MAX_PATH, szPath);

	strConfig.Format(_T("%s\\config.ini"), szPath);
	strLibConfig.Format(_T("%s\\libconfig.ini"), szPath);
	strCmd.Format(_T("%s\\7z.exe"), szPath);
	strDll.Format(_T("%s\\7z.dll"), szPath);

	CFileFind finder;
	if (!finder.FindFile(strCmd) || !finder.FindFile(strDll)) //finder.FindFile();找到,返回1。
	{
		AfxMessageBox(_T("7z运行环境不存在，请确认已正确安装!"));
		return;
	}
	if (!finder.FindFile( ) || !finder.FindFile(strLibConfig))
	{
		AfxMessageBox(_T("配置文件不存在，请生成配置文件!"));
		return;
	}
	DeleteTempDirectory(_T("mnt"));

	CFileDialog dlg(TRUE, _T("Tar File(*.tar.gz)|*.tar.gz"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("Tar File(*.tar.gz)|*.tar.gz||"), this);
	dlg.m_ofn.lpstrInitialDir = szPath;
	if (dlg.DoModal() == IDOK)
	{
		strFile = dlg.GetPathName();
		strTar  = strFile.Left(strFile.ReverseFind('.'));
		strPath = strFile.Left(strFile.ReverseFind('\\'));
		strTar.Format(_T("%s\\setup.tar"), strPath);
		strDirMnt.Format(_T("%s\\mnt"), szPath);

		CreateDirectory(strDirMnt, NULL);
		strDirNandflash.Format(_T("%s\\nandflash"), strDirMnt);
		CreateDirectory(strDirNandflash, NULL);
		strDirDatabase.Format(_T("%s\\database"), strDirNandflash);
		CreateDirectory(strDirDatabase, NULL);

		CopyFile(_T("config.ini"), _T("mnt\\nandflash\\config.ini"), FALSE);
		CopyFile(_T("libconfig.ini"), _T("mnt\\nandflash\\libconfig.ini"), FALSE);
		CopyFile(_T("param_config.db"), _T("mnt\\nandflash\\database\\param_config.db"), FALSE);

		strCmdLine.Format(_T("\"%s\" e -y -sdel \"%s\" -o\"%s\""), strCmd, strFile, strPath);
		if (!ExecCommand(strCmdLine))
			return;
		strCmdLine.Format(_T("\"%s\" u -y -r \"%s\" \"%s\""), strCmd, strTar, strDirMnt);
		if (!ExecCommand(strCmdLine))
			return;
		strCmdLine.Format(_T("\"%s\" a -y -tgzip -sdel \"%s\" \"%s\""), strCmd, strFile, strTar);
		if (!ExecCommand(strCmdLine))
			return;
		DeleteTempDirectory(_T("mnt"));
		AfxMessageBox(_T("配置文件导出成功!"));
	}
}
