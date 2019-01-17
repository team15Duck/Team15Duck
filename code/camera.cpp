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
	return S_OK;
}

void camera::release()
{
	SAFE_RELEASE(_backBuffer);
	ReleaseDC(_hWnd, _hdc);
}

void camera::update()
{
	move();
}

void camera::render()
{
}

void camera::move()
{
	if (_mapMove)
	{
		POINTF cameraP, playerP;
		cameraP.x = _pos.x + WINSIZEX / 2;
		cameraP.y = _pos.y + 176;
		playerP.x = *_playerX;
		playerP.y = *_playerY;
		_angle = dGetAngle(playerP, cameraP);

		if (getDistance(cameraP, playerP) < 5 ||
			(playerP.x < WINSIZEX / 2 && _pos.x < 5) ||
			(playerP.x > _mapSize.x - WINSIZEX / 2 && _pos.x > _mapSize.x - WINSIZEX - 5) ||
			(playerP.y < 176 && _pos.y < 5) ||
			(playerP.y > _mapSize.y - 128 - 176 && _pos.y > _mapSize.y - WINSIZEY - 5))
		{
			_mapMove = false;
		}
		else
		{
			_pos.x +=  dCosf(_angle) * CAMERA_SPEED * TIMEMANAGER->getElpasedTime();
			_pos.y += -dSinf(_angle) * CAMERA_SPEED * TIMEMANAGER->getElpasedTime();
		}
	}
	else
	{
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
