// AmmeterRangeDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "AmmeterRangeDlg.h"
#include "afxdialogex.h"
#include "sqlite3.h"

// CAmmeterRangeDlg dialog

IMPLEMENT_DYNAMIC(CAmmeterRangeDlg, CDialogEx)

CAmmeterRangeDlg::CAmmeterRangeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAmmeterRangeDlg::IDD, pParent)
	, m_iCanAddr(0)
	, m_strMaxRange(_T("999999.99"))
{
	m_bModify = FALSE;
}

CAmmeterRangeDlg::~CAmmeterRangeDlg()
{
}

void CAmmeterRangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_CanAddr, m_iCanAddr);
	DDX_CBString(pDX, IDC_COMBO_AmmeterRange, m_strMaxRange);
	DDX_Control(pDX, IDC_LIST_AmmeterRange, m_listAmmeterRange);
}

BEGIN_MESSAGE_MAP(CAmmeterRangeDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CAmmeterRangeDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CAmmeterRangeDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CAmmeterRangeDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDCANCEL, &CAmmeterRangeDlg::OnBnClickedCancel)
	ON_NOTIFY(NM_CLICK, IDC_LIST_AmmeterRange, &CAmmeterRangeDlg::OnClickListAmmeterrange)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CAmmeterRangeDlg message handlers

BOOL CAmmeterRangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 1; i <= 255; i++) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_CanAddr))->AddString(str);
	}
	CRect rect;
	m_listAmmeterRange.GetClientRect(rect);
	m_listAmmeterRange.SetExtendedStyle(m_listAmmeterRange.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listAmmeterRange.InsertColumn(0, _T("CAN地址"), 0, (rect.Width() - 50) / 2);
	m_listAmmeterRange.InsertColumn(1, _T("电表量程"), 0, (rect.Width() - 50) / 2);

	ReadConfig();

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

#if 1
BOOL CAmmeterRangeDlg::ReadConfig(void)
{
	USES_CONVERSION;

	CString   strSql;
	char       * err, **result;
	int          row = 0, col = 0;

	sqlite3    * db = NULL;
	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}

	strSql = _T("CREATE TABLE IF NOT EXISTS ammeter_range_table(id integer primary key autoincrement, can_addr integer, max_range text);");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Create table ammeter_range_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	strSql = _T("SELECT * FROM ammeter_range_table ORDER BY can_addr ASC;");
	if (sqlite3_get_table(db, (LPCSTR)W2A(strSql), &result, &row, &col, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Query table ammeter_range_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	CString                    str;
	AMMETER_RANGE    *info;
	for (int i = 0; i < row; i++) 
	{
		info = new AMMETER_RANGE;
		col++;
		info->iCanAddr = atoi(result[col++]);
		info->strRange = result[col++];
		m_mapRange.SetAt(info->iCanAddr, info);

		str.Format(_T("%d"), info->iCanAddr);
		m_listAmmeterRange.InsertItem(i, str);
		m_listAmmeterRange.SetItemText(i, 1, info->strRange);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);
	return TRUE;
}

BOOL CAmmeterRangeDlg::WriteConfig(void)
{
	USES_CONVERSION;

	CString strSql;
	sqlite3* db = NULL;
	char* err;
	int row = 0, col = 0;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}
	strSql = _T("DELETE FROM ammeter_range_table;");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Delete table ammeter_range_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}
	AMMETER_RANGE *info;
	int iCanAddr;
	POSITION pos = m_mapRange.GetStartPosition();
	while (pos) 
	{
		m_mapRange.GetNextAssoc(pos, iCanAddr, info);
		strSql.Format(_T("INSERT INTO ammeter_range_table (can_addr, max_range) VALUES(%d, '%s');"),
			info->iCanAddr, info->strRange);
		if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
		{
			AfxMessageBox(_T("Insert table ammeter_range_table failed!"));
			sqlite3_free(err);
			sqlite3_close(db);
			return FALSE;
		}
	}
	sqlite3_close(db);
	return TRUE;
}
#endif

void CAmmeterRangeDlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	AMMETER_RANGE *info = NULL;
	int iIndex = -1, iCanAddr = -1;
	CString str;

	if (m_strMaxRange.IsEmpty()) 
	{
		AfxMessageBox(_T("电表量程不能为空！"));
		return;
	}

	if (!m_bModify) 
	{
		m_mapRange.Lookup(m_iCanAddr + 1, info);
		if (info) 
		{
			str.Format(_T("CAN地址 %d 已经配置!"), info->iCanAddr);
			AfxMessageBox(str);
			return;
		}
		info = new AMMETER_RANGE;
		info->iCanAddr = m_iCanAddr + 1;
		info->strRange = m_strMaxRange;
		m_mapRange.SetAt(info->iCanAddr, info);
		iIndex = 0;
		str.Format(_T("%d"), info->iCanAddr);
		m_listAmmeterRange.InsertItem(iIndex, str);
	}
	else 
	{
		iIndex = m_listAmmeterRange.GetNextItem(-1, LVIS_SELECTED);
		if (iIndex < 0)
		{
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		str = m_listAmmeterRange.GetItemText(iIndex, 0);
		iCanAddr = _ttoi(str);
		m_mapRange.Lookup(iCanAddr, info);
		if (info) 
		{
			info->strRange = m_strMaxRange;
			m_mapRange.SetAt(iCanAddr, info);
		}
	}
	if (info) 
	{
		m_listAmmeterRange.SetItemText(iIndex, 1, info->strRange);
	}
}

void CAmmeterRangeDlg::OnBnClickedButtonDelete()
{
	int iIndex = -1;
	iIndex = m_listAmmeterRange.GetNextItem(-1, LVIS_SELECTED);
	if (iIndex < 0)
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	AMMETER_RANGE *info = NULL;
	CString str;
	int iCanAddr;
	str = m_listAmmeterRange.GetItemText(iIndex, 0);
	iCanAddr = _ttoi(str);
	m_mapRange.Lookup(iCanAddr, info);
	if (info) 
	{
		delete info;
		info = NULL;
	}
	m_mapRange.RemoveKey(iCanAddr);
	m_listAmmeterRange.DeleteItem(iIndex);
}

void CAmmeterRangeDlg::OnBnClickedButtonSave()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CAmmeterRangeDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CAmmeterRangeDlg::OnClickListAmmeterrange(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	AMMETER_RANGE *info;
	int iCanAddr, iIndex;
	CString str;

	iIndex = m_listAmmeterRange.GetNextItem(-1, LVIS_SELECTED);

	m_bModify = FALSE;
	m_iCanAddr = 0;

	if (iIndex >= 0)
	{
		m_bModify = TRUE;
		str = m_listAmmeterRange.GetItemText(iIndex, 0);
		iCanAddr = _ttoi(str);
		m_mapRange.Lookup(iCanAddr, info);
		if (info) 
		{
			m_iCanAddr = info->iCanAddr - 1;
			m_strMaxRange = info->strRange;
		}
	}

	GetDlgItem(IDC_COMBO_CanAddr)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	UpdateData(FALSE);
	*pResult = 0;
}


void CAmmeterRangeDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	AMMETER_RANGE *info = NULL;
	int iCanAddr;
	POSITION pos = m_mapRange.GetStartPosition();
	while (pos) 
	{
		m_mapRange.GetNextAssoc(pos, iCanAddr, info);
		if (info) 
		{
			delete info;
			info = NULL;
		}
	}
	m_mapRange.RemoveAll();
}
