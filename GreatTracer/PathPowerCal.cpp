#include "StdAfx.h"
#include "PathPowerCal.h"
#include <limits.h>
#include <time.h>
#include <random>
//#define C 300000000
//#define random(x) (rand() % (x + 1) / x)


CPathPowerCal::CPathPowerCal(void)
{
	permittivity = 6.4f;
	conductivity = 0.0001f;

	indexDirect = 0;
	indexOneRef = 0;
	indexTwoRef = 0;
	indexOneDiff = 0;
	indexRefDiff = 0;
	indexDiffRef = 0;
	indexRefDiffRef = 0;
}


CPathPowerCal::~CPathPowerCal(void)
{
}


void CPathPowerCal::LoadInfo(CArray<TxInfo> &txSet, CArray<RxInfo> &rxSet, CArray<GLfloat> &originalMapData,CArray<EnvironmentInfo> &environment)
{
	GLfloat tempPower;
	LoadEnvInfo(environment[0]);//加载大气信息
	test.loadMapInfo(originalMapData);
	

	for (int i = 0; i < rxSet.GetCount(); i++)
	{
		rxSet[i].ReceivedPower = INT_MIN;
	}

	for (int i = 0; i < txSet.GetCount(); i++)
	{
		LoadTxInto(txSet[i]);
		for (int j = 0; j < rxSet.GetCount(); j++)
		{
			LoadRxInfo(rxSet[j]);
			GLfloat sum = 0;
			if (!test.inImpossibleArea(rx.Pos))
			{
				Direct();
				OneReflection();
				TwoReflection();
				OneDiffraction();
				RefDiff();
				DiffRef();
				//RefDiffRef();
			}
			sum = CalSumPower();

			if (INT_MIN == rxSet[j].ReceivedPower)
			{
				rxSet[j].ReceivedPower = sum;
			} 
			else
			{
				tempPower = rxSet[j].ReceivedPower;
				//单位变换:dBm—>w
				tempPower = pow(10, (tempPower - 30) / 10);
				sum = pow(10, (sum - 30) / 10);

				tempPower += sum;

				//单位变换:w—>dBm
				tempPower = 10 * log10(tempPower) + 30;

				rxSet[j].ReceivedPower = tempPower;
			}
		}
	}

	test;
	cal;
}


void CPathPowerCal::LodaMapInfo(CArray<GLfloat> &originalMapData)
{
	test.loadMapInfo(originalMapData);
}


void CPathPowerCal::LoadTxRxInfo(TxInfo txInfo, RxInfo rxInfo)
{
	tx = txInfo;
	rx = rxInfo;
	test.loadTxRxInfo(txInfo.Pos, rxInfo.Pos);
}


void CPathPowerCal::LoadTxInto(TxInfo txInfo)
{
	tx = txInfo;
	if (0 != test.txVisibleFace.GetCount())
	{
		test.txVisibleFace.RemoveAll();
	}
	test.loadTxInto(txInfo.Pos);
}


void CPathPowerCal::LoadRxInfo(RxInfo rxInfo)
{
	rx = rxInfo;
	if (0 != test.rxVisibleFace.GetCount())
	{
		test.txVisibleLine.RemoveAll();	
		test.rxVisibleFace.RemoveAll();
		test.rxVisibleLine.RemoveAll();
		test.commonLine.RemoveAll();
	}
	test.loadRxInfo(rxInfo.Pos);
}

void CPathPowerCal::LoadEnvInfo(EnvironmentInfo envInfo)
{
	env=envInfo;
}


void CPathPowerCal::Direct()
{
	if (!test.haveObstacle(tx.Pos, rx.Pos))
	{
		pathDirect.Add(tx.Pos);
		pathDirect.Add(rx.Pos);
	}
}


