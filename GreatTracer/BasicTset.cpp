#include "StdAfx.h"
#include "BasicTset.h"
#include "BasicCalculation.h"


CBasicTest::CBasicTest(void)
{
}


CBasicTest::~CBasicTest(void)
{

}


void CBasicTest::loadMapInfo(CArray<GLfloat> &mapInfo)
{
	CurPos3D temp, p1, p2, p3, p4;

	for (int i = 0; i <= mapInfo.GetCount() - 3; i += 3)
	{
		temp.x = mapInfo[i];
		temp.y = mapInfo[i + 1];
		temp.z = mapInfo[i + 2];
		VertexSet.Add(temp);
	}

	for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
	{
		p1 = VertexSet[i];
		p2 = VertexSet[i + 1];
		p3 = VertexSet[i + 2];
		p4 = VertexSet[i + 3];
		if (0 != VertexSet[i].z && 0 != VertexSet[i + 1].z 
			&& 0 != VertexSet[i + 2].z && 0 != VertexSet[i + 3].z)
		{
			topFace.Add(p1);
			topFace.Add(p2);
			topFace.Add(p3);
			topFace.Add(p4);
		}
	}
}


void CBasicTest::loadTxInto(CurPos3D txPos)
{
	CurPos3D p1, p2, p3, p4;

	for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
	{
		p1 = VertexSet[i];
		p2 = VertexSet[i + 1];
		p3 = VertexSet[i + 2];
		p4 = VertexSet[i + 3];

		if (isVisible(txPos, p1, p2, p3, p4))
		{
			txVisibleFace.Add(p1);
			txVisibleFace.Add(p2);
			txVisibleFace.Add(p3);
			txVisibleFace.Add(p4);
		}
	}
}


void CBasicTest::loadRxInfo(CurPos3D rxPos)
{
	CurPos3D p1, p2, p3, p4;

	for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
	{
		p1 = VertexSet[i];
		p2 = VertexSet[i + 1];
		p3 = VertexSet[i + 2];
		p4 = VertexSet[i + 3];
		if (isVisible(rxPos, p1, p2, p3, p4))
		{
			rxVisibleFace.Add(p1);
			rxVisibleFace.Add(p2);
			rxVisibleFace.Add(p3);
			rxVisibleFace.Add(p4);
		}
	}

	TrimVisibleLine(txVisibleFace, txVisibleLine);
	TrimVisibleLine(rxVisibleFace, rxVisibleLine);
	FindCommonLine(txVisibleLine, rxVisibleLine, commonLine);
}


void CBasicTest::loadTxRxInfo(CurPos3D txPos, CurPos3D rxPos)
{
	//CurPos3D p1, p2, p3, p4;
	//CArray<CurPos3D> txVisibleLine, rxVisibleLine;

	//txVisibleFace.RemoveAll();
	//rxVisibleFace.RemoveAll();
	//commonLine.RemoveAll();
	//txVisibleLine.RemoveAll();
	//rxVisibleLine.RemoveAll();

	//for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
	//{
	//	p1 = VertexSet[i];
	//	p2 = VertexSet[i + 1];
	//	p3 = VertexSet[i + 2];
	//	p4 = VertexSet[i + 3];
	//	if (isVisible(txPos, p1, p2, p3, p4))
	//	{
	//		txVisibleFace.Add(p1);
	//		txVisibleFace.Add(p2);
	//		txVisibleFace.Add(p3);
	//		txVisibleFace.Add(p4);
	//	}
	//	if (isVisible(rxPos, p1, p2, p3, p4))
	//	{
	//		rxVisibleFace.Add(p1);
	//		rxVisibleFace.Add(p2);
	//		rxVisibleFace.Add(p3);
	//		rxVisibleFace.Add(p4);
	//	}
	//}

	loadTxInto(txPos);
	loadRxInfo(rxPos);

	TrimVisibleLine(txVisibleFace, txVisibleLine);
	TrimVisibleLine(rxVisibleFace, rxVisibleLine);
	FindCommonLine(txVisibleLine, rxVisibleLine, commonLine);
}

