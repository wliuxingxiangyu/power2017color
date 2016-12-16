#include "StdAfx.h"
#include "TIN.h"


TIN::TIN(void)
{
}

TIN::~TIN(void)
{
}

void TIN::OnTin(){
	int num=T1.GetCount();
	for(int i=0;i<num-1;i++){
		for(int j=i+1;j<num;j++){
			if(T1[i].x>T1[j].x){
				CurPos3D p1;
				p1=T1[i];
				T1[i]=T1[j];
				T1[j]=p1;
			}
		}
	}
	if(num>2){
		if(T1[0].y>T1[1].y)       //  ȷ�����ߺ���ұ߿�ʼ�ҵ�
			this->M_TIN(T1[0],T1[1]);
		else
			this->M_TIN(T1[1],T1[0]);
	}
	else
		MessageBox(NULL,"����������������","tips",MB_OK);
}
void TIN::M_TIN(CurPos3D p1,CurPos3D p2){
	CurPos3D p3,p4;
	p3=GetThirdPoint(p1,p2);
	if(p3.x!=0.00 && p3.y!=0.00){
		p4=p3;
		//this->GetTriangle(p1,p2,p4);
		//////////�洢��////////////
		line l1;
		l1.P1=p1;
		l1.P2=p2;

		T2.Add(l1);
		//////////////�洢������//////////////////
		Triangle triangles;
		triangles.P1=p1;
		triangles.P2=p2;
		triangles.P3=p4;

		T3.Add(triangles);
	}
	else return;
	M_TIN(p1,p4);
	M_TIN(p4,p2);
}

CurPos3D TIN::GetThirdPoint(CurPos3D p1,CurPos3D p2){
	bool t=this->IsLine(p1,p2);
	int j=0;double temp=1.0;
	
	for(int i=0;i<T1.GetCount();i++){
		double equation;
		equation=((p1.y-p2.y)*(T1[i].x-p2.x))-((T1[i].y-p2.y )*(p1.x-p2.x));//�б���ڻ��ߵ���໹���Ҳ๫ʽ
		if ( equation<=0) continue;     //�����ڻ��ߵ������ȥ
		double a=sqrt(pow((double)p1.x-T1[i].x,2)+pow((double)p1.y-T1[i].y,2));
		double b=sqrt(pow((double)p2.x-T1[i].x,2)+pow((double)p2.y-T1[i].y,2));
		double c=sqrt(pow((double)p1.x-p2.x,2)+pow((double)p1.y-p2.y,2));
		double d=(a*a+b*b-c*c)/(2*a*b);
		if(d<temp && equation>0 && t){   //ȡ����ֵ��С���Ž����ԭ��
			temp=d;      
			j=i;
		}  
	}
	if(j!=0){
		return T1[j];
	}
	else{
		CurPos3D returntemp;
		returntemp.x=0.0f;
		returntemp.y=0.0f;
		returntemp.z=0.0f;
		return returntemp;
	}
}
bool TIN::IsLine(CurPos3D p1,CurPos3D p2){
	bool p=true; //û����ֱ��
	line templine;
	templine.P1.x=p1.x;templine.P1.y=p1.y;templine.P1.z=p1.z;
	templine.P2.x=p2.x;templine.P2.y=p2.y;templine.P2.z=p2.z;
	for(int i=0;i<T2.GetCount();i++){
		if(templine.P1.x==T2[i].P1.x&&templine.P1.y==T2[i].P1.y&&templine.P1.z==T2[i].P1.z && templine.P2.x==T2[i].P2.x&&templine.P2.y==T2[i].P2.y&&templine.P2.z==T2[i].P2.z )//����ֱ��
			p=false;
	}
	return p;
}
BOOL TIN::CalculateNormal(){
	GLdouble dVector1[3],dVector2[3],norm[3];
	for (int  i=0; i<T3.GetCount(); i++){
		/////////////////////////////////////////////////////////////////////////////////////////////
		dVector1[0] = T3[i].P2.x - T3[i].P1.x;
		dVector1[1] = T3[i].P2.y - T3[i].P1.y;
		dVector1[2] = T3[i].P2.z - T3[i].P1.z;

		dVector2[0] = T3[i].P3.x - T3[i].P1.x;
		dVector2[1] = T3[i].P3.y - T3[i].P1.y;
		dVector2[2] = T3[i].P3.z - T3[i].P1.z;
		//////////////////////////////////////////////////////////////////////////////////////////////
		norm[0]=dVector1[1]*dVector2[2]-dVector1[2]*dVector2[1];
		norm[1]=dVector1[2]*dVector2[0]-dVector1[0]*dVector2[2];
		norm[2]=dVector1[0]*dVector2[1]-dVector1[1]*dVector2[0];

		double dnormalLength=sqrt(norm[0]*norm[0] + norm[1]*norm[1] + norm[2]*norm[2]);

		if(dnormalLength!=0.0){
			T3[i].normal[0]=(GLfloat)(norm[0]/dnormalLength);
			T3[i].normal[1]=(GLfloat)(norm[1]/dnormalLength);
			T3[i].normal[2]=(GLfloat)(norm[2]/dnormalLength);
		}
		else
		{
			T3[i].normal[0]=0;
			T3[i].normal[0]=0;
			T3[i].normal[0]=0;
		}
	}
	return 0;
}

BOOL TIN::SetTextTure(){

	//����bmpͼ���ļ�������
	AUX_RGBImageRec *Image=auxDIBImageLoad("..\\GreatTracer\\2.bmp");
	/*  �������� */
	glTexImage2D(GL_TEXTURE_2D, 0, 3, Image->sizeX,Image->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE,Image->data);
	/*  �����˲� */
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);  
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glClearColor(1.0,1.0,1.0,1.0);

	/*  ˵��ӳ�䷽ʽ*/
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE,GL_DECAL);    //�ڴ˴��ɸ���ӳ��ģʽ��ѡ��GL_DECAL��GL_MODULATE��GL_BLEND

	/*  ��������ӳ�� */
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_FLAT);   //����GL_SMOOTH��GL_FLAT

	/*  ����������������弸������ */
	//glRotatef(m_Rotateangle, 1, 1, 1);
	//��������Ķ�������ʾЧ������ͼλ�����£�������ͼ�α����Ǻ�
	glEnable(GL_CULL_FACE);
	glBegin(GL_TRIANGLES);
	for (int i=0; i<T3.GetCount(); i++){
		glTexCoord2f(0.0, 0.0); 
		glVertex3f(T3[i].P1.x, T3[i].P1.y, T3[i].P1.z);
		glTexCoord2f(0.0, 1.0); 
		glVertex3f(T3[i].P2.x, T3[i].P2.y, T3[i].P2.z);
		glTexCoord2f(1.0, 1.0);
		glVertex3f(T3[i].P3.x, T3[i].P3.y, T3[i].P3.z);

	}
	glEnd();
	glDisable(GL_TEXTURE_2D);
	return 0;
}