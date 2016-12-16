// ANTE_DIALOG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "ANTE_DIALOG.h"
#include "VIEWDLG.h"


// ANTE_DIALOG �Ի���

IMPLEMENT_DYNAMIC(ANTE_DIALOG, CDialog)

ANTE_DIALOG::ANTE_DIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(ANTE_DIALOG::IDD, pParent)
{

}

ANTE_DIALOG::~ANTE_DIALOG()
{
}

void ANTE_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(ANTE_DIALOG, CDialog)
	ON_BN_CLICKED(IDOK, &ANTE_DIALOG::OnBnClickedOk)
END_MESSAGE_MAP()


// ANTE_DIALOG ��Ϣ�������

void ANTE_DIALOG::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CVIEWDLG *cview1;
	cview1=new CVIEWDLG();

	AntennaInfo anteExam;
	CString temp;
	GetDlgItemText(IDC_STARTANGLE_EDIT,temp);
	anteExam.StartRad=(GLfloat)(atof(temp)*3.14159/180);
	GetDlgItemText(IDC_ENDANGLE_EDIT,temp);
	anteExam.EndRad=(GLfloat)(atof(temp)*3.14159/180);
	GetDlgItemText(IDC_ANTEGAIN_EDIT,temp);
	anteExam.PowerGain=(GLfloat)atof(temp);

	AnteInfo.Add(anteExam);

	free(cview1);
	OnOK();
}
BOOL ANTE_DIALOG::OnInitDialog(){
	SetDlgItemText(IDC_STARTANGLE_EDIT,"0.0");
	SetDlgItemText(IDC_ENDANGLE_EDIT,"0.0");
	SetDlgItemText(IDC_ANTEGAIN_EDIT,"0.0");
	return 0;
}