bool CBasicTest::includeCommonLine(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4, CurPos3D segP1, CurPos3D segP2)
{
	bool flag = false;
	if (isSameSegment(p1, p2, segP1, segP2) || isSameSegment(p2, p3, segP1, segP2) 
		|| isSameSegment(p3, p4, segP1, segP2) || isSameSegment(p4, p1, segP1, segP2))
	{
		flag = true;
	}

	return flag;
}

void CBasicTest::FindCommonLine(CArray<CurPos3D> &txLine, CArray<CurPos3D> &rxLine, CArray<CurPos3D> &commonLine)
{
	for (int i = 0; i <= txLine.GetCount() - 2; i += 2)
	{
		for (int j = 0; j <= rxLine.GetCount() - 2; j += 2)
		{
			if (isSameSegment(txLine[i], txLine[i + 1], rxLine[j], rxLine[j + 1]))
			{
				commonLine.Add(txLine[i]);
				commonLine.Add(txLine[i + 1]);
				break;
			}
		}
	}
}

void CBasicTest::TrimVisibleLine(CArray<CurPos3D> &source ,CArray<CurPos3D> &des)
{
	bool isExist;
	for (int i = 0; i <= source.GetCount() - 2; i += 2)
	{
		isExist = false;
		if (!isSamePoint(source[i], source[i + 1]))
		{
			if (0 != i)
			{
				for (int j = 0; j <= des.GetCount() - 2; j += 2)
				{
					if (isSameSegment(source[i], source[i + 1], des[j], des[j + 1]))
					{
						isExist = true;
						break;
					}
				}
			}
			if (!isExist)
			{
				des.Add(source[i]);
				des.Add(source[i + 1]);
			}
		} 
	}
}

bool CBasicTest::isVisible(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4)
{
	CBasicCalculation cal;
	PolyEquation equ;
	Vec inVector;
	bool flag1, flag2, flag3, flag4;

	equ = cal.CalPlane(v1, v2, v3, v4);
	inVector = cal.CalVector(p, v2);

	GLfloat pointP = cal.CalPointProduct(inVector, equ.normal);

	//默认点序顺时针
	if(0 < pointP)
	{
		//存在极端情况:只遮挡四点,本方案不考虑此种情况,在室内计算存在窗户的情况下可能产生错误结果
		flag1 = haveObstacle(p, v1);

		flag2 = haveObstacle(p, v2);

		flag3 = haveObstacle(p, v3);

		flag4 = haveObstacle(p, v4);

		if (flag1 && flag2 && flag3 && flag4)
			return false;
		else
			return true;
	}
	else
		return false;
}

bool CBasicTest::haveObstacle(CurPos3D p1, CurPos3D p2)
{
	bool flag = false;
	CBasicCalculation cal;
	CurPos3D intersection;
	PolyEquation equ;
	for (int i = 0; i <= VertexSet.GetCount() - 4; i += 4)
	{
		equ = cal.CalPlane(VertexSet[i], VertexSet[i + 1], VertexSet[i + 2], VertexSet[i + 3]);
		intersection = cal.CalPlaneIntersection(p1, p2, equ.normal.x, equ.normal.y, equ.normal.z, equ.D);
		if (3 != inPolygon(intersection, VertexSet[i], VertexSet[i + 1], VertexSet[i + 2], VertexSet[i + 3]) 
			&& 0 == inSegment(intersection, p1, p2))
		{
			flag = true;
			break;
		}
	}
	return flag;
}