void CPathPowerCal::OneReflection()
{
	PolyEquation equ;
	CurPos3D p1, p2, p3, p4, imagePoint, intersection;

	for (int i = 0; i <= test.txVisibleFace.GetCount() - 4; i += 4)
	{
		p1 = test.txVisibleFace[i];
		p2 = test.txVisibleFace[i + 1];
		p3 = test.txVisibleFace[i + 2];
		p4 = test.txVisibleFace[i + 3];
		equ = cal.CalPlane(p1, p2, p3, p4);
		imagePoint = cal.CalImagePoint(tx.Pos, equ.normal.x, equ.normal.y, equ.normal.z, equ.D);
		intersection = cal.CalPlaneIntersection(rx.Pos, imagePoint, equ.normal.x, 
			equ.normal.y, equ.normal.z, equ.D);
		//if(!DeciAnteAcl(tx, intersection))
		//{
		//	continue;
		//}
		if (0 == test.inPolygon(intersection, p1, p2, p3, p4))
		{
			if (!test.haveObstacle(intersection, tx.Pos) 
				&& !test.haveObstacle(intersection, rx.Pos)
				&& test.isSameSide(tx.Pos, intersection, rx.Pos, equ.normal))
			{
				pathOneRef.Add(tx.Pos);
				pathOneRef.Add(intersection);
				pathOneRef.Add(rx.Pos);
			}
		}
	}
}


void CPathPowerCal::TwoReflection()
{
	PolyEquation equ1, equ2;
	CurPos3D p1, p2, p3, p4, q1, q2, q3, q4, imageOne, imageTwo, intersectionOne, intersectionTwo;
	CArray<CurPos3D> imageOnePoinSet, imageTwoPointSet;
	
	for (int i = 0; i <= test.txVisibleFace.GetCount() - 4; i += 4)
	{
		p1 = test.txVisibleFace[i];
		p2 = test.txVisibleFace[i + 1];
		p3 = test.txVisibleFace[i + 2];
		p4 = test.txVisibleFace[i + 3];
		equ1 = cal.CalPlane(p1, p2, p3, p4);
		imageOne = cal.CalImagePoint(tx.Pos, equ1.normal.x, equ1.normal.y, equ1.normal.z, equ1.D);
		for(int j = 0; j <= test.rxVisibleFace.GetCount() - 4; j += 4)
		{
			q1 = test.rxVisibleFace[j];
			q2 = test.rxVisibleFace[j + 1];
			q3 = test.rxVisibleFace[j + 2];
			q4 = test.rxVisibleFace[j + 3];
			equ2 = cal.CalPlane(q1, q2, q3, q4);
			imageTwo = cal.CalImagePoint(imageOne, equ2.normal.x, equ2.normal.y, equ2.normal.z, equ2.D);
			intersectionTwo = cal.CalPlaneIntersection(imageTwo, rx.Pos, equ2.normal.x, 
				equ2.normal.y, equ2.normal.z, equ2.D);
			if (0 == test.inPolygon(intersectionTwo, q1, q2, q3, q4))
			{
				intersectionOne = cal.CalPlaneIntersection(imageOne, intersectionTwo, 
					equ1.normal.x, equ1.normal.y, equ1.normal.z, equ1.D);
				//if(!DeciAnteAcl(tx, intersectionOne))
				//{
				//	continue;
				//}
				if (0 == test.inPolygon(intersectionOne, p1, p2, p3, p4))
				{
					if (test.isSameSide(tx.Pos, intersectionOne, intersectionTwo, equ1.normal) 
						&& test.isSameSide(intersectionOne,intersectionTwo, rx.Pos, equ2.normal))
					{
						if (!test.haveObstacle(tx.Pos, intersectionOne) 
							&& !test.haveObstacle(intersectionOne, intersectionTwo)
							&& !test.haveObstacle(intersectionTwo, rx.Pos))
						{
							pathTwoRef.Add(tx.Pos);
							pathTwoRef.Add(intersectionOne);
							pathTwoRef.Add(intersectionTwo);
							pathTwoRef.Add(rx.Pos);
						}
					}
				}
			}
		}
	}
}


void CPathPowerCal::OneDiffraction()
{
	CurPos3D impossiblePoint = {INT_MIN, INT_MIN, INT_MIN};
	CurPos3D diffPoint;

	for (int i = 0; i <= test.commonLine.GetCount() - 2; i += 2)
	{
		if (0 == test.commonLine[i].z && 0 == test.commonLine[i + 1].z)
			continue;
		else
		{
			diffPoint = FindDiffractionPoint(tx.Pos, rx.Pos, 
				test.commonLine[i], test.commonLine[i + 1]);
			if (!test.isSamePoint(impossiblePoint, diffPoint))
			{
				if (!test.haveObstacle(diffPoint, tx.Pos) && !test.haveObstacle(diffPoint, rx.Pos))
				{
					pathOneDiff.Add(tx.Pos);
					pathOneDiff.Add(diffPoint);
					pathOneDiff.Add(rx.Pos);
				}
			}
		}
	}
}


