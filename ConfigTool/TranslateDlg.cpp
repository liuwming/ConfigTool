// TranslateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "TranslateDlg.h"
#include "afxdialogex.h"


// CTranslateDlg dialog

IMPLEMENT_DYNAMIC(CTranslateDlg, CDialogEx)

CTranslateDlg::CTranslateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTranslateDlg::IDD, pParent)
	, m_strKey1(_T(""))
	, m_strKey2(_T(""))
{

}

CTranslateDlg::~CTranslateDlg()
{
}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_Key1, m_strKey1);
	DDX_Text(pDX, IDC_EDIT_Key2, m_strKey2);
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_Translate, &CTranslateDlg::OnBnClickedButtonTranslate)
	//	ON_WM_CHAR()
END_MESSAGE_MAP()


// CTranslateDlg message handlers

void CTranslateDlg::OnBnClickedButtonTranslate()
{
	USES_CONVERSION;

	UpdateData(TRUE);

	m_strKey2 = theApp.StringToHex(W2A(m_strKey1));

	UpdateData(FALSE);
}