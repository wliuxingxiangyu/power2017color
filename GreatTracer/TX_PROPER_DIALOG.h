#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "VIEWDLG.h"
#include "ScaleVariable.h"


// TX_PROPER_DIALOG �Ի���

extern CArray <TxInfo> TxInfoSet;//�������Ϣ
extern CArray <TxInfo> TxInfoSet;


class TX_PROPER_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(TX_PROPER_DIALOG)

public:
	TX_PROPER_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~TX_PROPER_DIALOG();

// �Ի�������
	enum { IDD = IDD_TX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();//�Ի����ʼ������

	DECLARE_MESSAGE_MAP()
public:

	int TestPara(int b);
private:
	CComboBox m_Ante_Combo;
public:
	CComboBox m_Wave_Combo;
	afx_msg void OnBnClickedOk();//ȷ����ť����
};
