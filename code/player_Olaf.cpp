#include "stdafx.h"
#include "player_Olaf.h"


player_Olaf::player_Olaf()
{
}


player_Olaf::~player_Olaf()
{
}

HRESULT player_Olaf::init()
{
	
	return S_OK;
}

void player_Olaf::release()
{
}

void player_Olaf::update()
{
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Olaf::render()
{
}

void player_Olaf::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
}

void player_Olaf::initOlaf()
{
	_x = WINSIZEX / 2 + 100;
	_y = 1400;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Olaf::initShield()
{
}

void player_Olaf::pixelHorizenWallCollision()
{
	
}

void player_Olaf::rectBrokenWallCollision()
{


}

void player_Olaf::pixelBottomCollision()
{
	for (int i = _proveBottom - 50; i < _proveBottom + 50; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			_y = i - (_playerRect.top + (_playerRect.bottom - _playerRect.top) / 2);
			break;
		}
	}

	_proveBottom = _y + (_playerRect.bottom - _playerRect.top) / 2;
	_playerRect = RectMakeCenter(_x, _y, 50, 70);

}
