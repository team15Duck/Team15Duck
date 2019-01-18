#pragma once
#include "gameNode.h"

class startScene : public gameNode
{
private:

	int _imgNum;	//현재 그리고 있는 이미지 숫자
	float _alpha;	//알파값
	bool _isBlack;	//검은색으로칠할거니
	
public:
	startScene();
	~startScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

