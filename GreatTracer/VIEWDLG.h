#pragma once

#pragma comment( lib, "glaux.lib" )
#pragma comment( lib, "glu32.lib" )
#pragma comment( lib, "OpenGL32.lib" )

#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"
#include "resource.h"
#include "ScaleVariable.h"
#include "vector"
#include "TIN.h"
#include "ArcBall.h"
#include "DrawEv.h"
#include "TX_PROPER_DIALOG.h"
#include "RX_DIALOG.h"
#include "ANTE_DIALOG.h"
#include "POLYGON_TX_DIALOG.h"
#include "POLYGON_RX_DIALOG.h"
#include "ReadandWrite.h"
#include "environmentDlg.h"


extern CArray <GLfloat> CubeVertex_Tx;//收发信机的小立方体坐标
extern CArray <GLfloat> CubeVertex_Rx;
extern CArray <GLfloat> RenderArray;
extern GLfloat space;//接收机的space
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

extern CArray <Vec3T> GLBoundaryPoint;//多接收机的边界在OpenGL中的坐标
extern CArray <CPoint> ScrBoundaryPoint;//多接收机的边界在屏幕上的坐标

extern CArray <RxInfo> RxInfoSet;//接收机信息
extern CArray <RxInfo> RxInfoSet;
extern CArray <TxInfo> TxInfoSet;//发射机信息
extern CArray <TxInfo> TxInfoSet;
extern CArray <AntennaInfo> AnteInfo;//天线信息
extern CArray <ModualInfo> ModualWay;//调试方式信息

extern CArray<CurPos3D>T1;//存放TIN的点
extern CArray<line>T2;//存放TIN的线
extern CArray<Triangle>T3;//存放TIN的三角形

extern GLfloat MapCenterX,MapCenterY,MapcenterZ;
extern GLfloat Rmin,Rmax;
extern CArray <CurPos3D> Range;//范围边界点
extern int isRender;

// CVIEWDLG 对话框

class CVIEWDLG : public CDialog
{
	DECLARE_DYNAMIC(CVIEWDLG)


public:
	CVIEWDLG(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVIEWDLG();

	//TX or RX Point Convert to a cube with 8 Points
	void Deal_Tx_Vertex_Cube(TxInfo Temp);
	void Deal_Rx_Vertex_Cube( RxInfo Temp);

	void AddEle();//向数组中添加元素
	CurPos3D PosInGL;//另一种float类型的OpenGL的坐标
	BOOL SeeFlag;//是否通视,true为通视,false表示有障碍存在

	void MagicSort(CArray <RxInfo> &aref,int low,int high);////排序
	int Partition(CArray<RxInfo> &aref,int i,int j);

	void PowerToColor(CArray <RxInfo> &AREF);//由接收功率判定相应颜色
	void MyPowerToColor(CArray <RxInfo> &AREF);
	
	void Deal_Render_Quads(CurPos3D temp);//处理渲染的小四边形

	void GetCoor_TIN(GLfloat tempx,GLfloat tempy);
private:
	BOOL SetWindowPixelFormat(HDC hDC);//设定像素格式
	BOOL CreateViewGLContext(HDC hDC);//View GL Context
	void RenderScene();//绘制场景
	void ReshapeSize();//定义视口
	HDC hrenderDC;//DC
	HGLRC hrenderRC;//RC
	int PixelFormat;
	void Opengl_light();//光照控制
	void GetSize();//获取控件尺寸
	CRect cr_Size;//控件尺寸存储
	void SetupRC();//初始化场景
	int  IsButtonLeftDown;//鼠标左右键指示
	int IsButtonRightDown;//鼠标右键是否按下
	POINT cur_pos,last_pos;//记录鼠标位置
	float m_xScaling,m_yScaling,m_zScaling;//缩放因子
	CArray <CString> Vertex;//存储地图顶点位置
	int InitFlag;//初始化指示标志
	void GetImg();
	void FPSrate();//获取帧速率
	void GetCoor(CPoint point);//获取鼠标在模型中的位置

	void CurPos3DToGlfloat(CArray<CurPos3D> &curpos, CArray<GLfloat> &glf); //将CurPos3D坐标转换为glfloat坐标
	
	bool TxPointFlag,TxPolygonFlag,RxPointFlag,RxPolygonFlag;//收发信机设置模式指示
	CString Dxfpath,Citypath,CityName,DxfName,Imgpath;//文件名和文件位置
	bool IsRender,IsPathAvailable,IsRenderOutput;//RenderFlag & PathFlag & 是否通视;
	bool IsRange;//范围可计算
	bool IsRangeable;//准确范围计算
	int PointVision;//画点的维度
	int TinFlag;//是否画TIN
	int IsSetTexTure;
// 对话框数据
	enum { IDD = IDD_VIEW_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual BOOL OnInitDialog();//初始化窗口重载

	
public:
	//////////////////////////////////////////////////////////////////////////
	//下面主要是一些对话框的消息函数，按钮函数声明
	//////////////////////////////////////////////////////////////////////////
	afx_msg void OnPaint();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnFileDxf();
	afx_msg void OnFileCity();
	afx_msg void OnViewRender();
	afx_msg void OnViewNormal();
	afx_msg void OnTransmmitsPoints();
	afx_msg void OnReceiversPoints();
	afx_msg void OnTransmmitsPolygons();
	afx_msg void OnReceiversPolygons();
	afx_msg void OnClose();
	afx_msg void OnOutputPowerpath();
	afx_msg void OnSetAntenna();
	afx_msg void OnOutputRenderoutput();
	afx_msg void OnClearPolygontx();
	afx_msg void OnClearPolygonrx();
	afx_msg void OnExamplePathexample();
	afx_msg void OnExampleRenderexample();
	afx_msg void OnEditTin();
	afx_msg void OnEditModeltin();
	afx_msg void OnClearTin();
	afx_msg void OnClearPath();
	afx_msg void OnClearPointtx();
	afx_msg void OnClearPointrx();
	afx_msg void OnClearRender();
	afx_msg void OnFileTin();
	afx_msg void OnTestTest1();//计算边界范围
	afx_msg void OnView32819();
	afx_msg void OnEditTin32820();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClearAll();
	afx_msg void OnSetEnvironment();
	afx_msg void OnTestRange();//计算边界点
};
