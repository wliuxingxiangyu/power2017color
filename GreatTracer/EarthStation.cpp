#include "StdAfx.h"
#include "EarthStation.h"


EarthStation::EarthStation(void)
{
}


EarthStation::~EarthStation(void)
{
}

GLfloat EarthStation::atmosFreqTwo(GLfloat f)
{
	GLfloat a=1.5;
	GLfloat tempa=(1-1.2*pow(f,a)/100000)*2/10000;
	GLfloat tempb=4/((f-63)*(f-63)+0.936);
	GLfloat tempc=0.28/((f-118.75)*(f-118.75)+1.771);
	return (tempa+tempb+tempc)*f*f*6.24/1000;
}

GLfloat EarthStation::atmosFreqOne(GLfloat f)//rw
{
	GLfloat tempa=7.19/1000;
	GLfloat tempb=6.09/(f*f+0.227);
	GLfloat tempc=4.81/((f-57)*(f-57)+1.50);
	return (tempa+tempb+tempc)*f*f/1000;
}

GLfloat EarthStation::waterFreqOne(GLfloat f,GLfloat ro)
{
	GLfloat tempc=3.6/((f-22.2)*(f-22.2)+8.5);
	return (0.050+0.0021*ro+tempc)*f*f*ro/10000;
}

GLfloat EarthStation::waterFreqTwo(GLfloat f)//ro
{
	GLfloat b=0.5;
	GLfloat tempb=7.7*pow(f,b)/10000;
	return (0.039+tempb)*2.369*f*f/10000;
}

GLfloat EarthStation::landFreqOne(GLfloat f,GLfloat p1,GLfloat d)
{
	return 142.8+20*log10(f)+10*log10(p1)+0.1*d;
}

GLfloat EarthStation::seaFreqOne(GLfloat f,GLfloat p1,GLfloat d)
{
	GLfloat a=1.76;
	GLfloat b=0.393;
	GLfloat c=1.38;
	GLfloat cc=0.597;
	GLfloat tempa=49.91*log10(d+1840*pow(f,a));
	GLfloat tempb=1.195*pow(f,b)*pow(d,cc)*pow(log10(p1),c);
	GLfloat tempc=(0.01*d-70)*(f-0.1581);
	GLfloat tempd=(0.02-2*p1*p1/100000)*d;
	GLfloat tempe=9.72*d*d*p1*p1/1000000000;
	return tempa+tempb+tempc+tempd+tempe+20.2;
}

GLfloat EarthStation::seaFreqTwo(GLfloat f,GLfloat p1,GLfloat d)
{
	GLfloat a=1.58;
	GLfloat b=0.468;
	GLfloat c=2.598;
	GLfloat cc=0.453;
	GLfloat tempa=49.343*log10(d+1840*pow(f,a));
	GLfloat tempb=1.266*pow(d,cc)*pow(log(p1),b+c*f);
	GLfloat tempc=(0.037*d-70)*(f-0.1581);
	GLfloat tempd=1.95*d*d*p1*p1*p1/10000000000;
	return tempa+tempb+tempc+tempd+20.2;
}

GLfloat  EarthStation::ductLoss(GLfloat dc,GLfloat f)
{
	GLfloat cc=0.333;
	return 0.05*pow(f,cc)-6/(1+dc);
}

GLfloat EarthStation::minDistance(GLfloat f,GLfloat b)
{
	return 100+(b-f)*b/2;
}

GLfloat EarthStation::minFreqDistance(GLfloat f,GLfloat b)
{
	GLfloat tempDistance=0;
	if(f<40)
	{
		tempDistance=minDistance(40,b);
	}
	if(f>=40&&f<54)
	{
		tempDistance=((54-f)*minDistance(40,b)+10*(f-40))/14;
	}
	if(f>=54&&f<66)
	{
		tempDistance=10;
	}
	if(f>=66&&f<75)
	{
		tempDistance=((75-f)*10+45*(f-66))/9;
	}
	if(f>=75&&f<90)
	{
		tempDistance=45;
	}
	if(f>=90&&f<=105)
	{
		tempDistance=45-(f-90)/1.5;
	}
	return tempDistance;
}

GLfloat EarthStation::maxFreqDistance(GLfloat f,GLfloat p1)
{
	GLfloat tempDistance=0;
	if(f<=60)
	{
		tempDistance=1200;
	}
	if(f>60)
	{
		tempDistance=80-10*log10(p1/50);
	}
	return tempDistance;
}