int CBasicTest::inPolygon(CurPos3D p, CurPos3D v1, CurPos3D v2, CurPos3D v3, CurPos3D v4)
{
	if (isSamePoint(p, v1) || isSamePoint(p, v2) || isSamePoint(p, v3) || isSamePoint(p, v4))
	{
		return 2;
	}
	if (0 == inSegment(p, v1, v2) || 0 == inSegment(p, v2, v3) || 0 == inSegment(p, v3, v4)
		|| 0 == inSegment(p, v4, v1))
	{
		return 1;
	}
	
	CBasicCalculation cal;
	//GLfloat sum = 0;
	//GLfloat tempRad1, tempRad2, tempRad3, tempRad4;
	double tempRad1, tempRad2, tempRad3, tempRad4;
	double sum = 0;
	Vec vec1 = cal.CalVector(p, v1);
	Vec vec2 = cal.CalVector(p, v2);
	Vec vec3 = cal.CalVector(p, v3);
	Vec vec4 = cal.CalVector(p, v4);
	//tempRad1 = cal.CalIncludedAngle(vec1, vec2);
	//tempRad2 = cal.CalIncludedAngle(vec2, vec3);
	//tempRad3 = cal.CalIncludedAngle(vec3, vec4);
	//tempRad4 = cal.CalIncludedAngle(vec4, vec1);
	tempRad1 = cal.CalIncludedAngleDouble(vec1, vec2);
	tempRad2 = cal.CalIncludedAngleDouble(vec2, vec3);
	tempRad3 = cal.CalIncludedAngleDouble(vec3, vec4);
	tempRad4 = cal.CalIncludedAngleDouble(vec4, vec1);
	sum = tempRad1 + tempRad2 + tempRad3 + tempRad4;
	//double res = abs(sum - 2 * M_PI);
	if (THRESHOLD * 0.1 >= abs(sum - 2 * M_PI))
	//if (threshold >= res)
	{
		return 0;
	}
	else
	{
		return 3;
	}
}

int CBasicTest::inSegment(CurPos3D p, CurPos3D v1, CurPos3D v2)
{

	CBasicCalculation cal;
	GLfloat dp1 = cal.CalDistance(p, v1);
	GLfloat dp2 = cal.CalDistance(p, v2);
	GLfloat d12 = cal.CalDistance(v1, v2);
	if (isSamePoint(p, v1) || isSamePoint(p, v2))
	{
		return 1;
	}
	else if (THRESHOLD * 10000 >= abs(d12 - dp1 - dp2))
	{
		return 0;
	} 
	else
	{
		return 2;
	}
}

bool CBasicTest::isSamePoint(CurPos3D p1, CurPos3D p2)
{
	CBasicCalculation cal;
	return THRESHOLD >= cal.CalDistance(p1, p2);
}

bool CBasicTest::isSameSide(CurPos3D start, CurPos3D middle, CurPos3D end, Vec normalVec)
{
	CBasicCalculation cal;
	Vec vecIn, vecOut;
	GLfloat angIn, angOut;
	vecIn = cal.CalVector(middle, start);
	vecOut = cal.CalVector(middle, end);
	angIn = cal.CalIncludedAngle(vecIn, normalVec);
	angOut = cal.CalIncludedAngle(normalVec, vecOut);
	if (THRESHOLD * 10000 >= abs(angIn - angOut))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

bool CBasicTest::isSameSegment(CurPos3D seg1a, CurPos3D seg1b, CurPos3D seg2a, CurPos3D seg2b)
{
	bool flag1, flag2, flag3, flag4;
	flag1 = isSamePoint(seg1a, seg2a);
	flag2 = isSamePoint(seg1b, seg2b);
	flag3 = isSamePoint(seg1a, seg2b);
	flag4 = isSamePoint(seg1b, seg2a);

	return (flag1 && flag2) || (flag3 && flag4);
}


bool CBasicTest::inImpossibleArea(CurPos3D testPoint)
{
	bool ans = false;
	CurPos3D temp = {testPoint.x, testPoint.y, 0.0};

	for (int i = 0; i <= topFace.GetCount() - 4; i += 4)
	{
		CurPos3D p1 = {topFace[i].x, topFace[i].y, 0.0};
		CurPos3D p2 = {topFace[i + 1].x, topFace[i + 1].y, 0.0};
		CurPos3D p3 = {topFace[i + 2].x, topFace[i + 2].y, 0.0};
		CurPos3D p4 = {topFace[i + 3].x, topFace[i + 3].y, 0.0};

		if (testPoint.z < topFace[i].z 
			&& testPoint.z < topFace[i + 1].z 
			&& testPoint.z < topFace[i + 2].z
			&& testPoint.z < topFace[i + 2].z)
		{
			if (3 != inPolygon(temp, p1, p2, p3, p4))
			{
				ans = true;
			}
		}

		if (ans)
			break;
	}

	return ans;
}
