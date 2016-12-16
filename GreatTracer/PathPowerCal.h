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
	void LodaMapInfo(CArray<GLfloat> &originalMapData); //�����ͼ��Ϣ
	void LoadTxRxInfo(TxInfo txSet, RxInfo rxSet); //���뷢��������ջ�����
	void LoadTxInto(TxInfo txInfo);
	void LoadRxInfo(RxInfo rxInfo);
	void LoadEnvInfo(EnvironmentInfo envInfo);//���ش�����Ϣ
	void Direct(); //����ֱ��·��
	void OneReflection(); //����һ�׷���·��
	void TwoReflection(); //������׷���·��
	void OneDiffraction(); //����һ������·��
	void RefDiff(); //����һ��һ��·��
	void DiffRef(); //����һ��һ��·��
	void RefDiffRef(); //����һ��һ��һ��·��
	GLfloat CalPhase(GLfloat dis, GLfloat carrierFrequence); //���������,�Ѵ����ֵ��Ϊ�������
	GLfloat CalSumPower(); //������յ��ܹ���
	GLfloat CalDirectPower(CurPos3D startPos, CurPos3D endPos, GLfloat inputPower, GLfloat f); //����ֱ�䳡ǿ
	GLfloat CalReflectPower(CurPos3D startPos, CurPos3D refPos,CurPos3D endPos, GLfloat pIn); //���㷴�书��
	GLfloat CalDiffactPower(CurPos3D startPos, CurPos3D diffPos, CurPos3D endPos, GLfloat pIn); //�������书��
	CurPos3D FindDiffractionPoint(CurPos3D tx, CurPos3D rx, CurPos3D p1, CurPos3D p2); //���ַ�Ѱ���߶�p1p2�ϵ������
};

