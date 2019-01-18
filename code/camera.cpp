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
	_distance = 0;
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
	_distance = 0;
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
	_distance = 0;
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

		//if (_angle == 0 || _angle == 90 || _angle == 180 || _angle == 270)
		//{
		//	_distance -= fabsf(dCosf(_angle) * CAMERA_SPEED * elpasedTime) + fabsf(-dSinf(_angle) * CAMERA_SPEED * elpasedTime);
		//	if (_distance < 5)
		//	{
		//		_mapMove = false;
		//		return;
		//	}
		//}
		
		POINTF cP;
		cP.x = _pos.x + WINSIZEX / 2;
		cP.y = _pos.y + 176;


		if (_angle == 90 || _angle == 270)
		{
			if (fabsf(cP.y - playerP.y) < 5)
			{
				_mapMove = false;
				return;
			}
		}

		if (_angle == 0 || _angle == 180)
		{
			if (fabsf(cP.x - playerP.x) < 5)
			{
				_mapMove = false;
				return;
			}
		}



		if (getDistance(cP, playerP) <= 5)
		{
			_mapMove = false;
			return;
		}


		if (_angle == 45)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_distance = getDistance(_centerPos, playerP);
				_angle = 90;
			}
			if (_centerPos.x + WINSIZEX / 2 > _mapSize.x - 5)
			{
				_pos.x = _mapSize.x - WINSIZEX;
				_distance = getDistance(_centerPos, playerP);
				_angle = 90;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_distance = getDistance(_centerPos, playerP);
				_angle = 0;
			}
			if (_centerPos.y - 176 < 5)
			{
				_pos.y = 0;
				_distance = getDistance(_centerPos, playerP);
				_angle = 0;
			}
		}
		else if (_angle == 135)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_distance = getDistance(_centerPos, playerP);
				_angle = 90;
			}
			if (_centerPos.x - WINSIZEX / 2 < 5)
			{
				_pos.x = 0;
				_distance = getDistance(_centerPos, playerP);
				_angle = 90;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_distance = getDistance(_centerPos, playerP);
				_angle = 180;
			}
			if (_centerPos.y - 176 < 5)
			{
				_pos.y = 0;
				_distance = getDistance(_centerPos, playerP);
				_angle = 180;
			}
		}
		else if (_angle == 225)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_distance = getDistance(_centerPos, playerP);
				_angle = 270;
			}
			if (_centerPos.x - WINSIZEX / 2 < 5)
			{
				_pos.x = 0;
				_distance = getDistance(_centerPos, playerP);
				_angle = 270;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_distance = getDistance(_centerPos, playerP);
				_angle = 180;
			}
			if (_centerPos.y + 176 + 128 > _mapSize.y - 5)
			{
				_pos.y = _mapSize.y - WINSIZEY;
				_distance = getDistance(_centerPos, playerP);
				_angle = 180;
			}
		}
		else if (_angle == 315)
		{
			if (fabsf(playerP.x - _centerPos.x) < 5)
			{
				_pos.x = playerP.x - WINSIZEX / 2;
				_distance = getDistance(_centerPos, playerP);
				_angle = 270;
			}
			if (_centerPos.x + WINSIZEX / 2 > _mapSize.x - 5)
			{
				_pos.x = _mapSize.x - WINSIZEX;
				_distance = getDistance(_centerPos, playerP);
				_angle = 270;
			}
			if (fabsf(playerP.y - _centerPos.y) < 5)
			{
				_pos.y = playerP.y - 176;
				_distance = getDistance(_centerPos, playerP);
				_angle = 0;
			}
			if (_centerPos.y + 176 + 128 > _mapSize.y - 5)
			{
				_pos.y = _mapSize.y - WINSIZEY;
				_distance = getDistance(_centerPos, playerP);
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

		//if (getDistance(_centerPos, playerP) < 5 ||
		//	((playerP.x < WINSIZEX / 2 && _pos.x < 5) && (playerP.y < 176 && _pos.y < 5)) ||																					//left top
		//	((playerP.x > _mapSize.x - WINSIZEX / 2 && _pos.x > _mapSize.x - WINSIZEX - 5) && (playerP.y < 176 && _pos.y < 5)) ||												//right top
		//	((playerP.x < WINSIZEX / 2 && _pos.x < 5) && (playerP.y > _mapSize.y - 128 - 176 && _pos.y > _mapSize.y - WINSIZEY - 5)) ||											//left bottom
		//	((playerP.x > _mapSize.x - WINSIZEX / 2 && _pos.x > _mapSize.x - WINSIZEX - 5) && (playerP.y > _mapSize.y - 128 - 176 && _pos.y > _mapSize.y - WINSIZEY - 5)) ||    //right bottom
		//	((playerP.y > _mapSize.y - 128 - 176 && _pos.y > _mapSize.y - WINSIZEY - 5) && getDistance(_centerPos, playerP) < 176 - 128) ||										//아래벽 + 거리
		//	((playerP.x < WINSIZEX / 2 && _pos.x < 5) && getDistance(_centerPos, playerP) < WINSIZEX / 2) ||																	//왼벽 + 거리
		//	((playerP.x > _mapSize.x - WINSIZEX / 2 && _pos.x > _mapSize.x - WINSIZEX - 5) && getDistance(_centerPos, playerP) < WINSIZEX / 2) ||								//오른벽 + 거리
		//	((playerP.y < 176 && _pos.y < 5) && getDistance(_centerPos, playerP) < 176))	
		//{
		//	_mapMove = false;
		//}
		//else
		//{
		//	if (!((playerP.x < WINSIZEX / 2 && _pos.x < 5) || (playerP.x > _mapSize.x - WINSIZEX / 2 && _pos.x > _mapSize.x - WINSIZEX - 5)))
		//	{
		//		_pos.x += dCosf(_angle) * CAMERA_SPEED * TIMEMANAGER->getElpasedTime();
		//	}
		//	if (!((playerP.y < 176 && _pos.y < 5) || (playerP.y > _mapSize.y - 128 - 176 && _pos.y > _mapSize.y - WINSIZEY - 5)))
		//	{
		//		_pos.y += -dSinf(_angle) * CAMERA_SPEED * TIMEMANAGER->getElpasedTime();
		//	}
		//}
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
