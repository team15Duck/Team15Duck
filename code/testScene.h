#pragma once
#include "gameNode.h"


class testScene : public gameNode
{
private:

	image* _pixelMap;			//����ٰ� ��� �ʵ����͸� �����Ұ��� ���⼭ �ȼ������� �����ͼ� �����Ұ�.



public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};