// PhaseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "PhaseDlg.h"
#include "afxdialogex.h"

IMPLEMENT_DYNAMIC(CPhaseDlg, CDialogEx)

CPhaseDlg::CPhaseDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPhaseDlg::IDD, pParent)
{
	m_bModify		= FALSE;
	m_iCurrentIndex = -1;
	m_iAddr			= 0;
	m_iPhase        = 0;
}

CPhaseDlg::~CPhaseDlg()
{
}

void CPhaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_Phase, m_listPhase);
	DDX_CBIndex(pDX, IDC_COMBO_Addr, m_iAddr);
	DDX_CBIndex(pDX, IDC_COMBO_Phase, m_iPhase);
}

BEGIN_MESSAGE_MAP(CPhaseDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_PhaseExit, &CPhaseDlg::OnBnClickedButtonPhaseexit)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_PhaseSave, &CPhaseDlg::OnBnClickedButtonPhasesave)
	ON_BN_CLICKED(IDC_BUTTON_Add, &CPhaseDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_Delete, &CPhaseDlg::OnBnClickedButtonDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_Phase, &CPhaseDlg::OnNMDblclkListPhase)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

BOOL CPhaseDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CRect rect;
	m_listPhase.GetClientRect(rect);
	m_listPhase.SetExtendedStyle(m_listPhase.GetExtendedStyle() | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_listPhase.InsertColumn(0, _T("can地址"), 0, (rect.Width() - 10) / 2);
	m_listPhase.InsertColumn(1, _T("相别"), 0, (rect.Width() - 10) / 2);

	CString str;
	PHASE_INFO *info;
	for (int i = 0; i < 110; i++) 
	{
		info = new PHASE_INFO;
		memset(info, 0, sizeof(PHASE_INFO));
		info->iAddr = i + 1;
		m_arPhase.Add(info);
		str.Format(_T("%d"), i + 1);
		((CComboBox *)GetDlgItem(IDC_COMBO_Addr))->AddString(str);
	}
	((CComboBox *)GetDlgItem(IDC_COMBO_Addr))->SetCurSel(0);
	((CComboBox *)GetDlgItem(IDC_COMBO_Phase))->SetCurSel(0);

	ReadConfig();

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CPhaseDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	PHASE_INFO* info;
	for (int i = 0; i < m_arPhase.GetCount(); i++) 
	{
		info = m_arPhase.GetAt(i);
		if (info) 
		{
			delete info;
			info = NULL;
		}
	}
	m_arPhase.RemoveAll();
}

void CPhaseDlg::OnBnClickedButtonPhaseexit()
{
	CDialogEx::OnCancel();
}

void CPhaseDlg::OnBnClickedButtonPhasesave()
{
	WriteConfig();
	CDialogEx::OnOK();
}

void CPhaseDlg::OnBnClickedButtonAdd()
{
	CString str;
	int iCount = 0;
	PHASE_INFO* info;

	UpdateData(TRUE);

	info = m_arPhase.GetAt(m_iAddr);
	iCount = m_listPhase.GetItemCount();

	if (!m_bModify) 
	{
		if (info->iPhase > 0) 
		{
			AfxMessageBox(_T("该地址已设置相别！"));
			return;
		}
		((CComboBox *)GetDlgItem(IDC_COMBO_Addr))->GetLBText(m_iAddr, str);
		m_listPhase.InsertItem(iCount, str);
		((CComboBox *)GetDlgItem(IDC_COMBO_Phase))->GetLBText(m_iPhase, str);
		if (str == _T("A相"))
			info->iPhase = 1;
		else if (str == _T("B相"))
			info->iPhase = 2;
		else if (str == _T("C相"))
			info->iPhase = 3;
		else
			return;
		m_listPhase.SetItemText(iCount, 1, str);
	}
	else 
	{
		if (m_iCurrentIndex < 0) 
		{
			AfxMessageBox(_T("请选择一条记录！"));
			return;
		}
		((CComboBox *)GetDlgItem(IDC_COMBO_Addr))->GetLBText(m_iAddr, str);
		info->iAddr = _ttoi(str);
		m_listPhase.SetItemText(m_iCurrentIndex, 0, str);
		((CComboBox *)GetDlgItem(IDC_COMBO_Phase))->GetLBText(m_iPhase, str);
		if (str == _T("A相"))
			info->iPhase = 1;
		else if (str == _T("B相"))
			info->iPhase = 2;
		else if (str == _T("C相"))
			info->iPhase = 3;
		m_listPhase.SetItemText(m_iCurrentIndex, 1, str);
	}
	m_bModify = FALSE;
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));
}

void CPhaseDlg::OnBnClickedButtonDelete()
{
	int index = -1;
	index = m_listPhase.GetNextItem(-1, LVIS_SELECTED);
	if (index < 0) 
	{
		AfxMessageBox(_T("请选择一条记录！"));
		return;
	}

	UpdateData(TRUE);

	PHASE_INFO* info;
	CString str;
	int iAddr;

	str = m_listPhase.GetItemText(index, 0);
	iAddr = _ttoi(str);
	if (iAddr <= 0 || iAddr > 110) 
	{
		AfxMessageBox(_T("can地址错误！"));
		return;
	}
	info = m_arPhase.GetAt(iAddr - 1);
	info->iPhase = 0;
	m_listPhase.DeleteItem(index);
}