CurPos3D CPathPowerCal::FindDiffractionPoint(CurPos3D tx, CurPos3D rx, CurPos3D p1, CurPos3D p2)
{
	int testTime = 18; //考虑THRESHOLD为0.000001后的最佳值,同时考虑到GLfloat精度
	CurPos3D temp1, temp2, testPoint;
	CurPos3D imPoint = {INT_MIN, INT_MIN, INT_MIN};
	Vec dirVec, vtr, vin, vout;
	GLfloat angleIn, angleOut;
	testPoint = cal.CalMiddlePoint(p1, p2);
	vtr = cal.CalVector(tx, rx);
	dirVec = cal.CalVector(p1, p2);
	if (0 > cal.CalPointProduct(vtr, dirVec))
	{
		dirVec = cal.CalVector(p2, p1);
		temp1 = p2;
		temp2 = p1;
	}
	else
	{
		temp1 = p1;
		temp2 = p2;
	}

	//二分法探测,testTime为探测次数
	//注释部分与外部功能重复,影响复合路径计算,注释后该函数仅作绕射点求算,可见性判断放在外部进行
	for(int i = 0; i < testTime; i++)
	{
		vin = cal.CalVector(tx, testPoint);
		vout = cal.CalVector(testPoint, rx);
		angleIn = cal.CalIncludedAngle(vin, dirVec);
		angleOut = cal.CalIncludedAngle(vout, dirVec);
		if (THRESHOLD * 10000 >= abs(angleIn - angleOut))
		{
			//if (!test.haveObstacle(testPoint, tx) && !test.haveObstacle(testPoint, rx))
			//{
				return testPoint;
			//} 
			//else
			//{
				//break;
			//}
		} 
		else
		{
			if (angleIn < angleOut)
			{
				temp2 = testPoint;
			} 
			else
			{
				temp1 = testPoint;
			}
			testPoint = cal.CalMiddlePoint(temp1, temp2);
		}
		if (THRESHOLD * 100 >= cal.CalDistance(testPoint, p1) 
			|| THRESHOLD * 100 >= cal.CalDistance(testPoint, p2))
		{
			break;
		}
	}
	return imPoint;
}


void CPathPowerCal::RefDiff()
{
	CurPos3D imageTx;
	PolyEquation refPlane;
	CurPos3D impossiblePoint = {INT_MIN, INT_MIN, INT_MIN};
	CurPos3D diffPoint, refPoint;
	CurPos3D p1, p2, p3, p4;

	for (int i = 0; i <= test.txVisibleFace.GetCount() - 4; i += 4)
	{
		p1 = test.txVisibleFace[i];
		p2 = test.txVisibleFace[i + 1];
		p3 = test.txVisibleFace[i + 2];
		p4 = test.txVisibleFace[i + 3];
		refPlane = cal.CalPlane(p1, p2, p3, p4);
		imageTx = cal.CalImagePoint(tx.Pos, refPlane.normal.x, refPlane.normal.y, 
			refPlane.normal.z,refPlane.D);
		for (int j = 0; j <= test.rxVisibleLine.GetCount() - 2; j += 2)
		{
			if (0 == test.rxVisibleLine[j].z && 0 == test.rxVisibleLine[j + 1].z)
				continue;
			else
			{
				diffPoint = FindDiffractionPoint(imageTx, rx.Pos, 
					test.rxVisibleLine[j], test.rxVisibleLine[j + 1]);
				if (!test.isSamePoint(impossiblePoint, diffPoint))
				{
					if (!test.haveObstacle(diffPoint, rx.Pos))
					{
						refPoint = cal.CalPlaneIntersection(diffPoint, imageTx, refPlane.normal.x, 
							refPlane.normal.y, refPlane.normal.z, refPlane.D);
						if (0 == test.inPolygon(refPoint, p1, p2, p3, p4))
						{
							if (test.isSameSide(tx.Pos, refPoint, diffPoint, refPlane.normal))
							{
								if (!test.haveObstacle(refPoint, diffPoint) 
									&& !test.haveObstacle(refPoint, tx.Pos))
								{
									pathRefDiff.Add(tx.Pos);
									pathRefDiff.Add(refPoint);
									pathRefDiff.Add(diffPoint);
									pathRefDiff.Add(rx.Pos);
								}
							}
						}
					}
				}
			}
		}
	}
}


