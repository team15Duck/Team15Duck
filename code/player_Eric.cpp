#include "stdafx.h"
#include "player_Eric.h"


player_Eric::player_Eric()
{
}


player_Eric::~player_Eric()
{
}


HRESULT player_Eric::init()
{
	_x = WINSIZEX / 2 + 200;
	_y = 1400;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{
	float posX = _x - CAMERA->getPosX();
	float posY = _y - CAMERA->getPosY();
	_playerRect = RectMakeCenter(posX, posY, 50, 70);
}


void player_Eric::render()
{
	
}


void player_Eric::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
}
