#pragma once
#define BULLET_SPEED 300.0f
#define ARROW_WIDTH 32
#define ARROW_HEIGHT 12

class playerBase;

class bullet
{
private:
	POINTF			_pos;			//화살의 중점좌표
	RECT			_bulletRc;		//화살 rect
	float			_bulletSpeed;	//스피드
	
	bool			_isRight;		//오른쪽임?
	bool			_isAlive;		// 살아있냐?
	
	image*			_bulletImage;	//화살 이미지
	image*			_pixelData;		//픽셀데이터


public:
	bullet();
	~bullet();
	/*
	void release();
	void update();
	void render();

	void move();
	void pixelCollition();

	POINTF getPos() { return _pos; }
	RECT getRect() { return _rc; }*/
	//HRESULT init(POINTF pos);
	
	HRESULT init(image* img, image* pixelData, bool isRight, POINTF p);
	void release();
	void update();
	void render();

	//void fire();
	void move();
	void pixelCollition();
	bool isAlive() { return _isAlive; }

	POINTF getPos() { return _pos; }
	RECT getRect() { return _bulletRc; }
	//image getBulletImage() { return _image; }
};

