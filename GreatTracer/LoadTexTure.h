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

	void DrawTextTure();//绘制纹理贴图
	int loadGLTextures();//载入纹理贴图
private:
	GLuint	texture[2];	//贴图数组
};
