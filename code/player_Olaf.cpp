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
	_x = WINSIZEX / 2 + 100;
	_y = 1400;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	return S_OK;
}

void player_Olaf::release()
{
}

void player_Olaf::update()
{
	float posX = _x - CAMERA->getPosX();
	float posY = _y - CAMERA->getPosY();
	_playerRect = RectMakeCenter(posX, posY, 50, 70);
}

void player_Olaf::render()
{
}

void player_Olaf::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
}
