#include "StdAfx.h"
#include "ReadandWrite.h"

ReadandWrite::ReadandWrite(void)
{
}

ReadandWrite::~ReadandWrite(void)
{
}

int ReadandWrite::ReadPointofTIN(){
	if(T1.GetCount()!=0)
		T1.RemoveAll();
	CString path,temp;
	CStdioFile CSF;
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,".txt|*.txt|all files(*.*)|*.*");
	if(dlg.DoModal()==IDOK){
		path=dlg.GetPathName();
		if(!CSF.Open(path,CFile::modeRead)){
			MessageBox(NULL,"cannot open file!","tips",MB_OK);
			return 0;
		}
		else{
			while(CSF.ReadString(temp)){
				DealString(temp);
			}
		}
	}
	MapCenterX=0;MapCenterY=0;MapCenterZ=0;
	int n=T1.GetCount();
	for(int i=0;i<n;i++){//计算TIN的中心点
		MapCenterX+=(GLfloat)T1[i].x/n;
		MapCenterY+=(GLfloat)T1[i].y/n;
		MapCenterZ+=(GLfloat)T1[i].z/n;
	}

	for(int i=0;i<n;i++){
		T1[i].x-=MapCenterX;
		T1[i].y-=MapCenterY;
		T1[i].z-=MapCenterZ;
	}

	return 0;
}
void ReadandWrite::DealString(CString temp){
	int symbolflag=0;
	CurPos3D tempPoint;
	CString tempx,tempy,tempz;
	for(int i=0;i<temp.GetLength();i++){
		if(0==symbolflag&&temp[i]!=' '&&temp[i]!=','&&temp[i]!='	')
			tempx+=temp[i];
		if(1==symbolflag&&temp[i]!=' '&&temp[i]!=','&&temp[i]!='	')
			tempy+=temp[i];
		if(2==symbolflag)
			tempz+=temp[i];
		else if(temp[i]==' '||temp[i]==','||temp[i]=='	'){
			symbolflag+=1;
		}
	}
	tempPoint.x=(GLfloat)atof(tempx);
	tempPoint.y=(GLfloat)atof(tempy);
	tempPoint.z=(GLfloat)atof(tempz);

	T1.Add(tempPoint);

}