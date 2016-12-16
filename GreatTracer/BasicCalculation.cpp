#include "StdAfx.h"
#include "BasicCalculation.h"
#include <math.h>


CBasicCalculation::CBasicCalculation(void)
{
	cntCalPlane = 0;cntCalImage = 0;cntCalPlaneInter = 0;cntCalDistance = 0;cntCalCross = 0;
	cntCalPoint = 0;cntCalIncludeDouble = 0;cntCalMoudle = 0;cntCalVec = 0;cntCalMidPoint = 0;cntCalIncident = 0;
}


CBasicCalculation::~CBasicCalculation(void)
{
}


PolyEquation CBasicCalculation::CalPlane(CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4)
{
	cntCalPlane++;

	PolyEquation res;
	Vec vec1, vec2, normalVec;
	vec1 = CalVector(p1, p2);
	vec2 = CalVector(p2, p3);
	normalVec = CalCrossProduct(vec1, vec2);
	res.normal = normalVec;
	res.D = normalVec.x * p2.x + normalVec.y * p2.y + normalVec.z * p2.z;

	return res;
}

CurPos3D CBasicCalculation::CalImagePoint(CurPos3D p, GLfloat A, GLfloat B, GLfloat C, GLfloat D)
{
	cntCalImage++;

	CurPos3D inter, res;
	Vec dirVec = {A, B, C};
	Vec normalVec = dirVec;
	GLfloat t = (D - A * p.x - B * p.y - C * p.z) / CalPointProduct(dirVec, normalVec);
	inter.x = dirVec.x * t + p.x;
	inter.y = dirVec.y * t + p.y;
	inter.z = dirVec.z * t + p.z;
	res.x = 2 * inter.x - p.x;
	res.y = 2 * inter.y - p.y;
	res.z = 2 * inter.z - p.z;

	return res;
}

CurPos3D CBasicCalculation::CalPlaneIntersection(CurPos3D p1, CurPos3D p2, GLfloat A, GLfloat B, GLfloat C, GLfloat D)
{
	cntCalPlaneInter++;

	GLfloat t;
	CurPos3D inter = {INT_MIN, INT_MIN, INT_MIN};
	Vec dirVec = CalVector(p1, p2);
	Vec normalVec = {A, B, C};
	GLfloat pointPro = CalPointProduct(dirVec, normalVec);
	if (0 != pointPro)
	{
		t = (D - A * p1.x - B * p1.y - C * p1.z) / pointPro;
		inter.x = dirVec.x * t + p1.x;
		inter.y = dirVec.y * t + p1.y;
		inter.z = dirVec.z * t + p1.z;
	}

	return inter;
}

GLfloat CBasicCalculation::CalDistance(CurPos3D p1, CurPos3D p2)
{
	cntCalDistance++;

	return SqrtByCarmark((p1.x - p2.x) * (p1.x - p2.x) 
		+ (p1.y - p2.y) * (p1.y - p2.y)
		+ (p1.z - p2.z) * (p1.z - p2.z));
	//return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

Vec CBasicCalculation::CalCrossProduct(Vec v1, Vec v2)
{
	cntCalCross++;

	Vec result;
	result.x = v1.y * v2.z - v1.z * v2.y;
	result.y = v1.z * v2.x - v1.x * v2.z;
	result.z = v1.x * v2.y - v1.y * v2.x;

	return result;
}

GLfloat CBasicCalculation::CalPointProduct(Vec v1, Vec v2)
{
	cntCalPoint++;

	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

GLfloat CBasicCalculation::CalIncludedAngle(Vec v1, Vec v2)
{
	return acos(CalPointProduct(v1, v2) / (CalModule(v1) * CalModule(v2)));
}

double CBasicCalculation::CalIncludedAngleDouble(Vec v1, Vec v2)
{
	cntCalIncludeDouble++;

	return acos((double)CalPointProduct(v1, v2) / (double)(CalModule(v1) * CalModule(v2)));
}

GLfloat CBasicCalculation::CalModule(Vec v)
{
	cntCalMoudle++;

	//GLfloat sum = pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2);
	//GLfloat sum = v.x * v.x + v.y * v.y + v.z * v.z;

	return SqrtByCarmark(v.x * v.x + v.y * v.y + v.z * v.z);
	//return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	//return sqrt(sum);
	//return sqrt(pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

Vec CBasicCalculation::CalVector(CurPos3D start, CurPos3D end)
{
	cntCalVec++;

	Vec res;
	res.x = end.x - start.x;
	res.y = end.y - start.y;
	res.z = end.z - start.z;
	return res;
}

CurPos3D CBasicCalculation::CalMiddlePoint(CurPos3D p1, CurPos3D p2)
{
	cntCalMidPoint++;

	CurPos3D res;
	res.x = (p1.x + p2.x) / 2;
	res.y = (p1.y + p2.y) / 2;
	res.z = (p1.z + p2.z) / 2;
	return res;
}

GLfloat CBasicCalculation::CalIncidentAngle(Vec inLine, CurPos3D p1, CurPos3D p2, CurPos3D p3, CurPos3D p4)
{
	cntCalIncident++;

	GLfloat ans;
	PolyEquation polyEq;
	polyEq = CalPlane(p1, p2, p3, p4);
	ans = CalIncludedAngle(inLine, polyEq.normal);

	return ans >= 0? ans: -ans;
	//return abs(ans);
}

GLfloat CBasicCalculation::SqrtByCarmark(GLfloat number)
{
	int i;
	GLfloat x2, y;
	const GLfloat threehalfs = 1.5F;

	x2 = number * 0.5F;
	y  = number;
	i  = * ( int * ) &y;     
	i  = 0x5f375a86 - ( i >> 1 ); 
	y  = * ( float * ) &i;
	y  = y * ( threehalfs - ( x2 * y * y ) ); 
	y  = y * ( threehalfs - ( x2 * y * y ) );  	
	y  = y * ( threehalfs - ( x2 * y * y ) ); 

	return number*y;
}