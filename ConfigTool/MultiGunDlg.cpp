// MultiGunDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "MultiGunDlg.h"
#include "afxdialogex.h"
#include "sqlite3.h"

// CMultiGunDlg dialog

IMPLEMENT_DYNAMIC(CMultiGunDlg, CDialogEx)

CMultiGunDlg::CMultiGunDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMultiGunDlg::IDD, pParent)
	, m_iCanAddr(0)
	, m_iGunNum(0)
	, m_bSingleGunOpen(FALSE)
{
	m_bModify = FALSE;
}

CMultiGunDlg::~CMultiGunDlg()
{
}

void CMultiGunDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_CanAddr, m_iCanAddr);
	DDX_CBIndex(pDX, IDC_COMBO_GunNum, m_iGunNum);
	DDX_Check(pDX, IDC_CHECK_SingleGunOpen, m_bSingleGunOpen);
	DDX_Control(pDX, IDC_LIST_MultiGun, m_listMultiGun);
}

BEGIN_MESSAGE_MAP(CMultiGunDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CMultiGunDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CMultiGunDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CMultiGunDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDCANCEL, &CMultiGunDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_MultiGun, &CMultiGunDlg::OnClickListMultigun)
END_MESSAGE_MAP()

// CMultiGunDlg message handlers

BOOL CMultiGunDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 1; i <= 255; i++) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_CanAddr))->AddString(str);
	}

	CRect rect;
	m_listMultiGun.GetClientRect(rect);
	m_listMultiGun.SetExtendedStyle(m_listMultiGun.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listMultiGun.InsertColumn(0, _T("CAN地址"), 0, (rect.Width() - 60) / 3);
	m_listMultiGun.InsertColumn(1, _T("枪数量"), 0, (rect.Width() - 60) / 3);
	m_listMultiGun.InsertColumn(2, _T("自动检测枪数"), 0, (rect.Width() - 60) / 3);

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CMultiGunDlg::ReadConfig()
{
	CStringA strSql;
	sqlite3* db = NULL;
	char* err, **result;
	int row = 0, col = 0;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}
	strSql = _T("create table if not exists terminal_autocharge_set_table (id integer primary key autoincrement, canaddr integer, autochargenum integer, isenable integer);");
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Create table terminal_autocharge_set_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	strSql = _T("SELECT canaddr, autochargenum, isenable FROM terminal_autocharge_set_table;");
	if (sqlite3_get_table(db, (LPCSTR)strSql, &result, &row, &col, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Query table phasetype_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	CString str;
	MULTI_GUN_INFO *info;
	for (int i = 0; i < row; i++) 
	{
		info = new MULTI_GUN_INFO;
		memset(info, 0, sizeof(MULTI_GUN_INFO));
		info->iCanAddr = atoi(result[col++]);
		info->iGunNum = atoi(result[col++]);
		info->iSingleEnable = atoi(result[col++]);
		m_mapMultiGun.SetAt(info->iCanAddr, info);

		str.Format(_T("%d"), info->iCanAddr);
		m_listMultiGun.InsertItem(i, str);
		str.Format(_T("%d"), info->iGunNum);
		m_listMultiGun.SetItemText(i, 1, str);
		str = info->iSingleEnable == 1 ? _T("开启") : _T("关闭");
		m_listMultiGun.SetItemText(i, 2, str);
	}
	sqlite3_free_table(result);
	sqlite3_close(db);

	UpdateData(FALSE);
	return TRUE;
}

BOOL CMultiGunDlg::WriteConfig()
{
	CStringA strSql;
	sqlite3  *db = NULL;
	char     *err;
	int      row = 0, col = 0;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}
	strSql = _T("DELETE FROM terminal_autocharge_set_table;");
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Create table terminal_autocharge_set_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}
	MULTI_GUN_INFO *info;
	int iCanAddr;
	POSITION pos = m_mapMultiGun.GetStartPosition();
	while (pos) 
	{
		m_mapMultiGun.GetNextAssoc(pos, iCanAddr, info);
		strSql.Format("INSERT INTO terminal_autocharge_set_table (canaddr, autochargenum, isenable) VALUES(%d, %d, %d);",
			info->iCanAddr, info->iGunNum, info->iSingleEnable);
		if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
		{
			AfxMessageBox(_T("Insert table terminal_autocharge_set_table failed!"));
			sqlite3_free(err);
			sqlite3_close(db);
			return FALSE;
		}
	}

	sqlite3_close(db);
	return TRUE;
}

void CMultiGunDlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	MULTI_GUN_INFO *info = NULL;
	int iIndex = -1, iCanAddr = -1;
	CString str;

	if (!m_bModify) 
	{
		m_mapMultiGun.Lookup(m_iCanAddr + 1, info);
		if (info) 
		{
			str.Format(_T("CAN地址 %d 已经配置!"), info->iCanAddr);
			AfxMessageBox(str);
			return;
		}
		info = new MULTI_GUN_INFO;
		memset(info, 0, sizeof(MULTI_GUN_INFO));
		info->iCanAddr = m_iCanAddr + 1;
		info->iGunNum = m_iGunNum + 1;
		info->iSingleEnable = m_bSingleGunOpen;
		m_mapMultiGun.SetAt(info->iCanAddr, info);
		iIndex = 0;
		str.Format(_T("%d"), info->iCanAddr);
		m_listMultiGun.InsertItem(iIndex, str);
	}
	else 
	{
		iIndex = m_listMultiGun.GetNextItem(-1, LVIS_SELECTED);
		if (iIndex < 0) 
		{
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		str = m_listMultiGun.GetItemText(iIndex, 0);
		iCanAddr = _ttoi(str);
		m_mapMultiGun.Lookup(iCanAddr, info);
		if (info) 
		{
			info->iGunNum = m_iGunNum + 1;
			info->iSingleEnable = m_bSingleGunOpen;
			m_mapMultiGun.SetAt(iCanAddr, info);
		}
	}
	if (info) 
	{
		str.Format(_T("%d"), info->iGunNum);
		m_listMultiGun.SetItemText(iIndex, 1, str);
		str = info->iSingleEnable == 1 ? _T("开启") : _T("关闭");
		m_listMultiGun.SetItemText(iIndex, 2, str);
	}
}

void CMultiGunDlg::OnBnClickedButtonDelete()
{
	int iIndex = -1;
	iIndex = m_listMultiGun.GetNextItem(-1, LVIS_SELECTED);
	if (iIndex < 0) 
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	MULTI_GUN_INFO *info = NULL;
	CString str;
	int iCanAddr;
	str = m_listMultiGun.GetItemText(iIndex, 0);
	iCanAddr = _ttoi(str);
	m_mapMultiGun.Lookup(iCanAddr, info);
	if (info) 
	{
		delete info;
		info = NULL;
	}
	m_mapMultiGun.RemoveKey(iCanAddr);
	m_listMultiGun.DeleteItem(iIndex);
}

void CMultiGunDlg::OnBnClickedOk()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CMultiGunDlg::OnBnClickedCancel()
{
	MULTI_GUN_INFO *info = NULL;
	int iCanAddr;
	POSITION pos = m_mapMultiGun.GetStartPosition();
	while (pos) 
	{
		m_mapMultiGun.GetNextAssoc(pos, iCanAddr, info);
		if (info) 
		{
			delete info;
			info = NULL;
		}
	}
	m_mapMultiGun.RemoveAll();

	CDialogEx::OnCancel();
}

void CMultiGunDlg::OnClickListMultigun(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	MULTI_GUN_INFO *info;
	int iCanAddr, iIndex;
	CString str;

	iIndex     = m_listMultiGun.GetNextItem(-1, LVIS_SELECTED);

	m_bModify  = FALSE;
	m_iCanAddr = 0;
	m_iGunNum  = 0;
	m_bSingleGunOpen = FALSE;

	if (iIndex >= 0) 
	{
		m_bModify = TRUE;
		iCanAddr  = _ttoi(str);
		str       = m_listMultiGun.GetItemText(iIndex, 0);
		m_mapMultiGun.Lookup(iCanAddr, info);
		if (info) 
		{
			m_iCanAddr = info->iCanAddr - 1;
			m_iGunNum = info->iGunNum - 1;
			m_bSingleGunOpen = info->iSingleEnable;
		}
	}

	GetDlgItem(IDC_COMBO_CanAddr)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	UpdateData(FALSE);
	*pResult = 0;
}
