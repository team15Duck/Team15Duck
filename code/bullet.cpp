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
	_bulletImage = img;
	_pixelData = pixelData;

	_isRight = isRight;

	_pos.x = p.x;
	_pos.y = p.y;
	_bulletSpeed = BULLET_SPEED * TIMEMANAGER->getElpasedTime();
	_bulletRc = RectMakeCenter(_pos.x, _pos.y, ARROW_WIDTH, ARROW_HEIGHT);

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
	_bulletRc = RectMakeCenter(_pos.x, _pos.y, ARROW_WIDTH, ARROW_HEIGHT);
}

void bullet::render()
{
	Rectangle(CAMERA->getMemDC(), _bulletRc, false);
	//_
}

void bullet::move()
{
	if (_isRight)
	{
		pixelCollition();
		_pos.x += _bulletSpeed;
	}
	else
	{
		pixelCollition();
		_pos.x -= _bulletSpeed;		
	}
}

void bullet::pixelCollition()
{
	//if (_isRight)
	//{
	//	//오른쪽갈떄 픽셀검사
	//}
	//else
	//{
	//	//왼쪽갈때 픽셀검사
	//}
}
