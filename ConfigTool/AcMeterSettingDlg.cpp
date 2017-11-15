// AcMeterSettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "AcMeterSettingDlg.h"
#include "afxdialogex.h"
#include "sqlite3.h"

// CAcMeterSettingDlg dialog

IMPLEMENT_DYNAMIC(CAcMeterSettingDlg, CDialogEx)

CAcMeterSettingDlg::CAcMeterSettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAcMeterSettingDlg::IDD, pParent)
	, m_iCanAddr(0)
	, m_strScale(_T("99.99"))
	, m_bAcMeterEnable(FALSE)
{
	m_bModify = FALSE;
}

CAcMeterSettingDlg::~CAcMeterSettingDlg()
{
}

void CAcMeterSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_CBIndex(pDX, IDC_COMBO_CanAddr, m_iCanAddr);
	DDX_Text(pDX, IDC_EDIT_AcScale, m_strScale);
	DDX_Check(pDX, IDC_CHECK_AcMeter, m_bAcMeterEnable);
	DDX_Control(pDX, IDC_LIST_AcMeter, m_listAcMeter);
}

BEGIN_MESSAGE_MAP(CAcMeterSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_CHECK_AcMeter, &CAcMeterSettingDlg::OnBnClickedCheckAcmeter)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CAcMeterSettingDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CAcMeterSettingDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CAcMeterSettingDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_CLICK, IDC_LIST_AcMeter, &CAcMeterSettingDlg::OnClickListAcmeter)
	ON_BN_CLICKED(IDCANCEL, &CAcMeterSettingDlg::OnBnClickedCancel)
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CAcMeterSettingDlg message handlers

