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
		//오른쪽갈떄 이동
	}
	else
	{
		//왼쪽갈때 이동
	}
}

void bullet::pixelCollition()
{
	if (_isRight)
	{
		//오른쪽갈떄 픽셀검사
	}
	else
	{
		//왼쪽갈때 픽셀검사
	}
}
