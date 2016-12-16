#pragma once

#include <limits.h>
#include <math.h>
#include "ScaleVariable.h"

class CBasicTest
{
public:
	CArray<CurPos3D> VertexSet; //地图顶点信息
	CArray<CurPos3D> txVisibleFace; //发射机可见面
	CArray<CurPos3D> rxVisibleFace; //接收机可见面
	CArray<CurPos3D> commonLine; //接收机、发射机共同可见的棱
	CArray<CurPos3D> topFace; //建筑物底面
	CArray<CurPos3D> txVisibleLine; //发射机可见棱
	CArray<CurPos3D> rxVisibleLine; //接收机可见棱

public:
	CBasicTest(void);
	~CBasicTest(void);
	void loadTxRxInfo(CurPos3D txPos, CurPos3D rxPos); //载入收发信机位置信息,寻找相应可见面
	void loadMapInfo(CArray<GLfloat> &mapInfo); //将地图信息存储到类内变量
	void loadTxInto(CurPos3D txPos); //载入发射机集合信息
	void loadRxInfo(CurPos3D rxPos); //载入接收机集合信息
	bool isVisible(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4); //判断点对于面的可见性,四点均不可见返回false,否则true
	bool haveObstacle(CurPos3D p1, CurPos3D p2); //判断两点间是否存在障碍,存才返回true,否则返回false(默认两点不重合)
	int inPolygon(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4); //判断点与多边形位置关系(0内部,1棱上非端点处,2棱端点处,3外部)
	int inSegment(CurPos3D p, CurPos3D v1, CurPos3D v2); //返回一个整数表示点与线段的位置关系(0内部,1与端点重合,2外部)
	bool isSamePoint(CurPos3D p1, CurPos3D p2); //判断两点是否重合
	bool isSameSide(CurPos3D start, CurPos3D middle, CurPos3D end, Vec normal); //判断出射入射线是否在面的同一侧,同侧返回true,否则false
	bool isSameSegment(CurPos3D seg1a, CurPos3D seg1b, CurPos3D seg2a, CurPos3D seg2b); //判断线段seg1和seg2是否为同一线段
	bool includeCommonLine(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4, CurPos3D segP1, CurPos3D segP2); //多边形是否包含共同可见的棱,包含返回true,否则false
	bool inImpossibleArea(CurPos3D testPoint); //判断待测点是否在不可能存在的区域(建筑物或墙体内),是返回true, 否则false

private:
	void TrimVisibleLine(CArray<CurPos3D> &source ,CArray<CurPos3D> &des); //整理可见棱
	void FindCommonLine(CArray<CurPos3D> &txLine, CArray<CurPos3D> &rxLine, CArray<CurPos3D> &commonLine); //寻找共同可见棱


	
//inline bool CBasicTest::haveObstacle(CurPos3D p1, CurPos3D p2)
//	{
//		cnt++;
//	
//		bool flag = false;
//		CBasicCalculation cal;
//		CurPos3D intersection;
//		PolyEquation equ;
//		for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
//		{
//			equ = cal.CalPlane(VertexSet[i], VertexSet[i + 1], VertexSet[i + 2], VertexSet[i + 3]);
//			intersection = cal.CalPlaneIntersection(p1, p2, equ.normal.x, equ.normal.y, equ.normal.z, equ.D);
//			if (3 != inPolygon(intersection, VertexSet[i], VertexSet[i + 1], VertexSet[i + 2], VertexSet[i + 3]) 
//				&& 0 == inSegment(intersection, p1, p2))
//			{
//				flag = true;
//				break;
//			}
//		}
//		return flag;
//	}


};