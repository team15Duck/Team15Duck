#include "stdafx.h"
#include "player_Baleog.h"


player_Baleog::player_Baleog()
{
}


player_Baleog::~player_Baleog()
{
}

HRESULT player_Baleog::init()
{
	_x = WINSIZEX/2;
	_y = 713;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//rect의 바텀이 proveBottom
	_proveBottom = (float)_playerRect.bottom + 5;
	_pixelData = IMAGEMANAGER->findImage("testMapPixelMap");

	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	pixelBottomCollision();
	_proveBottom = _playerRect.bottom + 5;
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Baleog::render()
{
	
}

void player_Baleog::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
}

void player_Baleog::keyPressSpace()
{
	//일반 공격
	//0 혹은 1 중에서 일정 확률로 0일 때는 가로 긋기, 1일 때는 세로 긋기
}

void player_Baleog::keyPressD()
{
	//활쏘기
}

void player_Baleog::pixelHorizenWallCollision()
{
	//양쪽 벽 충돌(픽셀충돌)

}

void player_Baleog::rectBrokenWallCollision()
{
	//부서지는 벽은 rect인데 그 벽이랑 부딪힌 경우
}

void player_Baleog::pixelBottomCollision()
{
	//바닥충돌처리(픽셀충돌)
	for (int i = _proveBottom - 5; i < _proveBottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetRValue(color);
		int b = GetRValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_y = i - (_playerRect.bottom - _playerRect.top) / 2;
			break;
		}
	}
}
