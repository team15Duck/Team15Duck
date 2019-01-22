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
	
	KEYANIMANAGER->addAnimationType("bullet");

	//ȭ���� �����϶�(������)
	int moveBulletRight[] = { 0 };
	KEYANIMANAGER->addArrayFrameAnimation("bullet", "moveBulletRight", "arrow", moveBulletRight, 1, 2, true);
	//ȭ���� �����϶�(����)
	int moveBulletLeft[] = { 4 };
	KEYANIMANAGER->addArrayFrameAnimation("bullet", "moveBulletLeft", "arrow", moveBulletLeft, 1, 2, true);
	//ȭ���� �ε����� ��(������)
	int brokenBulletRight[] = { 1, 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("bullet", "brokenBulletRight", "arrow", brokenBulletRight, 3, 8, false);
	//ȭ���� �ε����� ��(����)
	int brokenBulletLeft[] = { 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("bullet", "brokenBulletLeft", "arrow", brokenBulletLeft, 3, 8, false);

	if (isRight)
		_animation = KEYANIMANAGER->findAnimation("bullet", "moveBulletRight");
	else
		_animation = KEYANIMANAGER->findAnimation("bullet", "moveBulletLeft");

	//ȭ���� ���̳� ����� �ٴڿ� �������

	_pixelData = pixelData;

	_isRight = isRight;

	_pos.x = p.x;
	_pos.y = p.y;
	_bulletSpeed = BULLET_SPEED * TIMEMANAGER->getElpasedTime();
	_bulletRc = RectMakeCenter(_pos.x, _pos.y, ARROW_WIDTH, ARROW_HEIGHT);
	_isAlive = true;
	_isBroking = false;

	if (_animation)
		_animation->start();

	return S_OK;
}

void bullet::release()
{
}

void bullet::update()
{
	move();
	if (_isBroking)
	{
		KEYANIMANAGER->update("bullet");
		if (!_animation->isPlay())
		{
			_isAlive = false;
		}
	}
	_bulletRc = RectMakeCenter(_pos.x, _pos.y, ARROW_WIDTH, ARROW_HEIGHT);
}

void bullet::render()
{
	Rectangle(CAMERA->getMemDC(), _bulletRc, false);
	_bulletImage->aniRender(CAMERA->getMemDC(), _pos.x - _bulletImage->getFrameWidth() / 2, _pos.y - _bulletImage->getFrameHeight() / 2, _animation);
}


void bullet::move()
{
	pixelCollition();
	if (_isRight)
	{
		_pos.x += _bulletSpeed;
	}
	else
	{
		_pos.x -= _bulletSpeed;		
	}
}

void bullet::pixelCollition()
{
	if (_isBroking)
		return;

	if (_isRight)
	{
		//�����ʰ��� �ȼ��˻�	(��)
		for (int i = _bulletRc.right - 5; i < _bulletRc.right; ++i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _pos.y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 255 && b == 255) || (r == 255 && g == 0 && b == 255))
			{
				_isBroking = true;
				_bulletSpeed = 0.f;
				_animation = KEYANIMANAGER->findAnimation("bullet", "brokenBulletRight");
				_animation->start();
				break;
			}
		}
	}
	else
	{
		//���ʰ��� �ȼ��˻�(��)
		for (int i = _bulletRc.left + 5; i > _bulletRc.left; --i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _pos.y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (   (r == 0 && g == 255 && b == 255)
				|| (r == 255 && g == 0 && b == 255))
			{
				_isBroking = true;
				_bulletSpeed = 0.f;
				_animation = KEYANIMANAGER->findAnimation("bullet", "brokenBulletLeft");
				_animation->start();
				break;
			}
		}
	}
}
