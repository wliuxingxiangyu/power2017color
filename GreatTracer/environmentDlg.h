#pragma once
#include "ScaleVariable.h"

extern CArray <EnvironmentInfo> EnvInfo;

// environmentDlg dialog

class environmentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(environmentDlg)

public:
	environmentDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~environmentDlg();

// Dialog Data
	enum { IDD =IDD_ENVIRONMENT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();//�Ի����ʼ������
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
