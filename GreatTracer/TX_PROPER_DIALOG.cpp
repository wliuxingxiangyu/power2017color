// TX_PROPER_DIALOG.cpp : 实现文件
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "TX_PROPER_DIALOG.h"


CVIEWDLG *cview3;


IMPLEMENT_DYNAMIC(TX_PROPER_DIALOG, CDialog)

TX_PROPER_DIALOG::TX_PROPER_DIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(TX_PROPER_DIALOG::IDD, pParent)
{

}

TX_PROPER_DIALOG::~TX_PROPER_DIALOG()
{
}

void TX_PROPER_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_ANTE, m_Ante_Combo);
	//DDX_Control(pDX, IDC_WAVEFORM, m_Wave_Combo);
}


BEGIN_MESSAGE_MAP(TX_PROPER_DIALOG, CDialog)
	//ON_BN_CLICKED(IDOK, &TX_PROPER_DIALOG::OnBnClickedOk)
	ON_BN_CLICKED(IDOK, &TX_PROPER_DIALOG::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL TX_PROPER_DIALOG::OnInitDialog(){
	SetDlgItemText(IDC_EDIT_DESCRIPTION,"Untitled Tx");
	SetDlgItemText(IDC_EDIT_TX_HEIGHT,"10.0");
	SetDlgItemText(IDC_EDIT_CARRIERFRE,"1");
	SetDlgItemText(IDC_EDIT_INPUTPOWER,"60");
	SetDlgItemText(IDC_EDIT_ANTE,"0");
	SetDlgItemText(IDC_EDIT_WAVEFORM,"1");
	SetDlgItemText(IDC_EDIT_LAT,"40");
	SetDlgItemText(IDC_EDIT_ANGLE,"20");
	SetDlgItemText(IDC_EDIT_ALLOWLOSS,"2000");
	SetDlgItemText(IDC_EDIT_TIME,"1");
	return TRUE;
}

// TX_PROPER_DIALOG 消息处理程序


void TX_PROPER_DIALOG::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	cview3->AddEle();
	int a =TxInfoSet.GetCount();
	CString temp;
	int n=TxInfoSet.GetCount();
	for(int i=0;i<TxInfoSet.GetCount();i++){

		GetDlgItemText(IDC_EDIT_DESCRIPTION,temp);
		TxInfoSet[i].Description=temp;

		if(TxInfoSet[i].Pos.z<0){
			GetDlgItemText(IDC_EDIT_TX_HEIGHT,temp);
			TxInfoSet[i].Pos.z=(GLfloat)atof(temp);
			cview3->Deal_Tx_Vertex_Cube(TxInfoSet[i]);
		}
		if(TxInfoSet[i].CarrierFrequency<0){
			GetDlgItemText(IDC_EDIT_CARRIERFRE,temp);
			TxInfoSet[i].CarrierFrequency=(GLfloat)atof(temp);//单位是G
		}
		if(TxInfoSet[i].InputPower<0){
			GetDlgItemText(IDC_EDIT_INPUTPOWER,temp);
			TxInfoSet[i].InputPower=(GLfloat)atof(temp);
		}
		if(TxInfoSet[i].AntennaType<0){
			GetDlgItemText(IDC_EDIT_ANTE,temp);
			TxInfoSet[i].AntennaType=atoi(temp);
		}
		if(TxInfoSet[i].WaveForm<0){
			GetDlgItemText(IDC_EDIT_WAVEFORM,temp);
			TxInfoSet[i].WaveForm=atoi(temp);
		}
		if(TxInfoSet[i].Lat<0){
			GetDlgItemText(IDC_EDIT_LAT,temp);
			TxInfoSet[i].Lat=atoi(temp);
		}
		if(TxInfoSet[i].Angle<0){
			GetDlgItemText(IDC_EDIT_ANGLE,temp);
			TxInfoSet[i].Angle=atoi(temp);
		}
		if(TxInfoSet[i].AllowLoss<0){
			GetDlgItemText(IDC_EDIT_ALLOWLOSS,temp);
			TxInfoSet[i].AllowLoss=atoi(temp);
		}
		if(TxInfoSet[i].Time<0){
			GetDlgItemText(IDC_EDIT_TIME,temp);
			TxInfoSet[i].Time=atoi(temp);
		}
	}
	OnOK();
	free(cview3);
}

int TX_PROPER_DIALOG::TestPara(int b){
	int a=1;
	return b+a;
}