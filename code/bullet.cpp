#include "stdafx.h"
#include "bullet.h"


bullet::bullet()
{
}


bullet::~bullet()
{
}

HRESULT bullet::init(image * img, image * pixelData, bool isRight, POINTF p)
{

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
}

void bullet::render()
{
}

void bullet::move()
{
	if (_isRight)
	{
		//�����ʰ��� �̵�
	}
	else
	{
		//���ʰ��� �̵�
	}
}

void bullet::pixelCollition()
{
	if (_isRight)
	{
		//�����ʰ��� �ȼ��˻�
	}
	else
	{
		//���ʰ��� �ȼ��˻�
	}
}
