#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

	int _imgNum;
	float _alpha;
	bool _isBlack;
	
public:
	startScene();
	~startScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

