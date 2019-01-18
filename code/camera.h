#pragma once
#include "singletonBase.h"
#include "backBuffer.h"


#define CAMERA_SPEED 300.0f

class camera : public singletonBase<camera>
{
private:
	HDC _hdc;
	POINTF _pos;			//카메라 위치할 포지션
	POINTF _centerPos;		//카메라 센터 포지션

	float* _playerX;		//카메라가 따라가야 할 포지션
	float* _playerY;		//카메라가 따라가야 할 포지션

	POINTF _mapSize;		//카메라가 이동할수 있는 최대 범위
	float _angle;
	bool _mapMove;
	backBuffer* _backBuffer;

	float _distance;

public:
	camera();
	~camera();

	HRESULT init();
	HRESULT init(float x, float y);
	HRESULT init(float x, float y, float mapSizeX, float mapSizeY);
	void release();
	void update();
	void render();
	void move();

	float getPosX() { return _pos.x; }
	float getPosY() { return _pos.y; }
	void setPosX(float x) { _pos.x = x; }
	void setPosY(float y) { _pos.y = y; }
	void setMaxMapSize(float x, float y) { _mapSize.x = x; _mapSize.y = y; }

	POINTF getCenterPos() { return _centerPos; }

	float getAngle() { return _angle; }
	void setAngle(float angle) { _angle = angle; }

	void setPlayerPosX(float* x) { _playerX = x; }
	void setPlayerPosY(float* y) { _playerY = y; }


	bool getMapMove() { return _mapMove; }
	void setMapMove(bool mapMove) { _mapMove = mapMove; }





	backBuffer* getBackBuffer() { return _backBuffer; }
	HDC getMemDC() { return _backBuffer->getMemDC(); }
	HDC getHDC() { return _hdc; }




};

