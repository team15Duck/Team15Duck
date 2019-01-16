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
	_y = 1400;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	float posX = _x - CAMERA->getPosX();
	float posY = _y - CAMERA->getPosY();
	_playerRect = RectMakeCenter(posX, posY, 50, 70);
}

void player_Baleog::render()
{
	
}

void player_Baleog::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
}
