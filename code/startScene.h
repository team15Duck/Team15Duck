#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

	int _imgNum;	//���� �׸��� �ִ� �̹��� ����
	float _alpha;	//���İ�
	bool _isBlack;	//����������ĥ�ҰŴ�
	
public:
	startScene();
	~startScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

