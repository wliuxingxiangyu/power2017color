#pragma once
#include "VIEWDLG.h"
#include "ScaleVariable.h" 

extern CArray <TxInfo> TxInfoSet;

extern int SetPointOnTin;//�Ƿ�����TIN�����õ��շ��Ż�
extern Vec3T ResultPos;//Opengl�е�����
extern CArray <CPoint> ScrBoundaryPoint;//�߽�㣨��Ļ���꣩
extern CArray <Vec3T> GLBoundaryPoint;//�߽�㣨OpenGL���꣩
extern int BoundaryFlag;//�߽���ѻ��ĸ���
//extern int SetPointOnTin;//�Ƿ���Tin�������շ��Ż�

extern Vec3T ResultPos;//������CVIEWDLG���е�OpenGL�е���ά������


// POLYGON_TX_DIALOG �Ի���

class POLYGON_TX_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(POLYGON_TX_DIALOG)

public:
	POLYGON_TX_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~POLYGON_TX_DIALOG();

// �Ի�������
	enum { IDD = IDD_POLYGON_TX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();//��ʼ���Ի�����
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//�Ի���ȷ����ť����
};
