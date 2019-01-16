#pragma once
#include "singletonBase.h"
#include "backBuffer.h"


#define CAMERA_SPEED 10.0f

class camera : public singletonBase<camera>
{
private:
	HDC _hdc;

	POINTF _pos;
	POINTF _mapSize;

	bool _mapMove;

	backBuffer* _backBuffer;


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



	bool getMapMove() { return _mapMove; }


	backBuffer* getBackBuffer() { return _backBuffer; }

	//DC Á¢±ÙÀÚ
	HDC getMemDC() { return _backBuffer->getMemDC(); }


	HDC getHDC() { return _hdc; }

};

