// RX_DIALOG.cpp : 实现文件
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "RX_DIALOG.h"

CVIEWDLG *cview2;

// RX_DIALOG 对话框

IMPLEMENT_DYNAMIC(RX_DIALOG, CDialog)

RX_DIALOG::RX_DIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(RX_DIALOG::IDD, pParent)
{

}

RX_DIALOG::~RX_DIALOG()
{
}

void RX_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(RX_DIALOG, CDialog)
	ON_BN_CLICKED(IDOK, &RX_DIALOG::OnBnClickedOk)
END_MESSAGE_MAP()


// RX_DIALOG 消息处理程序

void RX_DIALOG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	CString temp;
	cview2->AddEle();
	int a =RxInfoSet.GetCount();
	for(int i=0;i<a;i++){
		GetDlgItemText(IDC_EDIT_RX_PZ_DES,temp);
		RxInfoSet[i].Description=temp;

		if(RxInfoSet[i].Pos.z<0){
			GetDlgItemText(IDC_EDIT__RX_PZ_Z,temp);
			RxInfoSet[i].Pos.z=(GLfloat)atof(temp);
			cview2->Deal_Rx_Vertex_Cube(RxInfoSet[i]);
		}
	}
	OnOK();
	free(cview2);
}

BOOL RX_DIALOG::OnInitDialog(){
	SetDlgItemText(IDC_EDIT_RX_PZ_DES,"Untitled Rx");
	SetDlgItemText(IDC_EDIT__RX_PZ_Z,"5.0");

	return TRUE;
}