#pragma once

#include <limits.h>
#include <math.h>
#include "ScaleVariable.h"

class CBasicTest
{
public:
	CArray<CurPos3D> VertexSet; //��ͼ������Ϣ
	CArray<CurPos3D> txVisibleFace; //������ɼ���
	CArray<CurPos3D> rxVisibleFace; //���ջ��ɼ���
	CArray<CurPos3D> commonLine; //���ջ����������ͬ�ɼ�����
	CArray<CurPos3D> topFace; //���������
	CArray<CurPos3D> txVisibleLine; //������ɼ���
	CArray<CurPos3D> rxVisibleLine; //���ջ��ɼ���

public:
	CBasicTest(void);
	~CBasicTest(void);
	void loadTxRxInfo(CurPos3D txPos, CurPos3D rxPos); //�����շ��Ż�λ����Ϣ,Ѱ����Ӧ�ɼ���
	void loadMapInfo(CArray<GLfloat> &mapInfo); //����ͼ��Ϣ�洢�����ڱ���
	void loadTxInto(CurPos3D txPos); //���뷢���������Ϣ
	void loadRxInfo(CurPos3D rxPos); //������ջ�������Ϣ
	bool isVisible(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4); //�жϵ������Ŀɼ���,�ĵ�����ɼ�����false,����true
	bool haveObstacle(CurPos3D p1, CurPos3D p2); //�ж�������Ƿ�����ϰ�,��ŷ���true,���򷵻�false(Ĭ�����㲻�غ�)
	int inPolygon(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4); //�жϵ�������λ�ù�ϵ(0�ڲ�,1���ϷǶ˵㴦,2��˵㴦,3�ⲿ)
	int inSegment(CurPos3D p, CurPos3D v1, CurPos3D v2); //����һ��������ʾ�����߶ε�λ�ù�ϵ(0�ڲ�,1��˵��غ�,2�ⲿ)
	bool isSamePoint(CurPos3D p1, CurPos3D p2); //�ж������Ƿ��غ�
	bool isSameSide(CurPos3D start, CurPos3D middle, CurPos3D end, Vec normal); //�жϳ����������Ƿ������ͬһ��,ͬ�෵��true,����false
	bool isSameSegment(CurPos3D seg1a, CurPos3D seg1b, CurPos3D seg2a, CurPos3D seg2b); //�ж��߶�seg1��seg2�Ƿ�Ϊͬһ�߶�
	bool includeCommonLine(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4, CurPos3D segP1, CurPos3D segP2); //������Ƿ������ͬ�ɼ�����,��������true,����false
	bool inImpossibleArea(CurPos3D testPoint); //�жϴ�����Ƿ��ڲ����ܴ��ڵ�����(�������ǽ����),�Ƿ���true, ����false

private:
	void TrimVisibleLine(CArray<CurPos3D> &source ,CArray<CurPos3D> &des); //����ɼ���
	void FindCommonLine(CArray<CurPos3D> &txLine, CArray<CurPos3D> &rxLine, CArray<CurPos3D> &commonLine); //Ѱ�ҹ�ͬ�ɼ���


	
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