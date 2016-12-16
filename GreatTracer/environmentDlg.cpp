// environmentDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "environmentDlg.h"
#include "afxdialogex.h"


// environmentDlg dialog

IMPLEMENT_DYNAMIC(environmentDlg, CDialogEx)

environmentDlg::environmentDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(environmentDlg::IDD, pParent)
{

}

environmentDlg::~environmentDlg()
{
}

void environmentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(environmentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &environmentDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// environmentDlg message handlers
BOOL environmentDlg::OnInitDialog(){
	SetDlgItemText(IDC_Describe,"0");
	SetDlgItemText(IDC_Density,"3");
	return 0;
}

void environmentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	EnvironmentInfo EnvExam;
	CString temp;
	GetDlgItemText(IDC_Describe,temp);
	EnvExam.DescribeMode=atoi(temp);
	GetDlgItemText(IDC_Density,temp);
	EnvExam.Density=(GLfloat)(atof(temp));
	EnvInfo.Add(EnvExam);
	OnOK();

}
