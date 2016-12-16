// POLYGON_TX_DIALOG.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GreatTracer.h"
#include "POLYGON_TX_DIALOG.h"

CVIEWDLG *cviewdlg1;

// POLYGON_TX_DIALOG �Ի���

IMPLEMENT_DYNAMIC(POLYGON_TX_DIALOG, CDialog)

POLYGON_TX_DIALOG::POLYGON_TX_DIALOG(CWnd* pParent /*=NULL*/)
	: CDialog(POLYGON_TX_DIALOG::IDD, pParent)
{
}

POLYGON_TX_DIALOG::~POLYGON_TX_DIALOG()
{
}

void POLYGON_TX_DIALOG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(POLYGON_TX_DIALOG, CDialog)
	ON_BN_CLICKED(IDOK, &POLYGON_TX_DIALOG::OnBnClickedOk)
END_MESSAGE_MAP()


// POLYGON_TX_DIALOG ��Ϣ�������
BOOL POLYGON_TX_DIALOG::OnInitDialog(){
	if(SetPointOnTin==1){
		GetDlgItem(IDC_POLYGON_HEIGHT_EDIT)->EnableWindow(FALSE);//���ø߶ȱ༭��
		GetDlgItem(IDC_POLYGON_length_EDIT)->EnableWindow(FALSE);//����
		GetDlgItem(IDC_POLYGON_WIDTH_EDIT)->EnableWindow(FALSE);//����
	}
	SetDlgItemText(IDC_POLYGON_length_EDIT,"100.0");
	SetDlgItemText(IDC_POLYGON_WIDTH_EDIT,"100.0");
	SetDlgItemText(IDC_POLYGON_HEIGHT_EDIT,"10.0");
	SetDlgItemText(IDC_POLYGON_SPACE_EDIT,"0.0");
	SetDlgItemText(IDC_POLYGON_POWER_EDIT,"0.0");
	SetDlgItemText(IDC_POLYGON_CARRIERFRE_EDIT,"1");
	SetDlgItemText(IDC_POLYGON_ANTE_EDIT,"1");
	SetDlgItemText(IDC_POLYGON_WAVEFORM_EDIT,"0");
	return 0;
}
void POLYGON_TX_DIALOG::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString temp;
	GLfloat length,width,height,space,power,carrierfrequencies;
	int ante,waveform;
	if(SetPointOnTin!=1){//������Tin�����շ��Ż�ʱ��Enable �߶� ��� ���ȿ�
		GetDlgItemText(IDC_POLYGON_length_EDIT,temp);
		length=(GLfloat)atof(temp);
		GetDlgItemText(IDC_POLYGON_WIDTH_EDIT,temp);
		width=(GLfloat)atof(temp);
		GetDlgItemText(IDC_POLYGON_HEIGHT_EDIT,temp);
		height=(GLfloat)atof(temp);
	}
	GetDlgItemText(IDC_POLYGON_SPACE_EDIT,temp);
	space=(GLfloat)atof(temp);
	GetDlgItemText(IDC_POLYGON_POWER_EDIT,temp);
	power=(GLfloat)atof(temp);
	GetDlgItemText(IDC_POLYGON_CARRIERFRE_EDIT,temp);
	carrierfrequencies=(GLfloat)atof(temp);//��λ��G
	GetDlgItemText(IDC_POLYGON_ANTE_EDIT,temp);
	ante=atoi(temp);
	GetDlgItemText(IDC_POLYGON_WAVEFORM_EDIT,temp);
	waveform=atoi(temp);
	
	if(SetPointOnTin==0){
		GLfloat minX,minY;
		long capacity=TxInfoSet.GetCount();
		minX=TxInfoSet[capacity-1].Pos.x-length/2;
		minY=TxInfoSet[capacity-1].Pos.y-width/2;

		GLfloat startX,startY,maxX,maxY;
		maxX = TxInfoSet[capacity - 1].Pos.x + length / 2;
		maxY = TxInfoSet[capacity - 1].Pos.y + width / 2;
		startX = minX + (length - space * (int)(length / space)) / 2;
		startY = minY + (width - space * (int)(width / space)) / 2;

		TxInfoSet.RemoveAll();
		TxInfoSet.FreeExtra();

		TxInfo tempTxPoint;

		if (length/space<1||width/space<1){
			MessageBox("���õľ��η�Χ��С�����߷�����������޷����÷����","Tips",MB_OK);
			return;
		}

		if(space<1){
			MessageBox("δ���÷�������������ļ����С�����������ã�","Tips",MB_OK);
			return;
		}

		for(int i = 0; startX + i * space <= maxX; i++){
			for(int j = 0; startY + j * space <= maxY; j++){
				tempTxPoint.Pos.x = startX + i * space;
				tempTxPoint.Pos.y = startY + j * space;
				tempTxPoint.Pos.z = height;
				tempTxPoint.CarrierFrequency = carrierfrequencies;
				tempTxPoint.AntennaType = ante;
				tempTxPoint.InputPower = power;
				tempTxPoint.WaveForm = waveform;
				TxInfoSet.Add(tempTxPoint);
			}			
		}

		//for(int i=0;i<length/space;i++){
		//	for(int j=0;j<width/space;j++){
		//		tempTxPoint.Pos.x=minX+i*space;
		//		tempTxPoint.Pos.y=minY+j*space;
		//		tempTxPoint.Pos.z=height;
		//		tempTxPoint.CarrierFrequency=carrierfrequencies;
		//		tempTxPoint.AntennaType=ante;
		//		tempTxPoint.InputPower=power;
		//		tempTxPoint.WaveForm=waveform;
		//		TxInfoSet.Add(tempTxPoint);
		//	}
		//}
	}

	else if(SetPointOnTin==1){
		if(ScrBoundaryPoint.GetCount()==2&&GLBoundaryPoint.GetCount()==2){

			TxInfo tempTxPoint;

			length=(GLfloat)(GLBoundaryPoint[0].x-GLBoundaryPoint[1].x);
			width=(GLfloat)(GLBoundaryPoint[0].y-GLBoundaryPoint[1].y);
			if (length<0)
				length*=-1;
			if(width<0)
				width*=-1;

			int m,n;//m�ǳ����Ϸ�����ĸ�����n�ǿ��Ϸ�����ĸ���
			m=(int) (length/space);n=(int)(width/space);

			if(m<1||n<1){
				MessageBox("���õľ��η�Χ��С�����߷�����������޷����÷����","Tips",MB_OK);
				return;
			}

			GLfloat scr_space_x,scr_space_y;//��������Ļ�ϵļ��
			scr_space_x=(GLfloat)((ScrBoundaryPoint[0].x-ScrBoundaryPoint[1].x)/m);
			scr_space_y=(GLfloat)((ScrBoundaryPoint[0].y-ScrBoundaryPoint[1].y)/n);

			if(scr_space_x>0){//��һ�����ڵڶ����������
				if(scr_space_y>0){//��һ�����ڵڶ����������
					for(int i=0;i<m;i++){
						for(int j=0;j<n;j++){
							cviewdlg1->GetCoor_TIN(ScrBoundaryPoint[0].x-i*scr_space_x,ScrBoundaryPoint[0].y-j*scr_space_y);
							tempTxPoint.Pos.x=(GLfloat)ResultPos.x;tempTxPoint.Pos.y=(GLfloat)ResultPos.y;tempTxPoint.Pos.z=(GLfloat)ResultPos.z+0.2;
							tempTxPoint.CarrierFrequency=carrierfrequencies;
							tempTxPoint.AntennaType=ante;
							tempTxPoint.InputPower=power;
							tempTxPoint.WaveForm=waveform;
							TxInfoSet.Add(tempTxPoint);
						}
					}

					//��ɼ��㣬��ձ߽��ͱ߽��־
					ScrBoundaryPoint.RemoveAll();
					GLBoundaryPoint.RemoveAll();
					//SetPointOnTin=0;
					BoundaryFlag=0;
				}
				if(scr_space_y<0){//��һ�����ڵڶ����������
					for(int i=0;i<m;i++){
						for(int j=0;j<n;j++){
							cviewdlg1->GetCoor_TIN(ScrBoundaryPoint[0].x-i*scr_space_x,ScrBoundaryPoint[0].y-j*scr_space_y);
							tempTxPoint.Pos.x=(GLfloat)ResultPos.x;tempTxPoint.Pos.y=(GLfloat)ResultPos.y;tempTxPoint.Pos.z=(GLfloat)ResultPos.z+0.2;
							//tempTxPoint.Pos.x=ResultPos.x;tempTxPoint.Pos.y=ResultPos.y;tempTxPoint.Pos.z=ResultPos.z;
							tempTxPoint.CarrierFrequency=carrierfrequencies;
							tempTxPoint.AntennaType=ante;
							tempTxPoint.InputPower=power;
							tempTxPoint.WaveForm=waveform;
							TxInfoSet.Add(tempTxPoint);
						}
					}
					//��ɼ��㣬��ձ߽��ͱ߽��־
					ScrBoundaryPoint.RemoveAll();
					GLBoundaryPoint.RemoveAll();
					//SetPointOnTin=0;
					BoundaryFlag=0;
				}
			}
			
			if(scr_space_x<0){//��һ�����ڵڶ����������
				if(scr_space_y>0){//��һ�����ڵڶ����������
					for(int i=0;i<m;i++){
						for(int j=0;j<n;j++){
							cviewdlg1->GetCoor_TIN(ScrBoundaryPoint[0].x-i*scr_space_x,ScrBoundaryPoint[0].y-j*scr_space_y);
							tempTxPoint.Pos.x=(GLfloat)ResultPos.x;tempTxPoint.Pos.y=(GLfloat)ResultPos.y;tempTxPoint.Pos.z=(GLfloat)ResultPos.z+0.2;
							//tempTxPoint.Pos.x=ResultPos.x;tempTxPoint.Pos.y=ResultPos.y;tempTxPoint.Pos.z=ResultPos.z;
							tempTxPoint.CarrierFrequency=carrierfrequencies;
							tempTxPoint.AntennaType=ante;
							tempTxPoint.InputPower=power;
							tempTxPoint.WaveForm=waveform;
							TxInfoSet.Add(tempTxPoint);
						}
					}
					//��ɼ��㣬��ձ߽��ͱ߽��־
					ScrBoundaryPoint.RemoveAll();
					GLBoundaryPoint.RemoveAll();
					//SetPointOnTin=0;
					BoundaryFlag=0;
				}
				if(scr_space_y<0){//��һ�����ڵڶ����������
					for(int i=0;i<m;i++){
						for(int j=0;j<n;j++){
							cviewdlg1->GetCoor_TIN(ScrBoundaryPoint[0].x-i*scr_space_x,ScrBoundaryPoint[0].y-j*scr_space_y);
							tempTxPoint.Pos.x=(GLfloat)ResultPos.x;tempTxPoint.Pos.y=(GLfloat)ResultPos.y;tempTxPoint.Pos.z=(GLfloat)ResultPos.z+0.2;
							//tempTxPoint.Pos.x=ResultPos.x;tempTxPoint.Pos.y=ResultPos.y;tempTxPoint.Pos.z=ResultPos.z;
							tempTxPoint.CarrierFrequency=carrierfrequencies;
							tempTxPoint.AntennaType=ante;
							tempTxPoint.InputPower=power;
							tempTxPoint.WaveForm=waveform;
							TxInfoSet.Add(tempTxPoint);
						}
					}
					//��ɼ��㣬��ձ߽��ͱ߽��־
					ScrBoundaryPoint.RemoveAll();
					GLBoundaryPoint.RemoveAll();
					//SetPointOnTin=0;
					BoundaryFlag=0;
				}
			}
		}
		else
			MessageBox("��ѡ��bug����ϵ������Ա��","Tips",MB_OK);
	}
	OnOK();
	free(cviewdlg1);
}
