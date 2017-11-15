// RelaySettingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "RelaySettingDlg.h"
#include "afxdialogex.h"
#include "sqlite3.h"

// CRelaySettingDlg dialog

CString device_str[] = {
	DEVICE_LIGHT_BELT,
	DEVICE_RELAY,
	DEVICE_GREEN_LIGHT,
	DEVICE_RED_LIGHT
};

CString relay_str[] = {
	RELAY_K1,
	RELAY_K2,
	RELAY_K3,
	RELAY_K4
};

IMPLEMENT_DYNAMIC(CRelaySettingDlg, CDialogEx)

CRelaySettingDlg::CRelaySettingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CRelaySettingDlg::IDD, pParent)
	, m_iRelayIndex(0)
	, m_iRelayType(0)
{
	m_bModify = FALSE;
	m_iDeviceType = 0;
	m_iRelayType = 0;
}

CRelaySettingDlg::~CRelaySettingDlg()
{
}

void CRelaySettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_RelaySetting, m_listRelaySetting);
	DDX_CBIndex(pDX, IDC_COMBO_DeviceType, m_iDeviceType);
	DDX_CBIndex(pDX, IDC_COMBO_RelayType, m_iRelayType);
}


BEGIN_MESSAGE_MAP(CRelaySettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CRelaySettingDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Save, &CRelaySettingDlg::OnBnClickedButtonSave)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RelaySetting, &CRelaySettingDlg::OnClickListRelaysetting)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CRelaySettingDlg::OnBnClickedButtonDelete)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDCANCEL, &CRelaySettingDlg::OnBnClickedCancel)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CRelaySettingDlg message handlers

BOOL CRelaySettingDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_listRelaySetting.GetClientRect(rect);
	m_listRelaySetting.SetExtendedStyle(m_listRelaySetting.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listRelaySetting.InsertColumn(0, _T("设备类型"), 0, (rect.Width() - 50) / 2);
	m_listRelaySetting.InsertColumn(1, _T("继电器编号"), 0, (rect.Width() - 50) / 2);

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
		      // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRelaySettingDlg::ReadConfig(void)
{
	USES_CONVERSION;

	CString strSql;
	char* err, **result;
	int row = 0, col = 0;
	sqlite3* db = NULL;
	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}

	strSql = _T("CREATE TABLE IF NOT EXISTS relay_set_table(id integer primary key autoincrement, device_type integer, relay_type integer);");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Create table relay_set_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	strSql = _T("SELECT device_type, relay_type FROM relay_set_table ORDER BY device_type ASC;");
	if (sqlite3_get_table(db, (LPCSTR)W2A(strSql), &result, &row, &col, &err) != SQLITE_OK)
	{
		AfxMessageBox(_T("Query table relay_set_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	DEVICE_RELAY_INFO *info;
	CString str;
	for (int i = 0; i < row; i++) 
	{
		info = new DEVICE_RELAY_INFO;
		info->iDevice = atoi(result[col++]);
		info->iRelay = atoi(result[col++]);
		m_mapRelay.SetAt(info->iDevice, info);

		switch (info->iDevice) 
		{
			case 1:
			{
				str = DEVICE_LIGHT_BELT;
				break;
			}
			case 2:
			{
				str = DEVICE_RELAY;
				break;
			}
			case 3:
			{
				str = DEVICE_GREEN_LIGHT;
				break;
			}
			case 4:
			{
				str = DEVICE_RED_LIGHT;
				break;
			}
			default:
			{
				str = _T("error device");
				break;
			}
		}
		m_listRelaySetting.InsertItem(i, str);
		m_listRelaySetting.SetItemData(i, (DWORD_PTR)info);

		switch (info->iRelay) 
		{
			case 1:
			{
				str = RELAY_K1;
				break;
			}
			case 2:
			{
				str = RELAY_K2;
				break;
			}
			case 3:
			{
				str = RELAY_K3;
				break;
			}
			case 4:
			{
				str = RELAY_K4;
				break;
			}
			default:
			{
				str = _T("error relay");
				break;
			}
		}
		m_listRelaySetting.SetItemText(i, 1, str);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);

	return TRUE;
}

BOOL CRelaySettingDlg::WriteConfig(void)
{
	USES_CONVERSION;

	CString  str;
	CString  strSql;
	sqlite3  *db = NULL;
	char     *err;
	int        row = 0, col = 0;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return FALSE;
	}
	strSql = _T("DELETE FROM relay_set_table;");
	if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Delete table relay_set_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return FALSE;
	}

	DEVICE_RELAY_INFO *info;
	int iDevice;
	POSITION pos = m_mapRelay.GetStartPosition();
	while (pos) 
	{
		m_mapRelay.GetNextAssoc(pos, iDevice, info);
		strSql.Format(_T("INSERT INTO relay_set_table(device_type, relay_type) VALUES(%d, %d);"),
			info->iDevice, info->iRelay);
		if (sqlite3_exec(db, (LPCSTR)W2A(strSql), NULL, NULL, &err) != SQLITE_OK) 
		{
			AfxMessageBox(_T("Insert table relay_set_table failed!"));
			sqlite3_free(err);
			sqlite3_close(db);
			return FALSE;
		}
	}

	sqlite3_close(db);
	return TRUE;
}

void CRelaySettingDlg::OnBnClickedButtonSave()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CRelaySettingDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}

void CRelaySettingDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	DEVICE_RELAY_INFO *info = NULL;
	int iDevice;
	POSITION pos = m_mapRelay.GetStartPosition();
	while (pos)
	{
		m_mapRelay.GetNextAssoc(pos, iDevice, info);
		if (info) 
		{
			delete info;
			info = NULL;
		}
	}
	m_mapRelay.RemoveAll();
}
void CRelaySettingDlg::OnBnClickedButtonAdd()
{
	UpdateData(TRUE);

	DEVICE_RELAY_INFO *info = NULL;
	int relay = 0, iIndex;
	CString str;

	if (!m_bModify) 
	{
		m_mapRelay.Lookup(m_iDeviceType + 1, info);
		if (info) 
		{
			str.Format(_T("设备 %s 已经配置!"), device_str[m_iDeviceType]);
			AfxMessageBox(str);
			return;
		}
		info = new DEVICE_RELAY_INFO;
		info->iDevice = m_iDeviceType + 1;
		info->iRelay = m_iRelayType + 1;
		iIndex = 0;
		m_mapRelay.SetAt(info->iDevice, info);
		m_listRelaySetting.InsertItem(iIndex, device_str[info->iDevice - 1]);
		m_listRelaySetting.SetItemData(iIndex, (DWORD_PTR)info);
	}
	else 
	{
		iIndex = m_listRelaySetting.GetNextItem(-1, LVIS_SELECTED);
		if (iIndex < 0) 
		{
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		info = (DEVICE_RELAY_INFO *)m_listRelaySetting.GetItemData(iIndex);
		//m_mapRelay.Lookup(info->iDevice, info);
		if (info) 
		{
			info->iRelay = m_iRelayType + 1;
			m_mapRelay.SetAt(info->iDevice, info);
		}
	}
	if (info) 
	{
		m_listRelaySetting.SetItemText(iIndex, 1, relay_str[info->iRelay - 1]);
	}
}

void CRelaySettingDlg::OnBnClickedButtonDelete()
{
	int iIndex = -1;
	iIndex = m_listRelaySetting.GetNextItem(-1, LVIS_SELECTED);
	if (iIndex < 0)
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	DEVICE_RELAY_INFO *info = NULL;
	info = (DEVICE_RELAY_INFO *)m_listRelaySetting.GetItemData(iIndex);
	if (info) 
	{
		m_mapRelay.RemoveKey(info->iDevice);
		delete info;
		info = NULL;
	}
	m_listRelaySetting.DeleteItem(iIndex);
}

void CRelaySettingDlg::OnClickListRelaysetting(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);

	DEVICE_RELAY_INFO *info = NULL;
	int iIndex;
	CString str;

	m_bModify = FALSE;
	iIndex = m_listRelaySetting.GetNextItem(-1, LVIS_SELECTED);

	if (iIndex >= 0) 
	{
		m_bModify = TRUE;
		info = (DEVICE_RELAY_INFO *)m_listRelaySetting.GetItemData(iIndex);
		if (info) 
		{
			m_iDeviceType = info->iDevice - 1;
			m_iRelayType = info->iRelay - 1;
		}
	}

	GetDlgItem(IDC_COMBO_DeviceType)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	UpdateData(FALSE);
	*pResult = 0;
}

void CRelaySettingDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	m_bModify = FALSE;

	GetDlgItem(IDC_COMBO_DeviceType)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	CDialogEx::OnLButtonDown(nFlags, point);
}
