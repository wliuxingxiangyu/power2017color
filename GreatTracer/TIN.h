#pragma once
#include "stdafx.h"
#include "math.h"
#include "VIEWDLG.h"
#include "ScaleVariable.h"

extern CArray <CurPos3D> T1;
extern CArray <line> T2;
extern CArray <Triangle> T3;

class TIN
{
public:
	TIN(void);
	~TIN(void);

	void OnTin();
	void M_TIN(CurPos3D p1,CurPos3D p2);
	CurPos3D GetThirdPoint(CurPos3D p1,CurPos3D p2);
	bool IsLine(CurPos3D p1,CurPos3D p2);
	BOOL CalculateNormal();
	BOOL SetTextTure();

};
