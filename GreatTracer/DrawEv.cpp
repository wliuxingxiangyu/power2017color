#include "StdAfx.h"
#include "DrawEv.h"
#include "deelx.h"
#include "String.h"
#include "LoadTexTure.h"
#include "resource.h"
#include "VIEWDLG.h"
#include "TIN.h"

CVIEWDLG cviewdlg;//CVIEWDLG类的实例化
int isRender=0;//是否渲染结果，全局变量CVIEWDLG

GLfloat DrawVertices[24];
GLint index_list[][4] = {
	0, 1, 2, 3,
	0, 4, 7, 3,
	0, 1, 5, 4,
	6, 7, 4, 5,
	6, 2, 3, 7,
	6, 2, 1, 5
};
DrawEv::DrawEv(void)
{
}
DrawEv::~DrawEv(void)
{
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////读取地图数据////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void DrawEv::ReadDxf(CString path){
	CStdioFile readDxfVertex;
	CString temp;
	if(!tempDxfVertex.IsEmpty())
		tempDxfVertex.RemoveAll();
	if(!DxfVertex.IsEmpty())
		DxfVertex.RemoveAll();
	if(!CityVertex.IsEmpty())
		CityVertex.RemoveAll();
	if(!tempCityVertex.IsEmpty())
		tempCityVertex.RemoveAll();
	if(!MultiVertexNum.IsEmpty())
		MultiVertexNum.RemoveAll();
	if(!MultiVertexPanel.IsEmpty())
		MultiVertexPanel.RemoveAll();
	readDxfVertex.Open(path,CFile::modeRead);
	while (readDxfVertex.ReadString(temp)){
		if (temp == "3DFACE"){
			for (int i = 0; i < 4; i++){
				readDxfVertex.ReadString(temp);
			}
			if (temp == "3DFACE"){
				CString strTem[24];
				for (int i = 0; i < 24; i++){             //每24行一读，将其存储到字符串数组,四个点，一个面
					readDxfVertex.ReadString(temp);
					strTem[i] = temp;
				}
				for (int j = 1; j <= 24; j++){
					tempDxfVertex.Add(strTem[j]);
					j++;
				}
			}
		}
	}
	//把string的数组转换成float的数组
	for(int i=0;i<tempDxfVertex.GetCount();i++){
		DxfVertex.Add((GLfloat)atof(tempDxfVertex[i]));
	}
	int n=DxfVertex.GetCount()/3;
	MapCenterX=0;
	MapCenterY=0;
	MapCenterZ=0;
	for(int i=0;i<n;i++){
		MapCenterX+=(GLfloat)DxfVertex[i*3]/n;
		MapCenterY+=(GLfloat)DxfVertex[i*3+1]/n;
		MapCenterZ+=(GLfloat)DxfVertex[i*3+2]/n;
	}

	for(int i=0;i<DxfVertex.GetCount();i+=3){
		DxfVertex[i]-=MapCenterX;
		DxfVertex[i+1]-=MapCenterY;
	}

	VertexSet.Copy(DxfVertex);

}
void DrawEv::ReadCity(CString path){
	CStdioFile cf;
	int a=0;
	char split=' ';
	CString temp,temp1;
	if(!tempDxfVertex.IsEmpty())
		tempDxfVertex.RemoveAll();
	if(!DxfVertex.IsEmpty())
		DxfVertex.RemoveAll();
	if(!CityVertex.IsEmpty())
		CityVertex.RemoveAll();
	if(!tempCityVertex.IsEmpty())
		tempCityVertex.RemoveAll();
	if(!MultiVertexNum.IsEmpty())
		MultiVertexNum.RemoveAll();
	if(!MultiVertexPanel.IsEmpty())
		MultiVertexPanel.RemoveAll();
	if(!PolygonVertex.IsEmpty())
		PolygonVertex.RemoveAll();
	if(!cf.Open(path,CFile::modeRead))
		MessageBox(NULL,"open failed!","tip",MB_OK);

	while(cf.ReadString(temp)){
		if(find_remark(temp)){
			if(4==GetVertexNum(temp)){
				for(int i=0;i<4;i++){
					cf.ReadString(temp);
					decodeCString(temp,tempCityVertex,split);
				}
			}
			else{
				int n=GetVertexNum(temp);
				MultiVertexNum.Add(n);
				for(int i=0;i<n;i++){
					cf.ReadString(temp);
					decodeCString(temp,MultiVertexPanel,split);
				}
			}
		}
	}
	for(int i=0;i<MultiVertexPanel.GetCount();i++){
		PolygonVertex.Add((GLfloat)atof(MultiVertexPanel[i]));
	}
	for(int i=0;i<tempCityVertex.GetCount();i++){
		CityVertex.Add((GLfloat)atof(tempCityVertex[i]));
	}

	//GLfloat tttt[1000];
	//for (int i = 0; i < CityVertex.GetCount(); i++)
	//{
	//	tttt[i] = CityVertex[i];
	//}

	//以下使地图坐标移动到原点，以便于轨迹球旋转和缩放时 地图始终处于视界中心

	int n=CityVertex.GetCount()/3;
	MapCenterX=0;
	MapCenterY=0;
	MapCenterZ=0;
	for(int i=0;i<n;i++){
		MapCenterX+=CityVertex[i*3]/n;
		MapCenterY+=CityVertex[i*3+1]/n;
		//MapCenterZ+=CityVertex[i*3+2]/n;
	}
	for(int i=0;i<n;i++){
		CityVertex[i*3]-=MapCenterX;
		CityVertex[i*3+1]-=MapCenterY;
		//CityVertex[i*3+2]-=MapCenterZ;
	}
	int m=PolygonVertex.GetCount()/3;

	for(int i=0;i<m;i++){
		PolygonVertex[i*3]-=MapCenterX;
		PolygonVertex[i*3+1]-=MapCenterY;
		//PolygonVertex[i*3+2]MapCenterZ;
	}

	//数据转存至VertexSet
	for (int i = 0; i <= CityVertex.GetCount() - 4; i += 4)
	{
		VertexSet.Add(CityVertex[i + 3]);
		VertexSet.Add(CityVertex[i + 2]);
		VertexSet.Add(CityVertex[i + 1]);
		VertexSet.Add(CityVertex[i]);
	}
}
int DrawEv::find_remark(CString str){
	// declare
	static CRegexpT <char> regexp("\\bnVertices\\b.*\\d+");
	// find and match
	MatchResult result = regexp.Match(str);
	// result
	if( result.IsMatched() ){
		return 1;
	}
	else
		return 0;
}
int DrawEv::GetVertexNum(CString str){
	CString temp;
	for(int i=9;i<str.GetLength();i++){
		temp+=str[i];
	}
	int re=atoi(temp);
	return re;
}
void DrawEv::decodeCString(CString source, CStringArray &CityVertex, char division)
{
	CString temp;
	int i=0;
	int j=0;
	for ( ;i<source.GetLength();i++){
		if(source[i]==division||i==source.GetLength()-1){
			for(;j<i;j++)
				temp+=source[j];
			CityVertex.Add(temp);
			temp="";
			continue;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
/////////////////////绘制地图/////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
GLfloat fVertices[12];//三维画图
GLfloat fVertices2D[8];//二维画图
void DrawEv::DrawCity(CString CityName,bool IsRender){

	LoadTexTure *LTT=NULL;//实例化贴图类
	LTT=new LoadTexTure();

	int Assi=0;
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glColor3f(0.64f,0.64f,0.64f);
	for( int i=0;i<MultiVertexNum.GetCount();i++){
		glBegin(GL_POLYGON);
		int a=( MultiVertexNum[i]+Assi)*3;
		for(int j=Assi*3;j<a;j+=3){
			glVertex3f( PolygonVertex[j], PolygonVertex[j+1], PolygonVertex[j+2]);
			Assi++;
		}
		glEnd();
	}
	Assi=0;
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glLineWidth(1.0f);
	glColor3f(0.64f,0.64f,0.64f);
	for( int i=0;i< MultiVertexNum.GetCount();i++){
		glBegin(GL_POLYGON);
		int a=( MultiVertexNum[i]+Assi)*3;
		for(int j=Assi*3;j<a;j+=3){
			glVertex3f( PolygonVertex[j],PolygonVertex[j+1] , PolygonVertex[j+2]);
			Assi++;
		}
		glEnd();
	}

	byte indices[4]={0,1,2,3};
	int n= CityVertex.GetCount()/3;
	for(int i=0;i<n;){
		for(int j=0;j<4;j++){
			fVertices[j*3]= CityVertex[i*3];
			fVertices[j*3+1]= CityVertex[i*3+1];
			fVertices[j*3+2]= CityVertex[i*3+2];
			i++;
		}
		glVertexPointer(3,GL_FLOAT,0,fVertices);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(1.0f,0.04f,0.8f);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indices);
		glPolygonMode(GL_FRONT,GL_FILL);
		glColor3f(0.64f,0.64f,0.64f);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indices);
	}
	if(CityName=="bupt.city"){
		LTT->DrawTextTure();
	}
	if(IsRender==TRUE)
		PowerRender(); 	

	free(LTT);
}

void DrawEv::DrawDxf(){
	byte indices[4];
	glLineWidth(1.0f);
	int n= DxfVertex.GetCount()/3;
	for(int i=0;i<n;){
		for(int j=0;j<4;j++){
			indices[j]=j;
			fVertices[j*3]= DxfVertex[i*3];
			fVertices[j*3+1]= DxfVertex[i*3+1];
			fVertices[j*3+2]= DxfVertex[i*3+2];
			i++;
		}
		glVertexPointer(3,GL_FLOAT,0,fVertices);
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		glColor3f(1.0f,0.04f,0.8f);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indices);
		glPolygonMode(GL_BACK,GL_FILL);
		glColor3f(0.64f,0.64f,0.64f);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indices);
	}
}

