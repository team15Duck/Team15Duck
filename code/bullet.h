#pragma once
#define BULLET_SPEED 300.0f

class bullet
{
private:
	POINTF _pos;		//포지션
	RECT _rc;			//렉트
	image* _img;		//이미지
	bool _isRight;		//방향성

public:
	bullet();
	~bullet();

	HRESULT init(image* img, image* pixelData, bool isRight, POINTF p);
	void release();
	void update();
	void render();

	void move();
	void pixelCollition();

	POINTF getPos() { return _pos; }
	RECT getRect() { return _rc; }
};