void CPhaseDlg::ReadConfig(void)
{
	CStringA strSql;
	char* err, **result;
	int row = 0, col = 0;

	sqlite3* db = NULL;
	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return;
	}

	strSql = _T("CREATE TABLE IF NOT EXISTS phasetype_param_table(id integer primary key autoincrement, canaddr integer,phase_type integer);");
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Create table phasetype_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	strSql = _T("SELECT * FROM phasetype_param_table;");
	if (sqlite3_get_table(db, (LPCSTR)strSql, &result, &row, &col, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Query table phasetype_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	CString str;
	int iAddr;
	PHASE_INFO* info;
	for (int i = 0; i < row; i++) 
	{
		col++;
		iAddr = atoi(result[col++]);
		if (iAddr <= 0 || iAddr > 110) 
		{
			AfxMessageBox(_T("相别数据不合法"));
			sqlite3_free_table(result);
			sqlite3_close(db);
			return;
		}
		info = m_arPhase.GetAt(iAddr - 1);
		info->iAddr = iAddr;
		info->iPhase = atoi(result[col++]);

		str.Format(_T("%d"), info->iAddr);
		m_listPhase.InsertItem(i, str);
		switch (info->iPhase) 
		{
			case 1:
			{
				str = _T("A相");
				break;
			}
			case 2:
			{
				str = _T("B相");
				break;
			}
			case 3:
			{
				str = _T("C相");
				break;
			}
			default:
			{
				AfxMessageBox(_T("相别数据不合法"));
				sqlite3_free_table(result);
				sqlite3_close(db);
				return;
			}
		}
		m_listPhase.SetItemText(i, 1, str);
	}

	sqlite3_free_table(result);
	sqlite3_close(db);
}

void CPhaseDlg::WriteConfig(void)
{
	CStringA strSql;
	char* err;
	sqlite3* db = NULL;

	sqlite3_open("param_config.db", &db);
	if (!db) 
	{
		AfxMessageBox(_T("open database failed!"));
		return;
	}

	strSql = "DELETE FROM phasetype_param_table;";
	if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
	{
		AfxMessageBox(_T("Delete table phasetype_param_table failed!"));
		sqlite3_free(err);
		sqlite3_close(db);
		return;
	}

	CString strAddr, strPhase;
	int iAddr = 0, iPhase = 0;
	for (int i = 0; i < m_listPhase.GetItemCount(); i++) 
	{
		strAddr = m_listPhase.GetItemText(i, 0);
		iAddr = _ttoi(strAddr);
		strPhase = m_listPhase.GetItemText(i, 1);
		if (strPhase == _T("A相"))
			iPhase = 1;
		else if (strPhase == _T("B相"))
			iPhase = 2;
		else if (strPhase == _T("C相"))
			iPhase = 3;

		strSql.Format("INSERT INTO phasetype_param_table(canaddr, phase_type)VALUES(%d, %d);", iAddr, iPhase);
		if (sqlite3_exec(db, (LPCSTR)strSql, NULL, NULL, &err) != SQLITE_OK) 
		{
			AfxMessageBox(_T("Create table phasetype_param_table failed!"));
			sqlite3_free(err);
			sqlite3_close(db);
			return;
		}
	}

	sqlite3_close(db);
}

void CPhaseDlg::OnNMDblclkListPhase(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	CString str;

	UpdateData(TRUE);

	m_iCurrentIndex = m_listPhase.GetNextItem(-1, LVIS_SELECTED);
	if (m_iCurrentIndex >= 0) 
	{
		str = m_listPhase.GetItemText(m_iCurrentIndex, 0);
		m_iAddr = _ttoi(str) - 1;
		str = m_listPhase.GetItemText(m_iCurrentIndex, 1);
		if (str == _T("A相"))
			m_iPhase = 0;
		else if (str == _T("B相"))
			m_iPhase = 1;
		else if (str == _T("C相"))
			m_iPhase = 2;
		m_bModify = TRUE;
	}
	else 
	{
		//m_iAddr = 0;
		//m_iPhase = 0;
		m_bModify = FALSE;
	}

	GetDlgItem(IDC_COMBO_Addr)->EnableWindow(m_bModify ? FALSE : TRUE);
	GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));
	UpdateData(FALSE);
	*pResult = 0;
}


void CPhaseDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_bModify) 
	{
		m_iCurrentIndex = -1;
		m_bModify       = FALSE;
		m_iAddr         = 0;
		m_iPhase        = 0;
		GetDlgItem(IDC_COMBO_Addr)->EnableWindow(m_bModify ? FALSE : TRUE);
		GetDlgItem(IDC_BUTTON_Add)->SetWindowText(m_bModify ? _T("修改") : _T("添加"));
		UpdateData(FALSE);
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}
