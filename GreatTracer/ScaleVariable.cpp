#include "StdAfx.h"
#include "ScaleVariable.h"

CArray <GLfloat> CubeVertex_Tx;//�շ��Ż���С����������
CArray <GLfloat> CubeVertex_Rx;

CArray <GLfloat> RenderArray;//�����Ⱦ��Ϣ������

CArray <GLfloat> DirectPath; //ֱ��·��
CArray <GLfloat> OneReflection;//һ�׷���
CArray <GLfloat> TwoReflection;//���׷���
CArray <GLfloat> OneDiffraction;//һ������
CArray <GLfloat> TwoDiffraction;//��������
CArray <GLfloat> ReflectionToDiffraction;//һ��һ��
CArray <GLfloat> DiffractionToReflection;//һ��һ��
CArray <GLfloat> TwoReflectionToDiffraction;//����һ��
CArray <GLfloat> ReflectionToTwoDiffraction;//һ������
CArray <GLfloat> TwoDiffractionToReflection;//����һ��
CArray <GLfloat> DiffractionToTwoReflection;//һ������
CArray <GLfloat> TwoReflectionToTwoDiffraction;//��������

CArray <Vec3T> GLBoundaryPoint;//����ջ��ı߽���OpenGL�е�����
CArray <CPoint> ScrBoundaryPoint;//����ջ��ı߽�����Ļ�ϵ�����


CArray <RxInfo> RxInfoSet;//���ջ�����
CArray <TxInfo> TxInfoSet;//���������

CArray <AntennaInfo> AnteInfo;//������Ϣ
CArray <ModualInfo> ModualWay;//���Է�ʽ��Ϣ
CArray <EnvironmentInfo> EnvInfo;//����������Ϣ

CArray<CurPos3D>T1;//���TIN�ĵ�
CArray<line>T2;//���TIN����
CArray<Triangle>T3;//���TIN��������

GLfloat MapCenterX,MapCenterY,MapCenterZ;//��ͼ����TIN�����ĵ㣬Ϊ�˱�֤��ͼ�����ͼ����
GLfloat Rmin,Rmax;//Э������Χ�߽�
CArray <CurPos3D> Range;//��Χ�߽��

ScaleVariable::ScaleVariable(void)
{
}

ScaleVariable::~ScaleVariable(void)
{
}
