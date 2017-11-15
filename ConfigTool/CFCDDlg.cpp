// CFCDDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "CFCDDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CCFCDDlg, CDialogEx)

CCFCDDlg::CCFCDDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCFCDDlg::IDD, pParent)
	, m_strSOC(_T(""))
	, m_strCurrent(_T(""))
{
	m_iStartHour = 0;
	m_iStartMinute = 0;
	m_iStopHour = 0;
	m_iStopMinute = 0;
	m_iPeriod = 0;
	m_bModify = FALSE;
	m_iCurrentIndex = -1;
	m_edtSOC.SetTextLength(3);
	m_edtCurrent.SetTextLength(4);
}

CCFCDDlg::~CCFCDDlg()
{
}

void CCFCDDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_CFCD, m_listCFCD);
	DDX_CBIndex(pDX, IDC_COMBO_StartHour, m_iStartHour);
	DDX_CBIndex(pDX, IDC_COMBO_StartMinute, m_iStartMinute);
	DDX_CBIndex(pDX, IDC_COMBO_StopHour, m_iStopHour);
	DDX_CBIndex(pDX, IDC_COMBO_StopMinute, m_iStopMinute);
	DDX_Text(pDX, IDC_EDIT_SOC, m_strSOC);
	DDX_Text(pDX, IDC_EDIT_Current, m_strCurrent);
	DDX_CBIndex(pDX, IDC_COMBO_Period, m_iPeriod);
	DDX_Control(pDX, IDC_EDIT_SOC, m_edtSOC);
	DDX_Control(pDX, IDC_EDIT_Current, m_edtCurrent);
	DDX_Check(pDX, IDC_CHECK_CFCDEnable, m_bCFCDEnable);
	DDX_Check(pDX, IDC_CHECK_Prioty, m_bCarPrioty);
}

BEGIN_MESSAGE_MAP(CCFCDDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_CFCDExit, &CCFCDDlg::OnBnClickedButtonCfcdexit)
	ON_BN_CLICKED(IDC_BUTTON_CFCDSave, &CCFCDDlg::OnBnClickedButtonCfcdsave)
	ON_BN_CLICKED(IDC_BUTTON_CFCDAdd, &CCFCDDlg::OnBnClickedButtonCfcdadd)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_CFCDDelete, &CCFCDDlg::OnBnClickedButtonCfcddelete)
	ON_CBN_SELCHANGE(IDC_COMBO_Period, &CCFCDDlg::OnCbnSelchangeComboPeriod)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CFCD, &CCFCDDlg::OnNMDblclkListCfcd)
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_CHECK_CFCDEnable, &CCFCDDlg::OnBnClickedCheckCfcdenable)
END_MESSAGE_MAP()

BOOL CCFCDDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_listCFCD.GetClientRect(rect);
	m_listCFCD.SetExtendedStyle(m_listCFCD.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listCFCD.InsertColumn(0, _T("时段"), 0, (rect.Width() - 25) / 5);
	m_listCFCD.InsertColumn(1, _T("起始时间"), 0, (rect.Width() - 25) / 5);
	m_listCFCD.InsertColumn(2, _T("结束时间"), 0, (rect.Width() - 25) / 5);
	m_listCFCD.InsertColumn(3, _T("SOC限值"), 0, (rect.Width() - 25) / 5);
	m_listCFCD.InsertColumn(4, _T("电流限值"), 0, (rect.Width() - 25) / 5);

	CString str;
	for (int i = 0; i < 24; i++) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_StartHour))->AddString(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_StopHour))->AddString(str);
	}
	for (int i = 0; i < 60; i += 30) 
	{
		str.Format(_T("%d"), i);
		((CComboBox *)GetDlgItem(IDC_COMBO_StartMinute))->AddString(str);
		((CComboBox *)GetDlgItem(IDC_COMBO_StopMinute))->AddString(str);
	}

	((CComboBox *)GetDlgItem(IDC_COMBO_Period))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_StartHour))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_StartMinute))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_StopHour))->SetCurSel(23);
	((CComboBox *)GetDlgItem(IDC_COMBO_StopMinute))->SetCurSel(1);
	GetDlgItem(IDC_BUTTON_CFCDAdd)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CFCDDelete)->EnableWindow(FALSE);

	//ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CCFCDDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	for (int i = 0; i < 4; i++) 
	{
		m_arCache[i].RemoveAll();
	}
}

void CCFCDDlg::OnBnClickedButtonCfcdexit()
{
	CDialogEx::OnCancel();
}

void CCFCDDlg::OnBnClickedButtonCfcdsave()
{
	//WriteConfig();

	CDialogEx::OnOK();
}

