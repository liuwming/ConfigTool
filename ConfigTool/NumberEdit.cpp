// EditEx.cpp : implementation file
//

#include "stdafx.h"
#include "ConfigTool.h"
#include "NumberEdit.h"

// CNumberEdit

IMPLEMENT_DYNAMIC(CNumberEdit, CEdit)

CNumberEdit::CNumberEdit()
{
	m_iTextLength = 6;
}

CNumberEdit::~CNumberEdit()
{
}

BEGIN_MESSAGE_MAP(CNumberEdit, CEdit)
	ON_WM_CHAR()
END_MESSAGE_MAP()

// CNumberEdit message handlers

BOOL CNumberEdit::SetTextLength(int iLength)
{
	if(iLength > 0)
	{
		m_iTextLength = iLength;
		return TRUE;
	}
	return FALSE;
}

void CNumberEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CString str, strText;
	int iStart = 0, iEnd = 0;

	if(nChar == 8)
	{
		CEdit::OnChar(nChar, nRepCnt, nFlags);
		return;
	}

	if(nChar >= 48 && nChar <= 57)
	{
		GetWindowText(str);
		if(str.GetLength() >= m_iTextLength)
		{
			GetSel(iStart, iEnd);
			if(iEnd > iStart)
			{
				GetWindowText(strText);
				str = strText.Left(iStart);
				strText = strText.Mid(iEnd);
				strText = str + strText;
				strText.Insert(iStart, nChar);
				SetWindowText(strText);
				SetSel(iStart + 1, iStart + 1);
			}
			return;
		}
		CEdit::OnChar(nChar, nRepCnt, nFlags);
	}
}
