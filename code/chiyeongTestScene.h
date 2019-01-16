#pragma once
#include "gameNode.h"

class chiyeongTestScene : public gameNode
{
private:

public:
	chiyeongTestScene();
	~chiyeongTestScene();

	HRESULT init();
	void release();
	void update();
	void render();
};

