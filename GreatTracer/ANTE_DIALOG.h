#pragma once
#include "ScaleVariable.h"


extern CArray <AntennaInfo> AnteInfo;//天线信息


// ANTE_DIALOG 对话框

class ANTE_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(ANTE_DIALOG)

public:
	ANTE_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ANTE_DIALOG();

// 对话框数据
	enum { IDD = IDD_ANTE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();//对话框初始化函数
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();//确定按钮函数

};