void DrawEv::DrawGround(){
	
	glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	glVertex3f(20000.0f,  20000.0f,-1.0f);
	glVertex3f(20000.0f, -20000.0f,-1.0f);
	glVertex3f(-20000.0f,-20000.0f,-1.0f);
	glVertex3f(-20000.0f, 20000.0f,-1.0f);
	glEnd();
}
//////////////////////////////////////////////////////////////////////////
////////////////////////////能量渲染//////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void DrawEv::PowerRender(){
	GLfloat coor=200.0f;
	glShadeModel(GL_SMOOTH);
	glBegin(GL_QUADS);
	glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)0);
	glVertex3f(-coor-100.0f,-coor,0.0f);
	glColor3ub((GLubyte)255,(GLubyte)0,(GLubyte)255);
	glVertex3f(-coor-100.0f,coor,0.0f);
	glColor3ub((GLubyte)0,(GLubyte)255,(GLubyte)0);
	glVertex3f(0.0f-100.0f,coor,0.0f);
	glColor3ub((GLubyte)0,(GLubyte)0,(GLubyte)255);
	glVertex3f(0.0f-100.0f,-coor,0.0f);
	glEnd();
}
void DrawEv::RenderOutput(){
	byte indices[4]={0,1,2,3};
	int i,j;

	//int ttttttt = RenderArray.GetCount();
	
	for(i=0;i<RenderArray.GetCount();i+=15){
		for(j=0;j<12;j++){
			fVertices[j]=RenderArray[i+j];
		}
		glVertexPointer(3,GL_FLOAT,0,fVertices);
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		
		//if(i == RenderArray.GetCount() - 15)
		//	ttttttt *= 1;
		
		glColor3f(RenderArray[i+j],RenderArray[i+j+1],RenderArray[i+j+2]);
		glDrawElements(GL_QUADS,4,GL_UNSIGNED_BYTE,indices);
		j=0;
	}		
}
/////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void DrawEv::DrawCube(){//绘制收发信机
	glPointSize(5);
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_POINTS);
		for(int i=0;i<TxInfoSet.GetCount();i++)
			glVertex3f(TxInfoSet[i].Pos.x,TxInfoSet[i].Pos.y,TxInfoSet[i].Pos.z);
		
	glEnd();
	glColor3f(0.0f,1.0f,0.0f);
	glBegin(GL_POINTS);
		if(1!=isRender){
			for(int i=0;i<RxInfoSet.GetCount();i++)
				glVertex3f(RxInfoSet[i].Pos.x,RxInfoSet[i].Pos.y,RxInfoSet[i].Pos.z);
		}
	glEnd();
}

