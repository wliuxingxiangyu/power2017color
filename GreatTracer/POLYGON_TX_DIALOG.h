#pragma once
#include "VIEWDLG.h"
#include "ScaleVariable.h" 

extern CArray <TxInfo> TxInfoSet;

extern int SetPointOnTin;//是否是在TIN上设置的收发信机
extern Vec3T ResultPos;//Opengl中的坐标
extern CArray <CPoint> ScrBoundaryPoint;//边界点（屏幕坐标）
extern CArray <Vec3T> GLBoundaryPoint;//边界点（OpenGL坐标）
extern int BoundaryFlag;//边界点已画的个数
//extern int SetPointOnTin;//是否在Tin上设置收发信机

extern Vec3T ResultPos;//定义在CVIEWDLG类中的OpenGL中的三维坐标结果


// POLYGON_TX_DIALOG 对话框

class POLYGON_TX_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(POLYGON_TX_DIALOG)

public:
	POLYGON_TX_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~POLYGON_TX_DIALOG();

// 对话框数据
	enum { IDD = IDD_POLYGON_TX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();//初始化对话框函数
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//对话框确定按钮函数
};
