// GreatTracer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGreatTracerApp:
// �йش����ʵ�֣������ GreatTracer.cpp
//

class CGreatTracerApp : public CWinApp
{
public:
	CGreatTracerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGreatTracerApp theApp;