void DrawEv::DrawPath(){
	//单发单收,单发多收去遍历函数

	glLineWidth(3.0f);

	//int cnt = DirectPath.GetCount();

	if(0!=DirectPath.GetCount()){
		glColor3f(1.0f,0.0f,0.0f);//直射
		for(int i=0;i<DirectPath.GetCount()/6;i++){
			glBegin(GL_LINES);
			glVertex3f(DirectPath[i*6],DirectPath[i*6+1],DirectPath[i*6+2]);
			glVertex3f(DirectPath[i*6+3],DirectPath[i*6+4],DirectPath[i*6+5]);
			glEnd();
		}
		glEnd();
	}
	if(0!=OneReflection.GetCount()){
		glColor3f(1.0f,0.4f,0.0f);//一介反射
		for(int i=0;i<OneReflection.GetCount()/9;i++){
			glBegin(GL_LINES);
			glVertex3f(OneReflection[i*9],OneReflection[i*9+1],OneReflection[i*9+2]);
			glVertex3f(OneReflection[i*9+3],OneReflection[i*9+4],OneReflection[i*9+5]);
			glVertex3f(OneReflection[i*9+3],OneReflection[i*9+4],OneReflection[i*9+5]);
			glVertex3f(OneReflection[i*9+6],OneReflection[i*9+7],OneReflection[i*9+8]);
			glEnd();
		}
	}
	if(0!=TwoReflection.GetCount()){
		glColor3f(0.65f,0.3f,0.8f);//二阶反射
		for(int i=0;i<TwoReflection.GetCount()/12;i++){
			glBegin(GL_LINES);
			glVertex3f(TwoReflection[i*12],TwoReflection[i*12+1],TwoReflection[i*12+2]);
			glVertex3f(TwoReflection[i*12+3],TwoReflection[i*12+4],TwoReflection[i*12+5]);
			glVertex3f(TwoReflection[i*12+3],TwoReflection[i*12+4],TwoReflection[i*12+5]);
			glVertex3f(TwoReflection[i*12+6],TwoReflection[i*12+7],TwoReflection[i*12+8]);
			glVertex3f(TwoReflection[i*12+6],TwoReflection[i*12+7],TwoReflection[i*12+8]);
			glVertex3f(TwoReflection[i*12+9],TwoReflection[i*12+10],TwoReflection[i*12+11]);
			glEnd();
		}
	}
	if(0!=OneDiffraction.GetCount()){
		glColor3f(1.0f,0.0f,0.5f);//一介绕射
		for(int i=0;i<OneDiffraction.GetCount()/9;i++){
			glBegin(GL_LINES);
			glVertex3f(OneDiffraction[i*9],OneDiffraction[i*9+1],OneDiffraction[i*9+2]);
			glVertex3f(OneDiffraction[i*9+3],OneDiffraction[i*9+4],OneDiffraction[i*9+5]);
			glVertex3f(OneDiffraction[i*9+3],OneDiffraction[i*9+4],OneDiffraction[i*9+5]);
			glVertex3f(OneDiffraction[i*9+6],OneDiffraction[i*9+7],OneDiffraction[i*9+8]);
			glEnd();
		}
	}
	if(0!=TwoDiffraction.GetCount()){
		glColor3f(0.5f,0.0f,0.25f);//二阶绕射
		for(int i=0;i<TwoDiffraction.GetCount()/12;i++){
			glBegin(GL_LINES);
			glVertex3f(TwoDiffraction[i*12],TwoDiffraction[i*12+1],TwoDiffraction[i*12+2]);
			glVertex3f(TwoDiffraction[i*12+3],TwoDiffraction[i*12+4],TwoDiffraction[i*12+5]);
			glVertex3f(TwoDiffraction[i*12+3],TwoDiffraction[i*12+4],TwoDiffraction[i*12+5]);
			glVertex3f(TwoDiffraction[i*12+6],TwoDiffraction[i*12+7],TwoDiffraction[i*12+8]);
			glVertex3f(TwoDiffraction[i*12+6],TwoDiffraction[i*12+7],TwoDiffraction[i*12+8]);
			glVertex3f(TwoDiffraction[i*12+9],TwoDiffraction[i*12+10],TwoDiffraction[i*12+11]);
			glEnd();
		}
	}
	if(0!=ReflectionToDiffraction.GetCount()){
		glColor3f(0.5f,0.5f,1.0f);//一反一绕
		for(int i=0;i<ReflectionToDiffraction.GetCount()/12;i++){
			glBegin(GL_LINES);
			glVertex3f(ReflectionToDiffraction[i*12],ReflectionToDiffraction[i*12+1],ReflectionToDiffraction[i*12+2]);
			glVertex3f(ReflectionToDiffraction[i*12+3],ReflectionToDiffraction[i*12+4],ReflectionToDiffraction[i*12+5]);
			glVertex3f(ReflectionToDiffraction[i*12+3],ReflectionToDiffraction[i*12+4],ReflectionToDiffraction[i*12+5]);
			glVertex3f(ReflectionToDiffraction[i*12+6],ReflectionToDiffraction[i*12+7],ReflectionToDiffraction[i*12+8]);
			glVertex3f(ReflectionToDiffraction[i*12+6],ReflectionToDiffraction[i*12+7],ReflectionToDiffraction[i*12+8]);
			glVertex3f(ReflectionToDiffraction[i*12+9],ReflectionToDiffraction[i*12+10],ReflectionToDiffraction[i*12+11]);
			glEnd();
		}
	}
	if(0!=DiffractionToReflection.GetCount()){
		glColor3f(0.5f,0.0f,0.0f);//一绕一反
		for(int i=0;i<DiffractionToReflection.GetCount()/12;i++){
			glBegin(GL_LINES);
			glVertex3f(DiffractionToReflection[i*12],DiffractionToReflection[i*12+1],DiffractionToReflection[i*12+2]);
			glVertex3f(DiffractionToReflection[i*12+3],DiffractionToReflection[i*12+4],DiffractionToReflection[i*12+5]);
			glVertex3f(DiffractionToReflection[i*12+3],DiffractionToReflection[i*12+4],DiffractionToReflection[i*12+5]);
			glVertex3f(DiffractionToReflection[i*12+6],DiffractionToReflection[i*12+7],DiffractionToReflection[i*12+8]);
			glVertex3f(DiffractionToReflection[i*12+6],DiffractionToReflection[i*12+7],DiffractionToReflection[i*12+8]);
			glVertex3f(DiffractionToReflection[i*12+9],DiffractionToReflection[i*12+10],DiffractionToReflection[i*12+11]);
			glEnd();
		}
	}
}

