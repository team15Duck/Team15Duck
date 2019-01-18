#include "stdafx.h"
#include "camera.h"


camera::camera()
{
}


camera::~camera()
{
}

HRESULT camera::init()
{
	_hdc = GetDC(_hWnd);
	_backBuffer = new backBuffer;
	_backBuffer->init(WINSIZEX, WINSIZEY);
	_mapMove = false;
	_pos.x = _pos.y = 0;
	_mapSize.x = WINSIZEX;
	_mapSize.y = WINSIZEY;
	_centerPos.x = 0;
	_centerPos.y = 0;
	return S_OK;
}

HRESULT camera::init(float x, float y)
{
	_hdc = GetDC(_hWnd);
	_backBuffer = new backBuffer;
	_backBuffer->init(WINSIZEX, WINSIZEY);
	_mapMove = false;
	_pos.x = x;
	_pos.y = y;
	_mapSize.x = WINSIZEX;
	_mapSize.y = WINSIZEY;
	_centerPos.x = 0;
	_centerPos.y = 0;
	return S_OK;
}

HRESULT camera::init(float x, float y, float mapSizeX, float mapSizeY)
{
	_hdc = GetDC(_hWnd);
	_backBuffer = new backBuffer;
	_backBuffer->init(WINSIZEX, WINSIZEY);
	_mapMove = false;
	_pos.x = x;
	_pos.y = y;
	_mapSize.x = mapSizeX;
	_mapSize.y = mapSizeY;
	_centerPos.x = 0;
	_centerPos.y = 0;
	return S_OK;
}

void camera::release()
{
	SAFE_RELEASE(_backBuffer);
	ReleaseDC(_hWnd, _hdc);
}

void camera::update()
{
	_centerPos.x = _pos.x + WINSIZEX / 2;
	_centerPos.y = _pos.y + 176;
	move();
}

void camera::render()
{
}

void camera::move()
{
	if (_mapMove)
	{
		POINTF playerP;
		playerP.x = *_playerX;
		playerP.y = *_playerY;
		

		float vecX, vecY;
		float elpasedTime = TIMEMANAGER->getElpasedTime();
		vecX = dCosf(_angle) * CAMERA_SPEED * elpasedTime;
		vecY = -dSinf(_angle) * CAMERA_SPEED * elpasedTime;

		_pos.x += vecX;
		_pos.y += vecY;

		if (_angle == 90 || _angle == 270)
		{
			if (fabsf(_centerPos.y - playerP.y) < 5)
			{
				_mapMove = false;
				return;
			}
		}
		if (_angle == 0 || _angle == 180)
		{
			if (fabsf(_centerPos.x - playerP.x) < 5)
			{
				_mapMove = false;
				return;
			}
		}
		if (getDistance(_centerPos, playerP) <= 5)
		{
			_mapMove = false;
			return;
		}


		if (_angle == 45)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_angle = 90;
			}
			if (_centerPos.x + WINSIZEX / 2 > _mapSize.x - 5)
			{
				_pos.x = _mapSize.x - WINSIZEX;
				_angle = 90;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_angle = 0;
			}
			if (_centerPos.y - 176 < 5)
			{
				_pos.y = 0;
				_angle = 0;
			}
		}
		else if (_angle == 135)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_angle = 90;
			}
			if (_centerPos.x - WINSIZEX / 2 < 5)
			{
				_pos.x = 0;
				_angle = 90;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_angle = 180;
			}
			if (_centerPos.y - 176 < 5)
			{
				_pos.y = 0;
				_angle = 180;
			}
		}
		else if (_angle == 225)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_angle = 270;
			}
			if (_centerPos.x - WINSIZEX / 2 < 5)
			{
				_pos.x = 0;
				_angle = 270;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_angle = 180;
			}
			if (_centerPos.y + 176 + 128 > _mapSize.y - 5)
			{
				_pos.y = _mapSize.y - WINSIZEY;
				_angle = 180;
			}
		}
		else if (_angle == 315)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_angle = 270;
			}
			if (_centerPos.x + WINSIZEX / 2 > _mapSize.x - 5)
			{
				_pos.x = _mapSize.x - WINSIZEX;
				_angle = 270;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_angle = 0;
			}
			if (_centerPos.y + 176 + 128 > _mapSize.y - 5)
			{
				_pos.y = _mapSize.y - WINSIZEY;
				_angle = 0;
			}
		}
		else if (_angle == 0)
		{
			if (_centerPos.x + WINSIZEX / 2 > _mapSize.x - 5)
			{
				_mapMove = false;
				return;
			}
		}
		else if (_angle == 90)
		{
			if (_centerPos.y - 176 < 5)
			{
				_mapMove = false;
				return;
			}
		}
		else if (_angle == 180)
		{
			if (_centerPos.x - WINSIZEX / 2 < 5)
			{
				_mapMove = false;
				return;
			}
		}
		else if (_angle == 270)
		{
			if (_centerPos.y + 176 + 128 > _mapSize.y - 5)
			{
				_mapMove = false;
				return;
			}
		}
	}
	else
	{
		_mapMove = false;
		_pos.x = *_playerX - WINSIZEX / 2;
		_pos.y = *_playerY - 176;

		if (_pos.x < 0)
		{
			_pos.x = 0;
		}
		if (_pos.x > _mapSize.x - WINSIZEX)
		{
			_pos.x = _mapSize.x - WINSIZEX;
		}
		if (_pos.y < 0)
		{
			_pos.y = 0;
		}
		if (_pos.y > _mapSize.y - WINSIZEY)
		{
			_pos.y = _mapSize.y - WINSIZEY;
		}
	}
}
