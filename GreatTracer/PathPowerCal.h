#pragma once

#include "ScaleVariable.h"
#include "BasicCalculation.h"
#include "BasicTset.h"
#include "EarthStation.h"
#define C 300000000
#define random(x) (rand() % (x + 1) / x)

class CPathPowerCal
{
private:
	CBasicCalculation cal;
	CBasicTest test;
	TxInfo tx;
	RxInfo rx;
	EarthStation ear;
	EnvironmentInfo env;

public:
	CArray<CurPos3D> pathDirect;
	CArray<CurPos3D> pathOneRef;
	CArray<CurPos3D> pathTwoRef;
	CArray<CurPos3D> pathOneDiff;
	CArray<CurPos3D> pathRefDiff;
	CArray<CurPos3D> pathDiffRef;
	CArray<CurPos3D> pathRefDiffRef;

	int indexDirect;
	int indexOneRef;
	int indexTwoRef;
	int indexOneDiff;
	int indexRefDiff;
	int indexDiffRef;
	int indexRefDiffRef;

	GLfloat conductivity;
	GLfloat permittivity;
	//GLfloat powerDirect;
	//GLfloat powerOneRef;
	//GLfloat powerTwoRef;
	//GLfloat powerOneDiff;
	//GLfloat powerRefDiff;
	//GLfloat powerDiffRef;

	CPathPowerCal(void);
	~CPathPowerCal(void);
	void LoadInfo(CArray<TxInfo> &txSet, CArray<RxInfo> &rxSet, CArray<GLfloat> &originalMapData, CArray<EnvironmentInfo> &environment);
	void LodaMapInfo(CArray<GLfloat> &originalMapData); //载入地图信息
	void LoadTxRxInfo(TxInfo txSet, RxInfo rxSet); //载入发射机、接收机参数
	void LoadTxInto(TxInfo txInfo);
	void LoadRxInfo(RxInfo rxInfo);
	void LoadEnvInfo(EnvironmentInfo envInfo);//加载大气信息
	void Direct(); //计算直射路径
	void OneReflection(); //计算一阶反射路径
	void TwoReflection(); //计算二阶反射路径
	void OneDiffraction(); //计算一阶绕射路径
	void RefDiff(); //计算一反一绕路径
	void DiffRef(); //计算一绕一反路径
	void RefDiffRef(); //计算一反一绕一反路径
	GLfloat CalPhase(GLfloat dis, GLfloat carrierFrequence); //产生随机数,把传入的值作为随机种子
	GLfloat CalSumPower(); //计算接收点总功率
	GLfloat CalDirectPower(CurPos3D startPos, CurPos3D endPos, GLfloat inputPower, GLfloat f); //计算直射场强
	GLfloat CalReflectPower(CurPos3D startPos, CurPos3D refPos,CurPos3D endPos, GLfloat pIn); //计算反射功率
	GLfloat CalDiffactPower(CurPos3D startPos, CurPos3D diffPos, CurPos3D endPos, GLfloat pIn); //计算绕射功率
	CurPos3D FindDiffractionPoint(CurPos3D tx, CurPos3D rx, CurPos3D p1, CurPos3D p2); //二分法寻找线段p1p2上的绕射点
};

