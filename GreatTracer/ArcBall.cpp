//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////  
#include "stdafx.h"
#include <math.h>                                    
#include "ArcBall.h"                                 


void ArcBall_t::_mapToSphere(const Point2fT* NewPt, Vector3fT* NewVec) const
{
	Point2fT TempPt;
	GLfloat length;

	//���Ƶ���ʱ����
	TempPt = *NewPt;

	//�ѳ��������[-1 ... 1]����
	TempPt.s.X  =        (TempPt.s.X * this->AdjustWidth)  - 1.0f;
	TempPt.s.Y  = 1.0f - (TempPt.s.Y * this->AdjustHeight);

	//���㳤�ȵ�ƽ��
	length      = (TempPt.s.X * TempPt.s.X) + (TempPt.s.Y * TempPt.s.Y);

	//�����ӳ�䵽�������
	if (length > 1.0f)
	{
		GLfloat norm;

		//���ŵ�����
		norm    = 1.0f / FuncSqrt(length);

		//����z����Ϊ0
		NewVec->s.X = TempPt.s.X * norm;
		NewVec->s.Y = TempPt.s.Y * norm;
		NewVec->s.Z = 0.0f;
	}
	//���������
	else   
	{
		//���ð뾶��ƽ��Ϊ1,���z����
		NewVec->s.X = TempPt.s.X;
		NewVec->s.Y = TempPt.s.Y;
		NewVec->s.Z = FuncSqrt(1.0f - length);
	}
}

ArcBall_t::ArcBall_t(GLfloat NewWidth, GLfloat NewHeight)
{
	this->StVec.s.X     =0.0f;
	this->StVec.s.Y     = 0.0f;
	this->StVec.s.Z     = 0.0f;

	this->EnVec.s.X     =0.0f;
	this->EnVec.s.Y     = 0.0f;
	this->EnVec.s.Z     = 0.0f;


	Matrix4fSetIdentity(&Transform);
	Matrix3fSetIdentity(&LastRot);
	Matrix3fSetIdentity(&ThisRot);

	this->isDragging=false;
	this->isClicked= false;
	this->isRClicked = false;
	this->isZooming = false;
	this->zoomRate = 1;
	this->setBounds(NewWidth, NewHeight);
}

void ArcBall_t::upstate()
{
	if(!this->isZooming && this->isRClicked){                    // ��ʼ�϶�
		this->isZooming = true;                                  // �����϶�Ϊ����Ϊtrue        
		this->LastPt = this->MousePt;
		this->lastZoomRate = this->zoomRate;
	}
	else if(this->isZooming){//�����϶�
		if(this->isRClicked){                //�϶�        
			Point2fSub(&this->MousePt, &this->LastPt);
			this->zoomRate = this->lastZoomRate + this->MousePt.s.X * this->AdjustWidth * 2;
		}
		else{                                            //ֹͣ�϶�
			this->isZooming = false;
		}
	}
	else if (!this->isDragging && this->isClicked){                                                // ���û���϶�
		this->isDragging = true;                                        // �����϶�Ϊ����Ϊtrue
		this->LastRot = this->ThisRot;                                        
		this->click(&this->MousePt);                                
	}
	else if(this->isDragging){
		if (this->isClicked){                                            //�����ס�϶�
			Quat4fT ThisQuat;
			this->drag(&this->MousePt, &ThisQuat);                        // ���¹켣��ı���
			Matrix3fSetRotationFromQuat4f(&this->ThisRot, &ThisQuat);        // ������ת��
			Matrix3fMulMatrix3f(&this->ThisRot, &this->LastRot);                
			Matrix4fSetRotationFromMatrix3f(&this->Transform, &this->ThisRot);    
		}
		else                                                        // ����ſ���꣬�����϶�Ϊfalse
			this->isDragging = false;
	}
}
//�������,��¼��ǰ��Ӧ�Ĺ켣���λ��
void    ArcBall_t::click(const Point2fT* NewPt)
{
	this->_mapToSphere(NewPt, &this->StVec);
}

//����϶�,������ת��Ԫ��
void    ArcBall_t::drag(const Point2fT* NewPt, Quat4fT* NewRot)
{
	//�µ�λ��
	this->_mapToSphere(NewPt, &this->EnVec);

	//������ת
	if (NewRot){
		Vector3fT  Perp;

		//������ת��
		Vector3fCross(&Perp, &this->StVec, &this->EnVec);

		//�����Ϊ0
		if (Vector3fLength(&Perp) > Epsilon)    {
			//��¼��ת��
			NewRot->s.X = Perp.s.X;
			NewRot->s.Y = Perp.s.Y;
			NewRot->s.Z = Perp.s.Z;
			//����Ԫ����,w=cos(a/2)��aΪ��ת�ĽǶ�
			NewRot->s.W= Vector3fDot(&this->StVec, &this->EnVec);
		}
		//��0��˵��û����ת
		else{
			NewRot->s.X = 
				NewRot->s.Y = 
				NewRot->s.Z = 
				NewRot->s.W = 0.0f;
		}
	}
}