#pragma once
#include "VIEWDLG.h"
#include "ScaleVariable.h"


// RX_DIALOG �Ի���
extern CArray <RxInfo> RxInfoSet;
extern CArray <RxInfo> RxInfoSet;//���ջ���Ϣ
extern CArray <RxInfo> RxInfoSet;

class RX_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(RX_DIALOG)

public:
	RX_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RX_DIALOG();

// �Ի�������
	enum { IDD = IDD_RX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();//�Ի����ʼ������
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//ȷ����ť����
};
