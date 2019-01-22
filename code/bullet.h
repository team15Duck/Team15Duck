#pragma once
#define BULLET_SPEED 300.0f
#define ARROW_WIDTH 32
#define ARROW_HEIGHT 12

class playerBase;

class bullet
{
private:
	POINTF			_pos;			//ȭ���� ������ǥ
	RECT			_bulletRc;		//ȭ�� rect
	float			_bulletSpeed;	//���ǵ�
	
	bool			_isRight;		//��������?
	bool			_isAlive;		//����ֳ�?
	bool			_isBroking;		//�μ������ִ�?

	image*			_bulletImage;	//ȭ�� �̹���
	image*			_pixelData;		//�ȼ�������
	animation*		_animation;

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
	HRESULT init2(image* img, image* pixelData, bool isRight, POINTF p);
	void release();
	void update();
	void update2();
	void render();
	void render2();

	//void fire();
	void move();
	void move2();
	void pixelCollition();
	void pixelCollition2();
	bool isAlive() { return _isAlive; }

	POINTF getPos() { return _pos; }
	RECT getRect() { return _bulletRc; }
	//image getBulletImage() { return _image; }
};

