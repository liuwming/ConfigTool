#pragma once

// CNumberEdit

class CNumberEdit : public CEdit
{
	DECLARE_DYNAMIC(CNumberEdit)

public:
	CNumberEdit();
	virtual ~CNumberEdit();

protected:
	DECLARE_MESSAGE_MAP()

private:
	int m_iTextLength;

public:
	BOOL SetTextLength(int iLength);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
};