BOOL CAcMeterSettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString str;
	for (int i = 181; i <= 230; i++) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_CanAddr))->AddString(str);
	}

	CRect rect;
	m_listAcMeter.GetClientRect(rect);
	m_listAcMeter.SetExtendedStyle(m_listAcMeter.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listAcMeter.InsertColumn(0, _T("CAN地址"), 0, (rect.Width() - 50) / 2);
	m_listAcMeter.InsertColumn(1, _T("损耗比"), 0, (rect.Width() - 50) / 2);

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

#if 1
BOOL CAcMeterSettingDlg::ReadConfig(void)
{
	USES_CONVERSION;

	CString strFile = _T("./config.ini");
	m_bAcMeterEnable = ::GetPrivateProfileInt(_T("CHARGE"), _T("MeterType"), 0, strFile);

	CString  strSql;
	char     * err, **result;
	int      row = 0, col = 0;
	sqlite3  * db = NULL;
	sqlite3_open("param_config.db", &db);
	if (!db)
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}

	strSql = _T("CREATE TABLE IF NOT EXISTS acmeter_scale_table(id integer primary key autoincrement, can_addr integer, ac_scale text);");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK)
	{
		AfxMessageBox(_T("Create table acmeter_scale_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	strSql = _T("SELECT can_addr, ac_scale FROM acmeter_scale_table ORDER BY can_addr ASC;");
	if (sqlite3_get_table(db, (LPCSTR)W2A(strSql), &result, &row, &col, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Query table acmeter_scale_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	CString str;
	ACMETER_SCALE *info;
	for (int i = 0; i < row; i++)
	{
		info = new ACMETER_SCALE;
		info->iCanAddr = atoi(result[col++]);
		info->strScale = result[col++];
		m_mapAcMeter.SetAt(info->iCanAddr, info);

		str.Format(_T("%d"), info->iCanAddr);
		m_listAcMeter.InsertItem(i, str);
		m_listAcMeter.SetItemText(i, 1, info->strScale);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);

	UpdateData(FALSE);
	OnBnClickedCheckAcmeter();

	return TRUE;
}

BOOL CAcMeterSettingDlg::WriteConfig(void)
{
	USES_CONVERSION;

	CString str, strFile = _T("./config.ini");

	UpdateData(TRUE);
	str.Format(_T("%d"), m_bAcMeterEnable);
	::WritePrivateProfileString(_T("CHARGE"), _T("MeterType"), str, strFile);

	CString  strSql;
	sqlite3  *db = NULL;
	char     *err;
	int      row = 0, col = 0;

	sqlite3_open("param_config.db", &db);
	if (!db)
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}
	strSql = _T("DELETE FROM acmeter_scale_table;");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Delete table acmeter_scale_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}
	ACMETER_SCALE  *info;
	int            iCanAddr;
	POSITION       pos = m_mapAcMeter.GetStartPosition();
	while (pos) 
	{
		m_mapAcMeter.GetNextAssoc(pos, iCanAddr, info);
		strSql.Format(_T("INSERT INTO acmeter_scale_table (can_addr, ac_scale) VALUES(%d, '%s');"),
			                       info->iCanAddr, info->strScale);
		if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
		{
			AfxMessageBox(_T("Insert table acmeter_scale_table failed!"));
			sqlite3_free(err);
			sqlite3_close(db);
			return FALSE;
		}
	}
	sqlite3_close(db);
	return TRUE;
}
#endif
void CAcMeterSettingDlg::OnBnClickedCheckAcmeter()
{
	UpdateData(TRUE);

	GetDlgItem(IDC_COMBO_CanAddr)->EnableWindow(m_bAcMeterEnable);
	GetDlgItem(IDC_EDIT_AcScale)->EnableWindow(m_bAcMeterEnable);
	GetDlgItem(IDC_BUTTON_Add)->EnableWindow(m_bAcMeterEnable);
	GetDlgItem(IDC_BUTTON_Delete)->EnableWindow(m_bAcMeterEnable);
	GetDlgItem(IDC_LIST_AcMeter)->EnableWindow(m_bAcMeterEnable);
}

void CAcMeterSettingDlg::OnBnClickedButtonSave()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CAcMeterSettingDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CAcMeterSettingDlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	ACMETER_SCALE *info = NULL;
	int iIndex = -1, iCanAddr = -1;
	CString str;
	double dScale = 0.0;

	if (m_strScale.IsEmpty())
	{
		AfxMessageBox(_T("损耗比不能为空！"));
		return;
	}

	if (!m_bModify)
	{
		m_mapAcMeter.Lookup(m_iCanAddr + 181, info);
		if (info)
		{
			str.Format(_T("CAN地址 %d 已经配置!"), info->iCanAddr);
			AfxMessageBox(str);
			return;
		}
		info = new ACMETER_SCALE;
		info->iCanAddr = m_iCanAddr + 181;
		info->strScale = m_strScale;
		m_mapAcMeter.SetAt(info->iCanAddr, info);
		iIndex = 0;
		str.Format(_T("%d"), info->iCanAddr);
		m_listAcMeter.InsertItem(iIndex, str);
	}
	else 
	{
		iIndex = m_listAcMeter.GetNextItem(-1, LVIS_SELECTED);
		if (iIndex < 0)
		{
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		str = m_listAcMeter.GetItemText(iIndex, 0);
		iCanAddr = _ttoi(str);
		m_mapAcMeter.Lookup(iCanAddr, info);
		if (info) 
		{
			info->strScale = m_strScale;
			m_mapAcMeter.SetAt(iCanAddr, info);
		}
	}
	if (info)
	{
		m_listAcMeter.SetItemText(iIndex, 1, info->strScale);
	}
}


void CAcMeterSettingDlg::OnBnClickedButtonDelete()
{
	int iIndex = -1;
	iIndex = m_listAcMeter.GetNextItem(-1, LVIS_SELECTED);
	if (iIndex < 0) 
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	ACMETER_SCALE *info = NULL;
	CString str;
	int iCanAddr;
	str = m_listAcMeter.GetItemText(iIndex, 0);
	iCanAddr = _ttoi(str);
	m_mapAcMeter.Lookup(iCanAddr, info);
	if (info) 
	{
		delete info;
		info = NULL;
	}
	m_mapAcMeter.RemoveKey(iCanAddr);
	m_listAcMeter.DeleteItem(iIndex);
}


void CAcMeterSettingDlg::OnClickListAcmeter(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	ACMETER_SCALE *info;
	int iCanAddr, iIndex;
	CString str;

	iIndex = m_listAcMeter.GetNextItem(-1, LVIS_SELECTED);

	m_bModify = FALSE;
	m_iCanAddr = 0;

	if (iIndex >= 0) 
	{
		m_bModify = TRUE;
		str = m_listAcMeter.GetItemText(iIndex, 0);
		iCanAddr = _ttoi(str);
		m_mapAcMeter.Lookup(iCanAddr, info);
		if (info) 
		{
			m_iCanAddr = info->iCanAddr - 181;
			m_strScale = info->strScale;
		}
	}

	GetDlgItem(IDC_COMBO_CanAddr)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	UpdateData(FALSE);
	*pResult = 0;
}

void CAcMeterSettingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	ACMETER_SCALE *info = NULL;
	int iCanAddr;
	POSITION pos = m_mapAcMeter.GetStartPosition();
	while (pos)
	{
		m_mapAcMeter.GetNextAssoc(pos, iCanAddr, info);
		if (info) 
		{
			delete info;
			info = NULL;
		}
	}
	m_mapAcMeter.RemoveAll();
}
