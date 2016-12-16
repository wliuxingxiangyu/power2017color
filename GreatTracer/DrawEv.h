#pragma once

#include "stdafx.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"
#include "deelx.h"
#include "ScaleVariable.h"
#include "VIEWDLG.h"

extern CArray <RxInfo> RxInfoSet;//接收机集合
extern CArray <TxInfo> TxInfoSet;//发射机集合

extern CArray <AntennaInfo> AnteInfo;//天线数组
extern CArray <ModualInfo> ModualWay;//调试方式数组

extern CArray <CurPos3D> T1;
extern CArray<line> T2;
extern CArray<Triangle> T3;

extern CArray <GLfloat> CubeVertex_Tx;//收发信机的小立方体坐标
extern CArray <GLfloat> CubeVertex_Rx;
extern CArray <GLfloat> RenderArray;//存放渲染信息的数组

extern CArray <GLfloat> DirectPath; //直射路径
extern CArray <GLfloat> OneReflection;//一阶反射
extern CArray <GLfloat> TwoReflection;//二阶反射
extern CArray <GLfloat> OneDiffraction;//一阶绕射
extern CArray <GLfloat> TwoDiffraction;//二阶绕射
extern CArray <GLfloat> ReflectionToDiffraction;//一反一绕
extern CArray <GLfloat> DiffractionToReflection;//一绕一反
extern CArray <GLfloat> TwoReflectionToDiffraction;//两反一绕
extern CArray <GLfloat> ReflectionToTwoDiffraction;//一反两绕
extern CArray <GLfloat> TwoDiffractionToReflection;//两绕一反
extern CArray <GLfloat> DiffractionToTwoReflection;//一绕两反
extern CArray <GLfloat> TwoReflectionToTwoDiffraction;//两绕两反

extern GLfloat MapCenterX,MapCenterY,MapCenterZ;

extern CArray <Vec3T> GLBoundaryPoint;
extern int BoundaryFlag;
extern int SetPointOnTin;
extern Vec3T ResultPos;

class DrawEv
{
public:
	DrawEv(void);//构造函数
	~DrawEv(void);
	//读取dxf和city文件
	void ReadDxf(CString path);
	void ReadCity(CString path);
	//绘制dxf和city地图
	void DrawDxf();
	void DrawCity(CString CityName,bool IsRender);

	void DrawGround();	//绘制地面
	void DrawCube();	//绘制收发信机
	void DrawPath();	//绘制射线路径
	void PowerRender();//能量渲染样式，仅演示用
	
	void RenderOutput();	//渲染结果
	void DrawTinPoint();//画TIN的点
	void DrawTIN();//画三角形
private:
	CStringArray tempCityVertex;//.city地图顶点的临时存放数组
	CStringArray  tempDxfVertex;//.dxf地图定点的临时存放数组
	CStringArray MultiVertexPanel;//3DFACE多边形的顶点的存放数组
	int find_remark(CString str);//匹配查询
	int GetVertexNum(CString str);//获取多边形顶点个数
	void decodeCString(CString source,CStringArray &CityVertex,char division);//将顶点数据写入数组
public:

	CArray <GLfloat> VertexSet; //用于存储处理后的地图信息的点集

	CArray <GLfloat> CityVertex;//*.city地图中的四边形顶点坐标
	CArray <GLfloat> DxfVertex;//3DFACE的顶点坐标数
	CArray <INT32> MultiVertexNum;//多边形的顶点数
	CArray <GLfloat> PolygonVertex;//多边形的顶点坐标
	GLuint	texture[1];		// 纹理贴图数组
	void DrawRect();
	void DrawCricle(GLfloat xc,GLfloat yc,GLfloat radius,int n,GLfloat rotAngle);//画圆
	void DrawRange(CArray <CurPos3D> &range);//画边界

};
