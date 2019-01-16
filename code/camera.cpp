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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_pos.x--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_pos.x++;
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_pos.y--;
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_pos.y++;
	}
}