void CPathPowerCal::DiffRef()
{
	CurPos3D imageRx;
	PolyEquation refPlane;
	CurPos3D impossiblePoint = {INT_MIN, INT_MIN, INT_MIN};
	CurPos3D diffPoint, refPoint;
	CurPos3D p1, p2, p3, p4;

	for (int i = 0; i <= test.rxVisibleFace.GetCount() - 4; i += 4)
	{
		p1 = test.rxVisibleFace[i];
		p2 = test.rxVisibleFace[i + 1];
		p3 = test.rxVisibleFace[i + 2];
		p4 = test.rxVisibleFace[i + 3];
		refPlane = cal.CalPlane(p1, p2, p3, p4);
		imageRx = cal.CalImagePoint(rx.Pos, refPlane.normal.x, refPlane.normal.y, 
			refPlane.normal.z,refPlane.D);
		for (int j = 0; j <= test.txVisibleLine.GetCount() - 2; j += 2)
		{
			if (0 == test.txVisibleLine[j].z && 0 == test.txVisibleLine[j + 1].z)
				continue;
			else
			{
				diffPoint = FindDiffractionPoint(imageRx, tx.Pos, 
					test.txVisibleLine[j], test.txVisibleLine[j + 1]);
				if (!test.isSamePoint(impossiblePoint, diffPoint))
				{
					if (!test.haveObstacle(diffPoint, tx.Pos))
					{
						refPoint = cal.CalPlaneIntersection(diffPoint, imageRx, refPlane.normal.x, 
							refPlane.normal.y, refPlane.normal.z, refPlane.D);
						if (0 == test.inPolygon(refPoint, p1, p2, p3, p4))
						{
							if (test.isSameSide(rx.Pos, refPoint, diffPoint, refPlane.normal))
							{
								if (!test.haveObstacle(refPoint, diffPoint) 
									&& !test.haveObstacle(refPoint, rx.Pos))
								{
									pathDiffRef.Add(tx.Pos);
									pathDiffRef.Add(diffPoint);
									pathDiffRef.Add(refPoint);
									pathDiffRef.Add(rx.Pos);
								}
							}
						}
					}
				}
			}
		}
	}
}


void CPathPowerCal::RefDiffRef()
{
	CurPos3D imageRx, imageTx;
	PolyEquation refTxPlane, refRxPlane;
	CurPos3D impossiblePoint = {INT_MIN, INT_MIN, INT_MIN};
	CurPos3D refTxPoint, refRxPoint, diffPoint;

	for (int i = 0; i <= test.txVisibleFace.GetCount() - 4; i += 4)
	{
		refTxPlane = cal.CalPlane(test.txVisibleFace[i], test.txVisibleFace[i + 1], 
			test.txVisibleFace[i + 2], test.txVisibleFace[i + 3]);
		imageTx = cal.CalImagePoint(tx.Pos, refTxPlane.normal.x, refTxPlane.normal.y, 
			refTxPlane.normal.z, refTxPlane.D);
		for (int j = 0; j <= test.rxVisibleFace.GetCount() - 4; j += 4)
		{
			refRxPlane = cal.CalPlane(test.rxVisibleFace[j], test.rxVisibleFace[j + 1], 
				test.rxVisibleFace[j + 2], test.rxVisibleFace[j + 3]);
			imageRx = cal.CalImagePoint(rx.Pos, refRxPlane.normal.x, refRxPlane.normal.y, 
				refRxPlane.normal.z, refRxPlane.D);
			for (int k = 0; k <= test.VertexSet.GetCount() - 2; k += 2)
			{
				if (0 == test.VertexSet[k].z && 0 == test.VertexSet[k + 1].z)
					continue;
				else
				{
					diffPoint = FindDiffractionPoint(imageTx, imageRx, 
						test.VertexSet[k], test.VertexSet[k + 1]);
					refTxPoint = cal.CalPlaneIntersection(diffPoint, imageTx, 
						refTxPlane.normal.x, refTxPlane.normal.y, refTxPlane.normal.z, refTxPlane.D);
					refRxPoint = cal.CalPlaneIntersection(diffPoint, imageRx,
						refRxPlane.normal.x, refRxPlane.normal.y, refRxPlane.normal.z, refRxPlane.D);
					if (0 == test.inPolygon(refTxPoint, test.txVisibleFace[i], test.txVisibleFace[i + 1], 
						test.txVisibleFace[i + 2], test.txVisibleFace[i + 3])
						&& 0 == test.inPolygon(refRxPoint, test.rxVisibleFace[j], test.rxVisibleFace[j + 1], 
						test.rxVisibleFace[j + 2], test.rxVisibleFace[j + 3]))
					{
						if (!test.isSamePoint(impossiblePoint, diffPoint))
						{
							if (test.isSameSide(tx.Pos, refTxPoint, diffPoint, refTxPlane.normal)
								&& test.isSameSide(diffPoint, refRxPoint, rx.Pos, refRxPlane.normal))
							{
								if (!test.haveObstacle(tx.Pos, refTxPoint)
									&& !test.haveObstacle(refTxPoint, diffPoint)
									&& !test.haveObstacle(diffPoint, refRxPoint)
									&& !test.haveObstacle(refRxPoint, rx.Pos))
								{

									pathRefDiffRef.Add(tx.Pos);
									pathRefDiffRef.Add(diffPoint);
									pathRefDiffRef.Add(refRxPoint);
									pathRefDiffRef.Add(rx.Pos);
								}
							}
						}
					}
				}
			}
		}
	}
}


