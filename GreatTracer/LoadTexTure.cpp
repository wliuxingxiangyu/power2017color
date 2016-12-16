#include "StdAfx.h"
#include "LoadTexTure.h"

LoadTexTure::LoadTexTure(void)
{}

LoadTexTure::~LoadTexTure(void)
{}

AUX_RGBImageRec *LoadBMP(CString Filename){			

	CFile myFile;
	CFileFind cff;
	CFileException fileException;
	if (!myFile.Open(Filename,CFile::modeRead,&fileException)){
		//MessageBox(NULL,"Open Error!","Tips",MB_OK);
		if(fileException.m_cause==CFileException::badPath)
			MessageBox(NULL,"BAD PATH","tip",MB_OK);
		return NULL;
	}
	else{
		myFile.Close();
		return auxDIBImageLoad(Filename);
	}
}
int LoadTexTure::loadGLTextures(){
	int Status=FALSE;									
	AUX_RGBImageRec *TextureImage[2];					
	memset(TextureImage,0,sizeof(void *)*1);           
	if (TextureImage[0]=LoadBMP("..\\Debug\\bask.bmp")){
		Status=TRUE;									
		glGenTextures(1, & texture[0]);					
		glBindTexture(GL_TEXTURE_2D,  texture[0]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[0]->sizeX, TextureImage[0]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[0]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	//if (TextureImage[1]=LoadBMP(F:\\C#\\TEST\\Dlg\\xx\\Data\\board.bmp")){
	if (TextureImage[1]=LoadBMP("F:\\C#\\TEST\\GreatTracer3-8\\GreatTracer\\Debug\\board.bmp")){
		Status=TRUE;									
		glGenTextures(1, & texture[1]);					
		glBindTexture(GL_TEXTURE_2D,  texture[1]);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, TextureImage[1]->sizeX, TextureImage[1]->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, TextureImage[1]->data);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	}
	for(int i=0;i<2;i++){
		if (TextureImage[i]){							
			if (TextureImage[i]->data){					
				free(TextureImage[i]->data);			
			}
			free(TextureImage[i]);						
		}
	}
	return Status;		
}

void LoadTexTure::DrawTextTure(){
	if (!loadGLTextures()){
		MessageBox(NULL,"loadGLTextures Error!","Tips",MB_OK);// If Texture Didn't Load Return FALSE
		return;
	}
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glTranslatef(20.0f,0.0f,20.0f);

	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-64.0f-MapCenterX, -32.0f-MapCenterY, -0.0f);
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 64.0f-MapCenterX, -32.0f-MapCenterY, -0.0f);
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 64.0f-MapCenterX,  32.0f-MapCenterY, -0.0f);	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-64.0f-MapCenterX,  32.0f-MapCenterY, -0.0f);


	glEnd();

	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glTranslatef(60.0f,220.0f,0.0f);
	glBegin(GL_QUADS);
	glColor3f(1.0f,1.0f,1.0f);
	// Bottom Face
	glTexCoord2f(1.0f, 1.0f); glVertex3f(-50.0f-MapCenterX, -100.0f-MapCenterY,-0.0f );
	glTexCoord2f(0.0f, 1.0f); glVertex3f( 50.0f-MapCenterX, -100.0f-MapCenterY,-0.0f );
	glTexCoord2f(0.0f, 0.0f); glVertex3f( 50.0f-MapCenterX,  100.0f-MapCenterY,-0.0f );	
	glTexCoord2f(1.0f, 0.0f); glVertex3f(-50.0f-MapCenterX,  100.0f-MapCenterY,-0.0f );


	glEnd();
}