GLfloat EarthStation::freqLos(GLfloat f,GLfloat p1,GLfloat d,GLfloat ro,int model)
{
	GLfloat Los=0;
	if(f>=0.1&&f<0.79){
		if(model==1)
		{
			Los=landFreqOne(f,p1,d)-(8.156f + 20 * log10(f) + 20 * log10(d));
		}
		if(model==2)
		{
			Los=seaFreqOne(f,p1,d)-(8.156f + 20 * log10(f) + 20 * log10(d));
		}
		if(model==3)
		{
			Los=seaFreqTwo(f,p1,d)-(8.156f + 20 * log10(f) + 20 * log10(d));
		}
	}
	if(f>=60&&f<105)
	{
		if(f>63.26)
		{
			Los=(atmosFreqTwo(f)+waterFreqTwo(f));
		}
		else
		{
			Los=(10+waterFreqTwo(f));
		}
	}
	if(f>=0.79&&f<60)
	{
		if(f>56.77)
		{
			Los=(atmosFreqOne(f)+waterFreqOne(f,ro))+ductLoss(0,f);
		}
		else
		{
			Los=(10+waterFreqOne(f,ro))+ductLoss(0,f);
		}
	}
	return Los;
}

GLfloat EarthStation::getBeita(GLfloat y)
{
	GLfloat a=0;
	if(abs(y)>1.8)
	{
	 a=abs(y)-1.8;
	}
	if(a<=70)
	{
		return pow(10,1.67-0.015*a);
	}
	if(a>70)
	{
		return 4.17;
	}
}

GLfloat EarthStation::getSin(CurPos3D tx,CurPos3D rx){
	GLfloat d=sqrt((rx.x-tx.x)*(rx.x-tx.x)+(rx.y-tx.y)*(rx.y-tx.y));
	return (rx.y-tx.y)/d;
}

GLfloat EarthStation::getCos(CurPos3D tx,CurPos3D rx){
	GLfloat d=sqrt((rx.x-tx.x)*(rx.x-tx.x)+(rx.y-tx.y)*(rx.y-tx.y));
	return (rx.x-tx.x)/d;
}

CurPos3D EarthStation::getRangePoint(CurPos3D tx,CArray <CurPos3D> &rx){
	GLfloat mind=INT_MAX;
	int index=0;
	for(int i=0;i<rx.GetCount();i++){
		GLfloat d=sqrt((rx[i].x-tx.x)*(rx[i].x-tx.x)+(rx[i].y-tx.y)*(rx[i].y-tx.y));
		if(d<mind){
			mind=d;
			index=i;
		}
	}
	return rx[index];
}


