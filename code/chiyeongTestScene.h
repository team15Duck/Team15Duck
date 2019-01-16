#pragma once
#include "gameNode.h"
#include "mainUI.h"

class chiyeongTestScene : public gameNode
{
private:
	mainUI* _mainUI;


public:
	chiyeongTestScene();
	~chiyeongTestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

