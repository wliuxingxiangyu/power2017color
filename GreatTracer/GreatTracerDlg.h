// GreatTracerDlg.h : 头文件
//

#pragma once
#include "VIEWDLG.h"

// CGreatTracerDlg 对话框
class CGreatTracerDlg : public CDialog
{
// 构造
public:
	CGreatTracerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GREATTRACER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CMenu m_Menu;//菜单Instance
	CListCtrl clc;//ListControl Instance


	// 生成的消息映射函数
	virtual BOOL OnInitDialog();//对话框初始化函数
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();//OnPaint()函数
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewProjectview();//Projectview按钮代码
	afx_msg void OnHelpAbout();
};
