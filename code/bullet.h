#pragma once
#define BULLET_SPEED 300.0f

class bullet
{
private:
	POINTF _pos;		//������
	RECT _rc;			//��Ʈ
	image* _img;		//�̹���
	bool _isRight;		//���⼺

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