void EarthStation::getRange(CArray <TxInfo> &TxInfoSet,CArray <RxInfo> &RxInfoSet){
	//取点，分区12个区间，每个区选点，装箱
	//想一个合适的区间，用w统一规则
	//存放点顺序有问题，1可以定长数组对应索引放值，然后除空2初始化一个绝对不可能（比如int_max）的值然后修改这个值，取得被修改后的值
	GLfloat pi=3.141592653;
	GLfloat rangecount=0.000004;
	CurPos3D txPoint=TxInfoSet[0].Pos;
	CurPos3D temrxPoint[12];//预存边界点
	CArray <CurPos3D> rxPoint;
	GLfloat spower=pow(10, (TxInfoSet[0].InputPower - 30) / 10);
	for(int i=0;i<12;i++){
		temrxPoint[i].z=INT_MIN;
	}
	for(int i=0;i<RxInfoSet.GetCount();i++){
		RxInfoSet[i].ReceivedPower=pow(10, (RxInfoSet[i].ReceivedPower - 30) / 10);

	}
	for(int i=0;i< RxInfoSet.GetCount();i++){
		if(RxInfoSet[i].ReceivedPower<=spower*rangecount){
			rxPoint.Add(RxInfoSet[i].Pos);
		}
	}

	CArray <CurPos3D> rx0,rx1,rx2,rx3,rx4,rx5,rx6,rx7,rx8,rx9,rx10,rx11;
	for(int i=0;i<rxPoint.GetCount();i++){
		GLfloat tempSin=getSin(txPoint,rxPoint[i]);
		GLfloat tempCos=getCos(txPoint,rxPoint[i]);
		if(tempSin>=0&&tempSin<sin(pi/6)&&tempCos<=1&&tempCos>cos(pi/6)){
			rx0.Add(rxPoint[i]);
			CurPos3D rangePoint0=getRangePoint(txPoint,rx0);
			//Range.Add(rangePoint0);
			temrxPoint[0]=rangePoint0;
		}
		if(tempSin>=sin(pi/6)&&tempSin<sin(pi/3)&&tempCos<=cos(pi/6)&&tempCos>cos(pi/3)){
			rx1.Add(rxPoint[i]);
			CurPos3D rangePoint1=getRangePoint(txPoint,rx1);
			// Range.Add(rangePoint1);
			temrxPoint[1]=rangePoint1;
		}
		if(tempSin>=sin(pi/3)&&tempSin<sin(pi/2)&&tempCos<=cos(pi/3)&&tempCos>cos(pi/2)){
			rx2.Add(rxPoint[i]);
			CurPos3D rangePoint2=getRangePoint(txPoint,rx2);
			// Range.Add(rangePoint2);
			temrxPoint[2]=rangePoint2;
		}
		if(tempSin>sin(2*pi/3)&&tempSin<=sin(pi/2)&&tempCos<=cos(pi/2)&&tempCos>cos(2*pi/3)){
			rx3.Add(rxPoint[i]);
			CurPos3D rangePoint3=getRangePoint(txPoint,rx3);
			// Range.Add(rangePoint3);
			temrxPoint[3]=rangePoint3;
		}
		if(tempSin>sin(5*pi/6)&&tempSin<=sin(2*pi/3)&&tempCos<=cos(2*pi/3)&&tempCos>cos(5*pi/6)){
			rx4.Add(rxPoint[i]);
			CurPos3D rangePoint4=getRangePoint(txPoint,rx4);
			 //Range.Add(rangePoint4);
			temrxPoint[4]=rangePoint4;
		}
		if(tempSin>sin(pi)&&tempSin<=sin(5*pi/6)&&tempCos<=cos(5*pi/6)&&tempCos>cos(pi)){
			rx5.Add(rxPoint[i]);
			CurPos3D rangePoint5=getRangePoint(txPoint,rx5);
			// Range.Add(rangePoint5);
			 temrxPoint[5]=rangePoint5;
		}
		if(tempSin>sin(7*pi/6)&&tempSin<=sin(pi)&&tempCos<cos(7*pi/6)&&tempCos>=cos(pi)){
			rx6.Add(rxPoint[i]);
			CurPos3D rangePoint6=getRangePoint(txPoint,rx6);
			// Range.Add(rangePoint6);
			temrxPoint[6]=rangePoint6;
		}
		if(tempSin>sin(4*pi/3)&&tempSin<=sin(7*pi/6)&&tempCos<cos(4*pi/3)&&tempCos>=cos(7*pi/6)){
			rx7.Add(rxPoint[i]);
			CurPos3D rangePoint7=getRangePoint(txPoint,rx7);
			// Range.Add(rangePoint7);
			temrxPoint[7]=rangePoint7;
		}
		if(tempSin>sin(3*pi/2)&&tempSin<=sin(4*pi/3)&&tempCos<cos(3*pi/2)&&tempCos>=cos(4*pi/3)){
			rx8.Add(rxPoint[i]);
			CurPos3D rangePoint8=getRangePoint(txPoint,rx8);
			 //Range.Add(rangePoint8);
			temrxPoint[8]=rangePoint8;
		}
		if(tempSin>=sin(3*pi/2)&&tempSin<sin(5*pi/3)&&tempCos<cos(5*pi/3)&&tempCos>=cos(3*pi/2)){
			rx9.Add(rxPoint[i]);
			CurPos3D rangePoint9=getRangePoint(txPoint,rx9);
			// Range.Add(rangePoint9);
			temrxPoint[9]=rangePoint9;
		}
		if(tempSin>=sin(5*pi/3)&&tempSin<sin(11*pi/6)&&tempCos<cos(11*pi/6)&&tempCos>=cos(5*pi/3)){
			rx10.Add(rxPoint[i]);
			CurPos3D rangePoint10=getRangePoint(txPoint,rx10);
			// Range.Add(rangePoint10);
			temrxPoint[10]=rangePoint10;
		}
		if(tempSin>=sin(11*pi/6)&&tempSin<sin(2*pi)&&tempCos<cos(2*pi)&&tempCos>=cos(11*pi/6)){
			rx11.Add(rxPoint[i]);
			CurPos3D rangePoint11=getRangePoint(txPoint,rx11);
			// Range.Add(rangePoint11);
			temrxPoint[11]=rangePoint11;
		}
	}
	for(int i=0;i<12;i++){
		if(temrxPoint[i].z!=INT_MIN){
			Range.Add(temrxPoint[i]);
		}
	}

	
}
