#pragma once
#include "stdafx.h"
#include "afxwin.h"
#include "VIEWDLG.h"
#include "ScaleVariable.h"


// TX_PROPER_DIALOG 对话框

extern CArray <TxInfo> TxInfoSet;//发射机信息
extern CArray <TxInfo> TxInfoSet;


class TX_PROPER_DIALOG : public CDialog
{
	DECLARE_DYNAMIC(TX_PROPER_DIALOG)

public:
	TX_PROPER_DIALOG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~TX_PROPER_DIALOG();

// 对话框数据
	enum { IDD = IDD_TX_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();//对话框初始化函数

	DECLARE_MESSAGE_MAP()
public:

	int TestPara(int b);
private:
	CComboBox m_Ante_Combo;
public:
	CComboBox m_Wave_Combo;
	afx_msg void OnBnClickedOk();//确定按钮函数
};
