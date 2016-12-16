#pragma once
#include "ScaleVariable.h"
#include "ScaleVariable.h"

extern CArray <CurPos3D> T1;
extern GLfloat MapCenterX,MapCenterY,MapCenterZ;

class ReadandWrite
{
public:
	ReadandWrite(void);
	~ReadandWrite(void);

	int ReadPointofTIN();

	

private:
	void DealString(CString temp);
};
