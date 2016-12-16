#pragma once
#include "ScaleVariable.h"
#include <math.h>

extern CArray <CurPos3D> Range;//��Χ�߽��

class EarthStation
{
public:
	EarthStation(void);
	~EarthStation(void);
	GLfloat atmosFreqOne(GLfloat f);//790MHz--60GHz,����С��56.77G�Ĵ���˥��
	GLfloat atmosFreqTwo(GLfloat f);//60GHz--105GHz,���д���63.26G�Ĵ���˥��
	GLfloat waterFreqOne(GLfloat f,GLfloat ro);//790MHz--60GHz,ˮ��˥��
	GLfloat waterFreqTwo(GLfloat f);//60GHz--105GHz,ˮ��˥��
	GLfloat landFreqOne(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,½��
	GLfloat seaFreqOne(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,�亣
	GLfloat seaFreqTwo(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,ů��
	GLfloat ductLoss(GLfloat dc,GLfloat f);//��������
	GLfloat freqLos(GLfloat f,GLfloat p1,GLfloat d,GLfloat ro,int model);//��Ƶ�ʣ��ֵ���˥��
	GLfloat minDistance(GLfloat f,GLfloat b);//��Χ��С�߽��������
	GLfloat minFreqDistance(GLfloat f,GLfloat b);//��Ƶ�ʣ���Χ��С�߽�
	GLfloat maxFreqDistance(GLfloat f,GLfloat p1);//��Ƶ�ʣ���Χ���߽�
	GLfloat getBeita(GLfloat y);//�����b
	void getRange(CArray <TxInfo> &TxInfoSet,CArray <RxInfo> &RxInfoSet);//�õ��߽��
	GLfloat getSin(CurPos3D tx,CurPos3D rx);//��sin
	GLfloat getCos(CurPos3D tx,CurPos3D rx);//��cos
	CurPos3D getRangePoint(CurPos3D tx,CArray <CurPos3D> &rx);//ȡ��1/12
	
};