GLfloat CPathPowerCal::CalDirectPower(CurPos3D startPos, CurPos3D endPos, GLfloat inputPower, GLfloat f)
{
	GLfloat d = cal.CalDistance(startPos, endPos);
	GLfloat ptw = pow(10, (inputPower - 30) / 10);//*******************
	assert(d > 0);
	//GLfloat dLos = 8.156f + 20 * log10(f) + 20 * log10(d / 1000);
	
	GLfloat dLos = 8.156f + 20 * log10(f) + 20 * log10(d)+ear.freqLos(f,tx.Time,d,env.Density,env.DescribeMode);//加大气station
	GLfloat prw = ptw / pow(10, dLos / 10);//******************
	GLfloat result=10 * log10(prw) + 30;
	return 10 * log10(prw) + 30;//*******************

	//GLfloat ptw = pow(10, (inputPower - 30) / 10);
	//GLfloat d = cal.CalDistance(startPos, endPos);
	//GLfloat E0 = sqrt(30 * ptw) / d;

	//return 10 * log10(E0) + 30;
}

GLfloat CPathPowerCal::CalReflectPower(CurPos3D startPos, CurPos3D refPos,CurPos3D endPos, GLfloat pIn)
{
	GLfloat pw = pow(10, (pIn - 30) / 10);
	Vec inLine = cal.CalVector(refPos, startPos);
	Vec outLine = cal.CalVector(refPos, endPos);
	GLfloat inAngle = cal.CalIncludedAngle(inLine, outLine) / 2;

	pw *= 0.5;
	//pw *= Random(pw);

	return 10 * log10(pw) + 30;
}

GLfloat CPathPowerCal::CalDiffactPower(CurPos3D startPos, CurPos3D diffPos, CurPos3D endPos, GLfloat pIn)
{
	GLfloat pw = pow(10, (pIn - 30) / 10);
	Vec inLine = cal.CalVector(diffPos, startPos);
	Vec outLine = cal.CalVector(diffPos, endPos);
	GLfloat inAngle = cal.CalIncludedAngle(inLine, outLine) / 2;
	
	pw *= 0.1f;
	//pw *= Random(pw);

	return 10 * log10(pw) + 30;
}


