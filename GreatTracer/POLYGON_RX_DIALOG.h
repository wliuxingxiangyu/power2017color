#pragma once
#include "VIEWDLG.h"
#include "ScaleVariable.h"
#include "stdlib.h"
#include "time.h"

extern CArray <RxInfo> RxInfoSet;

extern CArray <RxInfo> RxInfoSet;//���þ��ν��ջ���ȫ������
extern int SetPointOnTin;//�Ƿ�����TIN�����õ��շ��Ż�
extern Vec3T ResultPos;//Opengl�е�����

extern int SetPointOnTin;//�Ƿ�����TIN�����õ��շ��Ż�
extern Vec3T ResultPos;//Opengl�е�����
extern CArray <CPoint> ScrBoundaryPoint;//�߽�㣨��Ļ���꣩
extern CArray <Vec3T> GLBoundaryPoint;//�߽�㣨OpenGL���꣩
extern int BoundaryFlag;//�߽���ѻ��ĸ���


// POLYGON_RX_DIALOG �Ի���


class POLYGON_RX_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(POLYGON_RX_DIALOG)

public:
	POLYGON_RX_DIALOG(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~POLYGON_RX_DIALOG();

// �Ի�������
	enum { IDD = IDD_POLYGON_RX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();//��ʼ���Ի�����
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//ȷ����ť����
};
