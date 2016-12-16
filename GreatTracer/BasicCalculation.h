#pragma once

#include "ScaleVariable.h"

class CBasicCalculation
{
public:

	unsigned long cntCalPlane, cntCalImage, cntCalPlaneInter, cntCalDistance, cntCalCross, 
		cntCalPoint, cntCalIncludeDouble, cntCalMoudle, cntCalVec, cntCalMidPoint, cntCalIncident;

	CBasicCalculation(void);
	~CBasicCalculation(void);

	GLfloat SqrtByCarmark(GLfloat);//卡马克开平方算法

	PolyEquation CalPlane(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4); //传入信息为四点坐标
	CurPos3D CalImagePoint(CurPos3D p, GLfloat A, GLfloat B, GLfloat C, GLfloat D); //计算镜像点坐标
	CurPos3D CalPlaneIntersection(CurPos3D p1, CurPos3D p2, GLfloat A, GLfloat B, GLfloat C, GLfloat D); //计算两点p1,p2连线与多边形所在平面的交点
	GLfloat CalDistance(CurPos3D p1, CurPos3D p2); //计算两点间的距离
	Vec CalCrossProduct(Vec v1, Vec v2); //计算向量v1到向量v2的矢量积
	GLfloat CalPointProduct(Vec v1, Vec v2); //计算两向量的点积
	GLfloat CalIncludedAngle(Vec v1, Vec v2); //计算两向量间的夹角(单位为弧度)

	double CalIncludedAngleDouble(Vec v1, Vec v2); //计算两向量间的夹角(单位为弧度)

	GLfloat CalModule(Vec v); //计算向量的模
	Vec CalVector(CurPos3D start, CurPos3D end); //计算start到end的向量
	CurPos3D CalMiddlePoint(CurPos3D p1, CurPos3D p2); //计算两点中点
	GLfloat CalIncidentAngle(Vec inLine, CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4); //计算入射角(出射角)的弧度(需注意inLine方向)
};