GLfloat CPathPowerCal::CalSumPower()
{
	CBasicCalculation cal;
	GLfloat tempPower = 0;
	GLfloat sumPower = 0;
	GLfloat prwDirect = 0;
	GLfloat prwOneRef = 0;
	GLfloat prwTwoRef = 0;
	GLfloat prwOneDiff = 0;
	GLfloat prwRefDiff = 0;
	GLfloat prwDiffRef = 0;
	GLfloat prwRedDiffRef = 0;
	GLfloat dis = 0, cosPhase = 0;

	//直射功率
	while (pathDirect.GetCount() != 0 
		&& indexDirect <= pathDirect.GetCount() - 2
		&& test.isSamePoint(pathDirect[indexDirect], tx.Pos))
	{
		tempPower = CalDirectPower(pathDirect[indexDirect], pathDirect[indexDirect + 1], 
			tx.InputPower, tx.CarrierFrequency);
		prwDirect = pow(10, (tempPower - 30) / 10);

		indexDirect += 2;
	}

	//一阶反射功率
	while (pathOneRef.GetCount() != 0 
		&& indexOneRef <= pathOneRef.GetCount() - 3
		&& test.isSamePoint(pathOneRef[indexOneRef], tx.Pos))
	{
		tempPower = CalDirectPower(pathOneRef[indexOneRef], pathOneRef[indexOneRef + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathOneRef[indexOneRef], pathOneRef[indexOneRef + 1], 
			pathOneRef[indexOneRef + 2], tempPower);
		tempPower = CalDirectPower(pathOneRef[indexOneRef + 1], pathOneRef[indexOneRef + 2], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwOneRef += tempPower;

		indexOneRef += 3;
	}

	//二阶反射功率
	while (pathTwoRef.GetCount() != 0 
		&& indexTwoRef <= pathTwoRef.GetCount() - 4
		&& test.isSamePoint(pathTwoRef[indexTwoRef], tx.Pos))
	{
		tempPower = CalDirectPower(pathTwoRef[indexTwoRef], pathTwoRef[indexTwoRef + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathTwoRef[indexTwoRef], pathTwoRef[indexTwoRef + 1], 
			pathTwoRef[indexTwoRef + 2], tempPower);
		tempPower = CalDirectPower(pathTwoRef[indexTwoRef + 1], pathTwoRef[indexTwoRef + 2], 
			tempPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathTwoRef[indexTwoRef + 1], pathTwoRef[indexTwoRef + 2], 
			pathTwoRef[indexTwoRef + 3], tempPower);
		tempPower = CalDirectPower(pathTwoRef[indexTwoRef + 2], pathTwoRef[indexTwoRef + 3], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwTwoRef += tempPower;

		indexTwoRef += 4;
	}

	//一阶绕射功率
	while (pathOneDiff.GetCount() != 0 
		&& indexOneDiff <= pathOneDiff.GetCount() - 3
		&& test.isSamePoint(pathOneDiff[indexOneDiff], tx.Pos))
	{
		tempPower = CalDirectPower(pathOneDiff[indexOneDiff], pathOneDiff[indexOneDiff + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalDiffactPower(pathOneDiff[indexOneDiff], pathOneDiff[indexOneDiff + 1], 
			pathOneDiff[indexOneDiff + 2], tempPower);
		tempPower = CalDirectPower(pathOneDiff[indexOneDiff + 1], pathOneDiff[indexOneDiff + 2], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwOneDiff += tempPower;

		indexOneDiff += 3;
	}

	//一反一绕功率
	while (pathRefDiff.GetCount() != 0 
		&& indexRefDiff <= pathRefDiff.GetCount() - 4
		&& test.isSamePoint(pathRefDiff[indexRefDiff], tx.Pos))
	{
		tempPower = CalDirectPower(pathRefDiff[indexRefDiff], pathRefDiff[indexRefDiff + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathRefDiff[indexRefDiff], pathRefDiff[indexRefDiff + 1], 
			pathRefDiff[indexRefDiff + 2], tempPower);
		tempPower = CalDirectPower(pathRefDiff[indexRefDiff + 1], pathRefDiff[indexRefDiff + 2], 
			tempPower, tx.CarrierFrequency);
		tempPower = CalDiffactPower(pathRefDiff[indexRefDiff + 1], pathRefDiff[indexRefDiff + 2], 
			pathRefDiff[indexRefDiff + 3], tempPower);
		tempPower = CalDirectPower(pathRefDiff[indexRefDiff + 2], pathRefDiff[indexRefDiff + 3], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwRefDiff += tempPower;

		indexRefDiff += 4;
	}

	//一绕一反功率
	while (pathDiffRef.GetCount() != 0 
		&& indexDiffRef <= pathDiffRef.GetCount() - 4
		&& test.isSamePoint(pathDiffRef[indexDiffRef], tx.Pos))
	{
		tempPower = CalDirectPower(pathDiffRef[indexDiffRef], pathDiffRef[indexDiffRef + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalDiffactPower(pathDiffRef[indexDiffRef], pathDiffRef[indexDiffRef + 1], 
			pathDiffRef[indexDiffRef + 2], tempPower);
		tempPower = CalDirectPower(pathDiffRef[indexDiffRef + 1], pathDiffRef[indexDiffRef + 2], 
			tempPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathDiffRef[indexDiffRef + 1], pathDiffRef[indexDiffRef + 2], 
			pathDiffRef[indexDiffRef + 3], tempPower);
		tempPower = CalDirectPower(pathDiffRef[indexDiffRef + 2], pathDiffRef[indexDiffRef + 3], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwDiffRef += tempPower;

		indexDiffRef += 4;
	}

	//一反一绕一反功率
	while (pathRefDiffRef.GetCount() != 0 
		&& indexRefDiffRef <= pathRefDiffRef.GetCount() - 5
		&& test.isSamePoint(pathRefDiffRef[indexRefDiffRef], tx.Pos))
	{
		tempPower = CalDirectPower(pathRefDiffRef[indexRefDiffRef], pathRefDiffRef[indexRefDiffRef + 1], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathRefDiffRef[indexRefDiffRef], pathRefDiffRef[indexRefDiffRef + 1], 
			pathRefDiffRef[indexRefDiffRef + 2], tempPower);
		tempPower = CalDirectPower(pathRefDiffRef[indexRefDiffRef + 1], pathRefDiffRef[indexRefDiffRef + 2], 
			tx.InputPower, tx.CarrierFrequency);
		tempPower = CalDiffactPower(pathRefDiffRef[indexRefDiffRef + 1], pathRefDiffRef[indexRefDiffRef + 2], 
			pathRefDiffRef[indexRefDiffRef + 3], tempPower);
		tempPower = CalDirectPower(pathRefDiffRef[indexRefDiffRef + 2], pathRefDiffRef[indexRefDiffRef + 3], 
			tempPower, tx.CarrierFrequency);
		tempPower = CalReflectPower(pathRefDiffRef[indexRefDiffRef + 2], pathRefDiffRef[indexRefDiffRef + 3], 
			pathRefDiffRef[indexRefDiffRef + 4], tempPower);
		tempPower = CalDirectPower(pathRefDiffRef[indexRefDiffRef + 3], pathRefDiffRef[indexRefDiffRef + 4], 
			tempPower, tx.CarrierFrequency);
		tempPower = pow(10, (tempPower - 30) / 10);

		prwRedDiffRef += tempPower;

		indexRefDiffRef += 5;
	}

	sumPower = prwDirect + prwOneRef + prwTwoRef + prwOneDiff + prwRefDiff + prwDiffRef + prwRedDiffRef;
	sumPower == 0? sumPower = INT_MIN: sumPower = 10 * log10(sumPower) + 30;
	return sumPower;
}



//GLfloat CPathPowerCal::CalSumPower()
//{
//	CBasicCalculation cal;
//	GLfloat tempPower = 0;
//	GLfloat sumPower = 0;
//	GLfloat prwDirect = 0;
//	GLfloat prwOneRef = 0;
//	GLfloat prwTwoRef = 0;
//	GLfloat prwOneDiff = 0;
//	GLfloat prwRefDiff = 0;
//	GLfloat prwDiffRef = 0;
//	GLfloat prwRedDiffRef = 0;
//	GLfloat dis = 0, cosPhase = 0;
//
//	//直射功率
//	if (!test.haveObstacle(tx.Pos, rx.Pos))
//	{
//		tempPower = CalDirectPower(tx.Pos, rx.Pos, tx.InputPower, tx.CarrierFrequency);
//		prwDirect = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//prwDirect *= cosPhase;
//	}
//
//	//一阶反射功率
//	for (int i = 0; i < pathOneRef.GetCount(); i++)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathOneRef[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(tx.Pos, pathOneRef[i], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathOneRef[i], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathOneRef[i]) + cal.CalDistance(pathOneRef[i], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwOneRef += tempPower;
//	}
//
//	//二阶反射功率
//	for (int i = 0; i <= pathTwoRef.GetCount() - 2; i += 2)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathTwoRef[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(tx.Pos, pathTwoRef[i], pathTwoRef[i + 1], tempPower);
//		tempPower = CalDirectPower(pathTwoRef[i], pathTwoRef[i + 1], tempPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(pathTwoRef[i], pathTwoRef[i + 1], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathTwoRef[i + 1], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathTwoRef[i]) + cal.CalDistance(pathTwoRef[i], pathTwoRef[i + 1]) 
//		//	+ cal.CalDistance(pathTwoRef[i + 1], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwTwoRef += tempPower;
//	}
//
//	//一阶绕射功率
//	for (int i = 0; i < pathOneDiff.GetCount(); i++)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathOneDiff[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalDiffactPower(tx.Pos, pathOneDiff[i], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathOneDiff[i], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathOneDiff[i]) + cal.CalDistance(pathOneDiff[i], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwOneDiff += tempPower;
//	}
//
//	//一反一绕功率
//	for (int i = 0; i <= pathRefDiff.GetCount() - 2; i += 2)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathRefDiff[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(tx.Pos, pathRefDiff[i], pathRefDiff[i + 1], tempPower);
//		tempPower = CalDirectPower(pathRefDiff[i], pathRefDiff[i + 1], tempPower, tx.CarrierFrequency);
//		tempPower = CalDiffactPower(pathRefDiff[i], pathRefDiff[i + 1], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathRefDiff[i + 1], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathRefDiff[i]) + cal.CalDistance(pathRefDiff[i], pathRefDiff[i + 1]) 
//		//	+ cal.CalDistance(pathRefDiff[i + 1], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwRefDiff += tempPower;
//	}
//
//	//一绕一反功率
//	for (int i = 0; i <= pathDiffRef.GetCount() - 2; i += 2)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathDiffRef[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalDiffactPower(tx.Pos, pathDiffRef[i], pathDiffRef[i + 1], tempPower);
//		tempPower = CalDirectPower(pathDiffRef[i], pathDiffRef[i + 1], tempPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(pathDiffRef[i], pathDiffRef[i + 1], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathDiffRef[i + 1], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathDiffRef[i]) + cal.CalDistance(pathDiffRef[i], pathDiffRef[i + 1]) 
//		//	+ cal.CalDistance(pathDiffRef[i + 1], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwDiffRef += tempPower;
//	}
//
//	//一反一绕一反功率
//	for (int i = 0; i <= pathRefDiffRef.GetCount() - 3; i += 3)
//	{
//		tempPower = CalDirectPower(tx.Pos, pathRefDiffRef[i], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(tx.Pos, pathRefDiffRef[i], pathRefDiffRef[i + 1], tempPower);
//		tempPower = CalDirectPower(pathRefDiffRef[i], pathRefDiffRef[i + 1], tx.InputPower, tx.CarrierFrequency);
//		tempPower = CalDiffactPower(pathRefDiffRef[i], pathRefDiffRef[i + 1], pathRefDiffRef[i + 2], tempPower);
//		tempPower = CalDirectPower(pathRefDiffRef[i + 1], pathRefDiffRef[i + 2], tempPower, tx.CarrierFrequency);
//		tempPower = CalReflectPower(pathRefDiffRef[i + 1], pathRefDiffRef[i + 2], rx.Pos, tempPower);
//		tempPower = CalDirectPower(pathRefDiffRef[i + 2], rx.Pos, tempPower, tx.CarrierFrequency);
//		tempPower = pow(10, (tempPower - 30) / 10);
//
//		//dis = cal.CalDistance(tx.Pos, pathDiffRef[i]) + cal.CalDistance(pathDiffRef[i], pathDiffRef[i + 1]) 
//		//	+ cal.CalDistance(pathDiffRef[i + 1], rx.Pos);
//		//cosPhase = CalPhase(dis, tx.CarrierFrequency);
//		//tempPower *= cosPhase;
//
//		prwRedDiffRef += tempPower;
//	}
//
//	sumPower = prwDirect + prwOneRef + prwTwoRef + prwOneDiff + prwRefDiff + prwDiffRef + prwRedDiffRef;
//	sumPower == 0? sumPower = INT_MIN: sumPower = 10 * log10(sumPower) + 30;
//	return sumPower;
//}


GLfloat CPathPowerCal::CalPhase(GLfloat dis, GLfloat carrierFrequence)
{
	GLfloat phase, cosPhase;
	phase = 2 * M_PI * carrierFrequence * 1000000 * (dis / C);
	cosPhase = cos(phase);

	return pow(cosPhase, 2);
}