// GreatTracerDlg.h : ͷ�ļ�
//

#pragma once
#include "VIEWDLG.h"

// CGreatTracerDlg �Ի���
class CGreatTracerDlg : public CDialog
{
// ����
public:
	CGreatTracerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GREATTRACER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;
	CMenu m_Menu;//�˵�Instance
	CListCtrl clc;//ListControl Instance


	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();//�Ի����ʼ������
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();//OnPaint()����
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewProjectview();//Projectview��ť����
	afx_msg void OnHelpAbout();
};