void DrawEv::DrawTinPoint(){
	if(T1.GetCount()!=0){
		glPointSize(5);
		glColor3f(0.9f,0.1f,0.8f);
		glBegin(GL_POINTS);
		glEnable(GL_POINT_SMOOTH);
		for(int i=0;i<T1.GetCount();i++)
			glVertex3f(T1[i].x,T1[i].y,T1[i].z);
		glEnd();
	}
}
void DrawEv::DrawTIN(){
	if(T3.GetCount()!=0){
		glColor3f(0.0f,1.0f,0.0f);
		glLineWidth(1.5f);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		for(int i=0;i<T3.GetCount();i++){
			glBegin(GL_LINE_LOOP);
			glVertex3f(T3[i].P1.x,T3[i].P1.y,T3[i].P1.z);
			glVertex3f(T3[i].P2.x,T3[i].P2.y,T3[i].P2.z);
			glVertex3f(T3[i].P3.x,T3[i].P3.y,T3[i].P3.z);
			glEnd();
		}
	}
}

void DrawEv::DrawRect(){//绘制圈定多发射机或多接收机的虚线框
	if(SetPointOnTin==1&&GLBoundaryPoint.GetCount()==1){
		glColor3f(0.0f,0.0f,1.0f);
		glPointSize(10);
		glBegin(GL_POINTS);
			glVertex3f((GLfloat)GLBoundaryPoint[0].x,(GLfloat)GLBoundaryPoint[0].y,(GLfloat)GLBoundaryPoint[0].z+0.2);
			glVertex3f((GLfloat)ResultPos.x,(GLfloat)ResultPos.y,(GLfloat)ResultPos.z+0.2);
		glEnd();

		glColor3f(0.5,0.5,0.5);
		glLineWidth(1.0f);
		glBegin(GL_LINE_LOOP);
			glVertex3f((GLfloat)GLBoundaryPoint[0].x,(GLfloat)GLBoundaryPoint[0].y,100.0);
			glVertex3f((GLfloat)ResultPos.x,(GLfloat)GLBoundaryPoint[0].y,100.0);
			glVertex3f((GLfloat)ResultPos.x,(GLfloat)ResultPos.y,(GLfloat)ResultPos.z);
			glVertex3f((GLfloat)GLBoundaryPoint[0].x,(GLfloat)ResultPos.y,100.0);
			glVertex3f((GLfloat)GLBoundaryPoint[0].x,(GLfloat)GLBoundaryPoint[0].y,100.0);
		glEnd();
	}

}

void DrawEv::DrawCricle(GLfloat xc,GLfloat yc,GLfloat radius,int n,GLfloat rotAngle){
	GLfloat x,y,x0,y0;
	GLfloat angle=rotAngle*3.14159265/180;
	GLfloat angleInc=2*3.14159265/n;
	x0=radius*cos(angle)+xc;
	y0=radius*sin(angle)+yc;
	glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
		for(int i=0;i<n;i++){
			angle+=angleInc;
			x=radius*cos(angle)+xc;
			y=radius*sin(angle)+yc;
			glVertex3f(x0,y0,-1);
			glVertex3f(x,y,-1);
			x0=x;
			y0=y;
		}
	glEnd();
}

void DrawEv::DrawRange(CArray <CurPos3D> &range){
	int n=range.GetCount();
	glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(3.0f);
	glBegin(GL_LINES);
	for(int i=0;i<n-1;i++){
			glVertex3f(range[i].x,range[i].y,range[i].z);
			glVertex3f(range[i+1].x,range[i+1].y,range[i+1].z);
			
		}
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(range[n-1].x,range[n-1].y,range[n-1].z);
		glVertex3f(range[0].x,range[0].y,range[0].z);
	glEnd();
}