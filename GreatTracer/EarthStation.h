#pragma once
#include "ScaleVariable.h"
#include <math.h>

extern CArray <CurPos3D> Range;//范围边界点

class EarthStation
{
public:
	EarthStation(void);
	~EarthStation(void);
	GLfloat atmosFreqOne(GLfloat f);//790MHz--60GHz,其中小于56.77G的大气衰减
	GLfloat atmosFreqTwo(GLfloat f);//60GHz--105GHz,其中大于63.26G的大气衰减
	GLfloat waterFreqOne(GLfloat f,GLfloat ro);//790MHz--60GHz,水汽衰减
	GLfloat waterFreqTwo(GLfloat f);//60GHz--105GHz,水汽衰减
	GLfloat landFreqOne(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,陆地
	GLfloat seaFreqOne(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,冷海
	GLfloat seaFreqTwo(GLfloat f,GLfloat p1,GLfloat d);//100MHz--790MHz,暖海
	GLfloat ductLoss(GLfloat dc,GLfloat f);//大气波导
	GLfloat freqLos(GLfloat f,GLfloat p1,GLfloat d,GLfloat ro,int model);//分频率，分地区衰减
	GLfloat minDistance(GLfloat f,GLfloat b);//范围最小边界基本函数
	GLfloat minFreqDistance(GLfloat f,GLfloat b);//分频率，范围最小边界
	GLfloat maxFreqDistance(GLfloat f,GLfloat p1);//分频率，范围最大边界
	GLfloat getBeita(GLfloat y);//求参数b
	void getRange(CArray <TxInfo> &TxInfoSet,CArray <RxInfo> &RxInfoSet);//得到边界点
	GLfloat getSin(CurPos3D tx,CurPos3D rx);//求sin
	GLfloat getCos(CurPos3D tx,CurPos3D rx);//求cos
	CurPos3D getRangePoint(CurPos3D tx,CArray <CurPos3D> &rx);//取点1/12
	
};

