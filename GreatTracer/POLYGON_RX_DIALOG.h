#pragma once
#include "VIEWDLG.h"
#include "ScaleVariable.h"
#include "stdlib.h"
#include "time.h"

extern CArray <RxInfo> RxInfoSet;

extern CArray <RxInfo> RxInfoSet;//引用矩形接收机的全局数组
extern int SetPointOnTin;//是否是在TIN上设置的收发信机
extern Vec3T ResultPos;//Opengl中的坐标

extern int SetPointOnTin;//是否是在TIN上设置的收发信机
extern Vec3T ResultPos;//Opengl中的坐标
extern CArray <CPoint> ScrBoundaryPoint;//边界点（屏幕坐标）
extern CArray <Vec3T> GLBoundaryPoint;//边界点（OpenGL坐标）
extern int BoundaryFlag;//边界点已画的个数


// POLYGON_RX_DIALOG 对话框


class POLYGON_RX_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(POLYGON_RX_DIALOG)

public:
	POLYGON_RX_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~POLYGON_RX_DIALOG();

// 对话框数据
	enum { IDD = IDD_POLYGON_RX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();//初始化对话框函数
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//确定按钮函数
};
