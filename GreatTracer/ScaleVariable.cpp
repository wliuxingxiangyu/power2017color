#include "StdAfx.h"
#include "ScaleVariable.h"

CArray <GLfloat> CubeVertex_Tx;//收发信机的小立方体坐标
CArray <GLfloat> CubeVertex_Rx;

CArray <GLfloat> RenderArray;//存放渲染信息的数组

CArray <GLfloat> DirectPath; //直射路径
CArray <GLfloat> OneReflection;//一阶反射
CArray <GLfloat> TwoReflection;//二阶反射
CArray <GLfloat> OneDiffraction;//一阶绕射
CArray <GLfloat> TwoDiffraction;//二阶绕射
CArray <GLfloat> ReflectionToDiffraction;//一反一绕
CArray <GLfloat> DiffractionToReflection;//一绕一反
CArray <GLfloat> TwoReflectionToDiffraction;//两反一绕
CArray <GLfloat> ReflectionToTwoDiffraction;//一反两绕
CArray <GLfloat> TwoDiffractionToReflection;//两绕一反
CArray <GLfloat> DiffractionToTwoReflection;//一绕两反
CArray <GLfloat> TwoReflectionToTwoDiffraction;//两绕两反

CArray <Vec3T> GLBoundaryPoint;//多接收机的边界在OpenGL中的坐标
CArray <CPoint> ScrBoundaryPoint;//多接收机的边界在屏幕上的坐标


CArray <RxInfo> RxInfoSet;//接收机集合
CArray <TxInfo> TxInfoSet;//发射机集合

CArray <AntennaInfo> AnteInfo;//天线信息
CArray <ModualInfo> ModualWay;//调试方式信息
CArray <EnvironmentInfo> EnvInfo;//环境参数信息

CArray<CurPos3D>T1;//存放TIN的点
CArray<line>T2;//存放TIN的线
CArray<Triangle>T3;//存放TIN的三角形

GLfloat MapCenterX,MapCenterY,MapCenterZ;//地图或者TIN的中心点，为了保证视图看向地图中心
GLfloat Rmin,Rmax;//协调区范围边界
CArray <CurPos3D> Range;//范围边界点

ScaleVariable::ScaleVariable(void)
{
}

ScaleVariable::~ScaleVariable(void)
{
}