#if 0
void CCFCDDlg::ReadConfig(void)
{
	char* err = NULL, **result;
	CStringA strSql;
	int row = 0, col = 0;
	CString str, strFile = _T(".\\config.ini");

	::GetPrivateProfileString(_T("SMART_CHARGE"), _T("SmartCharge_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_bCFCDEnable = (str == "true" ? true : false);
	str.ReleaseBuffer();

	::GetPrivateProfileString(_T("SMART_CAR"), _T("SmartCar_Enable"), _T(""), str.GetBuffer(MAX_PATH), MAX_PATH, strFile);
	m_bCarPrioty = (str == "true" ? true : false);
	if (!m_bCFCDEnable)
		m_bCarPrioty = false;

	UpdateData(FALSE);
	OnBnClickedCheckCfcdenable();

	sqlite3* db = NULL;
	sqlite3_open("param_config.db", &db);
	if (!db)
	{
		AfxMessageBox(_T("open database failed!"));
		return;
	}
	strSql = _T("create table if not exists tpfv_param_table(id integer primary key  autoincrement,\
				time_seg integer, start_hour integer, start_minute integer, stop_hour integer, \
				stop_minute integer, limit_soc integer, limit_current integer); ");
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK)
	{
		AfxMessageBox(_T("Create table tpfv_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	strSql = _T("SELECT * FROM tpfv_param_table");
	if (sqlite3_get_table(db, (LPCSTR)strSql, &result, &row, &col, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Query table tpfv_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	for (int i = 0; i < row; i++) 
	{
		CFCD_INFO info;
		memset(&info, 0, sizeof(CFCD_INFO));
		info.iId = atoi(result[col++]);
		info.iPeriod = atoi(result[col++]);
		info.iStartHour = atoi(result[col++]);
		info.iStartMinute = atoi(result[col++]);
		info.iStopHour = atoi(result[col++]);
		info.iStopMinute = atoi(result[col++]);
		info.iSoc = atoi(result[col++]);
		info.iCurrent = atoi(result[col++]);
		m_arCache[info.iPeriod - 1].Add(info);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);

	OnCbnSelchangeComboPeriod();
}

void CCFCDDlg::WriteConfig(void)
{
	//USES_CONVERSION; 
	//strStart = W2A(m_listCFCD.GetItemText(i, 1));
	UpdateData(TRUE);

	CString str, strFile = _T(".\\config.ini");
	str = m_bCFCDEnable ? "true" : "false";
	::WritePrivateProfileString(_T("SMART_CHARGE"), _T("SmartCharge_Enable"), str, strFile);
	str = m_bCarPrioty ? "true" : "false";
	::WritePrivateProfileString(_T("SMART_CAR"), _T("SmartCar_Enable"), str, strFile);

	CStringA strSql;
	char* err;
	CFCD_INFO info;
	sqlite3* db = NULL;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return;
	}
	strSql = "DELETE FROM tpfv_param_table;";
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK)
	{
		AfxMessageBox(_T("Delete table tpfv_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < m_arCache[i].GetCount(); j++) 
		{
			info = m_arCache[i].GetAt(j);
			strSql.Format("INSERT INTO tpfv_param_table(time_seg, start_hour, start_minute, stop_hour, \
						  stop_minute, limit_soc, limit_current) VALUES(%d, %d, %d, %d, %d, %d, %d);",
				info.iPeriod, info.iStartHour, info.iStartMinute, info.iStopHour, info.iStopMinute, info.iSoc, info.iCurrent);
			if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
			{
				AfxMessageBox(_T("Create table tpfv_param_table failed!"));
				sqlite3_free(err);
				sqlite3_close(db);
				return;
			}
		}
	}
}
#endif

void CCFCDDlg::OnBnClickedButtonCfcdadd()
{
	CString str, strTime;
	int iCount = 0, iIndex = -1;

	UpdateData(TRUE);

	CFCD_INFO info;
	memset(&info, 0, sizeof(CFCD_INFO));
	info.iPeriod = m_iPeriod;
	info.iStartHour = m_iStartHour;
	info.iStartMinute = m_iStartMinute * 30;
	info.iStopHour = m_iStopHour;
	info.iStopMinute = m_iStopMinute * 30;
	info.iSoc = _ttoi(m_strSOC);
	info.iCurrent = _ttoi(m_strCurrent);

	if (!m_bModify) 
	{
		iCount = m_listCFCD.GetItemCount();
		if (iCount >= 5) 
		{
			AfxMessageBox(_T("最多设置五个时间段！"));
			return;
		}
		((CComboBox *)GetDlgItem(IDC_COMBO_Period))->GetLBText(m_iPeriod, str);
		m_listCFCD.InsertItem(iCount, str);
		strTime.Format(_T("%02d:%02d"), m_iStartHour, m_iStartMinute * 30);
		m_listCFCD.SetItemText(iCount, 1, strTime);
		strTime.Format(_T("%02d:%02d"), m_iStopHour, m_iStopMinute * 30);
		m_listCFCD.SetItemText(iCount, 2, strTime);
		m_listCFCD.SetItemText(iCount, 3, m_strSOC);
		m_listCFCD.SetItemText(iCount, 4, m_strCurrent);
		m_arCache[m_iPeriod - 1].Add(info);
	}
	else 
	{
		if (m_iCurrentIndex < 0) {
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		strTime.Format(_T("%02d:%02d"), m_iStartHour, m_iStartMinute * 30);
		m_listCFCD.SetItemText(m_iCurrentIndex, 1, strTime);
		strTime.Format(_T("%02d:%02d"), m_iStopHour, m_iStopMinute * 30);
		m_listCFCD.SetItemText(m_iCurrentIndex, 2, strTime);
		m_listCFCD.SetItemText(m_iCurrentIndex, 3, m_strSOC);
		m_listCFCD.SetItemText(m_iCurrentIndex, 4, m_strCurrent);
		info.iId = m_arCache[m_iPeriod - 1].GetAt(m_iCurrentIndex).iId;
		m_arCache[m_iPeriod - 1].RemoveAt(m_iCurrentIndex);
		m_arCache[m_iPeriod - 1].InsertAt(m_iCurrentIndex, info);
	}

	m_bModify = FALSE;
	GetDlgItem(IDC_BUTTON_CFCDAdd)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));
}

void CCFCDDlg::OnBnClickedButtonCfcddelete()
{
	int index;
	index = m_listCFCD.GetNextItem(-1, LVIS_SELECTED);
	if (index < 0) 
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	m_listCFCD.DeleteItem(index);
	m_arCache[m_iPeriod - 1].RemoveAt(index);
}

void CCFCDDlg::OnCbnSelchangeComboPeriod()
{
	int iFirst, iLast;

	UpdateData(TRUE);
	m_listCFCD.DeleteAllItems();

	if (m_iPeriod == 0) 
	{
		GetDlgItem(IDC_BUTTON_CFCDAdd)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_CFCDDelete)->EnableWindow(FALSE);
		iFirst = 1;
		iLast = 5;
	}
	else 
	{
		GetDlgItem(IDC_BUTTON_CFCDAdd)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CFCDDelete)->EnableWindow(TRUE);
		iFirst = m_iPeriod;
		iLast = m_iPeriod + 1;
	}

	CFCD_INFO info;
	CString str;
	int iCount;
	for (int i = iFirst; i < iLast; i++)
	{
		for (int j = 0; j < m_arCache[i - 1].GetCount(); j++) 
		{
			info = m_arCache[i - 1].GetAt(j);
			iCount = m_listCFCD.GetItemCount();
			((CComboBox *)GetDlgItem(IDC_COMBO_Period))->GetLBText(i, str);
			m_listCFCD.InsertItem(iCount, str);
			str.Format(_T("%02d:%02d"), info.iStartHour, info.iStartMinute);
			m_listCFCD.SetItemText(iCount, 1, str);
			str.Format(_T("%02d:%02d"), info.iStopHour, info.iStopMinute);
			m_listCFCD.SetItemText(iCount, 2, str);
			str.Format(_T("%d"), info.iSoc);
			m_listCFCD.SetItemText(iCount, 3, str);
			str.Format(_T("%d"), info.iCurrent);
			m_listCFCD.SetItemText(iCount, 4, str);
		}
	}
}

void CCFCDDlg::OnNMDblclkListCfcd(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CFCD_INFO info;
	int iIndex;

	UpdateData(TRUE);

	if (m_iPeriod <= 0)
		return;

	iIndex = m_listCFCD.GetNextItem(-1, LVIS_SELECTED);
	if (iIndex >= 0) 
	{
		info = m_arCache[m_iPeriod - 1].GetAt(iIndex);
		m_iStartHour = info.iStartHour;
		m_iStartMinute = info.iStartMinute / 30;
		m_iStopHour = info.iStopHour;
		m_iStopMinute = info.iStopMinute / 30;
		m_strSOC.Format(_T("%d"), info.iSoc);
		m_strCurrent.Format(_T("%d"), info.iCurrent);
		m_bModify = TRUE;
		m_iCurrentIndex = iIndex;
	}
	else 
	{
		m_bModify = FALSE;
		m_iCurrentIndex = -1;
	}

	GetDlgItem(IDC_BUTTON_CFCDAdd)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));

	UpdateData(FALSE);
	*pResult = 0;
}


void CCFCDDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bModify) 
	{
		m_iCurrentIndex = -1;
		m_bModify = FALSE;
		GetDlgItem(IDC_BUTTON_CFCDAdd)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCFCDDlg::OnBnClickedCheckCfcdenable()
{
	UpdateData(TRUE);
	GetDlgItem(IDC_COMBO_Period)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_COMBO_StartHour)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_COMBO_StartMinute)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_COMBO_StopHour)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_COMBO_StopMinute)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_EDIT_SOC)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_EDIT_Current)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_LIST_CFCD)->EnableWindow(m_bCFCDEnable);
	GetDlgItem(IDC_CHECK_Prioty)->EnableWindow(m_bCFCDEnable);
	if (!m_bCFCDEnable)
		m_bCarPrioty = false;
	UpdateData(FALSE);
}
