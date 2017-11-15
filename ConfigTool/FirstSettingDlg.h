#pragma once
#include "afxwin.h"
#include "DLEdit.h"
#include "NumberEdit.h"

// CFirstSettingDlg dialog

class CFirstSettingDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFirstSettingDlg)

public:
	CFirstSettingDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CFirstSettingDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG_FirstSetting };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	int m_iPassword;
	int m_iTEUIType;
	int m_iBoard;
	int m_iCardType;
	int m_iShowButton;
	int m_iVinType;
	int m_iTicketOpen;
	int m_iCardMultiChoose;
	int m_iSinglePileGroup;
	int m_iAbnormal;
	int m_iCardAuto;
	int m_iVinAuto;	
	int m_iRemoteEncrypt;
	int m_iLocalEncrypt;
	CString m_strDirect;
	CString m_strSingle;
	CString m_strThree;
	CString m_strNet1Ip;
	CString m_strNet1Mask;
	CString m_strNet1Gateway;
	CString m_strNet2Ip;
	CString m_strNet2Mask;
	CString m_strNet2Gateway;
	CString m_strDNS;
	CString m_strCan0Addr;
	CString m_strCan0Baud;
	CString m_strCan1Addr;
	CString m_strCan1Baud;
	CString m_strRemoteKey;
	CString m_strRemoteIp;
	CString m_strRemotePort;
	CString m_strRemoteStation;
	CString m_strLocalKey;
	CString m_strLocalIp;
	CString m_strLocalPort;
	CString m_strLocalStation;
	CString m_strWebPort;
	CString m_strOperatorId;
	CString m_strOperatorSecret;
	CString m_strDataSecret;
	CString m_strWebAesKey;
	CString m_strWebAesIV;
	CString m_strWebUrl;
	CNumberEdit m_edtDirect;
	CNumberEdit m_edtSingle;
	CNumberEdit m_edtThree;
	CNumberEdit m_edtPassword;
	CNumberEdit m_edtCan0Addr;
	CNumberEdit m_edtCan0Baud;
	CNumberEdit m_edtCan1Addr;
	CNumberEdit m_edtCan1Baud;
	CNumberEdit m_edtRemotePort;
	CNumberEdit m_edtLocalPort;

	virtual BOOL OnInitDialog();
	BOOL WriteConfig(void);
	BOOL ReadConfig(void);
	afx_msg void OnCbnSelchangeComboWeburl();
};
