#pragma once

#include "stdafx.h"
#include "gl/gl.h"
#include "gl/glu.h"
#include "gl/glaux.h"
#include "resource.h"
#include "ScaleVariable.h"

extern GLfloat MapCenterX,MapCenterY;
class LoadTexTure
{
public:
	LoadTexTure(void);
	~LoadTexTure(void);

	void DrawTextTure();//����������ͼ
	int loadGLTextures();//����������ͼ
private:
	GLuint	texture[2];	//��ͼ����
};
