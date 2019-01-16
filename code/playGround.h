#pragma once
#include "gameNode.h"
#include "testScene.h"
#include "chiyeongTestScene.h"

class playGround : public gameNode
{
private:

public:
	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();


	playGround();
	~playGround();
};

