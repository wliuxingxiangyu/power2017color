#pragma once
#include "ScaleVariable.h"


extern CArray <AntennaInfo> AnteInfo;//������Ϣ


// ANTE_DIALOG �Ի���

class ANTE_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(ANTE_DIALOG)

public:
	ANTE_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ANTE_DIALOG();

// �Ի�������
	enum { IDD = IDD_ANTE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();//�Ի����ʼ������
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//ȷ����ť����

};
