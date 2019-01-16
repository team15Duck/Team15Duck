#include "stdafx.h"
#include "playerBase.h"


playerBase::playerBase()
{
}


playerBase::~playerBase()
{
}

HRESULT playerBase::init()
{
	_proveBottom = (float)_playerRect.bottom;

	return S_OK;
}

void playerBase::release()
{
}

void playerBase::update()
{
}

void playerBase::render(HDC cameraDC)
{
	

}

void playerBase::keyUpdate()
{
	keyPressMove();
	keyPressSpace();
	keyPressD();
	keyPressE();
}

void playerBase::keyPressMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += _speed;
	}
	for (int i = _proveBottom - 70; i < _proveBottom + 70; ++i)
	{
		COLORREF color = GetPixel(IMAGEMANAGER->findImage("testMapData")->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetRValue(color);
		int b = GetRValue(color);

		if (r == 255, g == 0, b == 255)
		{
			_y = i - (_playerRect.top + (_playerRect.bottom - _playerRect.top) / 2);
			break;
		}
	}
}

void playerBase::keyPressSpace()
{
}

void playerBase::keyPressD()
{
}

void playerBase::keyPressE()
{
}

void playerBase::keyPressS()
{
}

void playerBase::keyPressCtrl()
{
}

void playerBase::keyPressTab()
{
}

void playerBase::pixelHorizenWallCollision()
{
}

void playerBase::rectBrokenWallCollision()
{
}

void playerBase::pixelTopWallCollision()
{
}

void playerBase::pixelBottomCollision()
{
}
