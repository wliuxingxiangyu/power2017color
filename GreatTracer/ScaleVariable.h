#pragma once

#include "gl/gl.h"
#include "stdafx.h"

#define M_PI		3.14159265358979323846
#define THRESHOLD	0.00001

typedef struct{//��ά����
	GLdouble x,y,z;
}Vec3T;

typedef struct{//OpenGL����ϵ�еĶ�ά����
	GLfloat x;
	GLfloat y;
}CurPos2D;

typedef struct{//OpenGL����ϵ�е���ά����
	GLfloat x;
	GLfloat y;
	GLfloat z;
}CurPos3D, Vec;

typedef struct{
	CurPos3D P1;
	CurPos3D P2;
}line;

typedef struct{
	Vec normal;
	GLfloat D;
}PolyEquation;

typedef struct{
	CurPos3D P1;
	CurPos3D P2;
	CurPos3D P3;
	GLfloat normal[3];//������
}Triangle;

typedef struct{
	GLfloat red,green,blue;
}ColorRamp;

typedef struct{
	CurPos3D Pos1st;
	CurPos3D Pos2nd;
	CurPos3D Pos3rd;
	CurPos3D Pos4th;
	ColorRamp Color;
}RenderCell;

typedef struct{//���������
	CString Description;
	CurPos3D Pos;
	GLfloat InputPower;
	char Pola;
	GLfloat CarrierFrequency;
	int AntennaType;
	int WaveForm;
	GLfloat Lat;
	GLfloat Angle;
	GLfloat AllowLoss;
	GLfloat Time;
}TxInfo;

typedef struct{//���ջ�����
	CString Description;
	CurPos3D Pos;
	GLfloat Distance;
	GLfloat ReceivedPower;
	int ModulType;
	GLfloat Delay;
	GLfloat Phase;
	GLfloat RangeR;
}RxInfo;

typedef struct {//��������
	GLfloat StartRad;
	GLfloat EndRad;
	GLfloat PowerGain;//��������
	//��ӽ�ģ��صĲ���

}AntennaInfo;

typedef struct{
	int DescribeMode;
	GLfloat Density;
}EnvironmentInfo;

typedef struct{//��������
	int ModulType;//���Ʒ�ʽ

}ModualInfo;

class ScaleVariable
{
public:
	ScaleVariable(void);
	~ScaleVariable(void);
};
