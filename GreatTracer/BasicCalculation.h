#pragma once

#include "ScaleVariable.h"

class CBasicCalculation
{
public:

	unsigned long cntCalPlane, cntCalImage, cntCalPlaneInter, cntCalDistance, cntCalCross, 
		cntCalPoint, cntCalIncludeDouble, cntCalMoudle, cntCalVec, cntCalMidPoint, cntCalIncident;

	CBasicCalculation(void);
	~CBasicCalculation(void);

	GLfloat SqrtByCarmark(GLfloat);//����˿�ƽ���㷨

	PolyEquation CalPlane(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4); //������ϢΪ�ĵ�����
	CurPos3D CalImagePoint(CurPos3D p, GLfloat A, GLfloat B, GLfloat C, GLfloat D); //���㾵�������
	CurPos3D CalPlaneIntersection(CurPos3D p1, CurPos3D p2, GLfloat A, GLfloat B, GLfloat C, GLfloat D); //��������p1,p2��������������ƽ��Ľ���
	GLfloat CalDistance(CurPos3D p1, CurPos3D p2); //���������ľ���
	Vec CalCrossProduct(Vec v1, Vec v2); //��������v1������v2��ʸ����
	GLfloat CalPointProduct(Vec v1, Vec v2); //�����������ĵ��
	GLfloat CalIncludedAngle(Vec v1, Vec v2); //������������ļн�(��λΪ����)

	double CalIncludedAngleDouble(Vec v1, Vec v2); //������������ļн�(��λΪ����)

	GLfloat CalModule(Vec v); //����������ģ
	Vec CalVector(CurPos3D start, CurPos3D end); //����start��end������
	CurPos3D CalMiddlePoint(CurPos3D p1, CurPos3D p2); //���������е�
	GLfloat CalIncidentAngle(Vec inLine, CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4); //���������(�����)�Ļ���(��ע��inLine����)
};