#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{
}


HRESULT playGround::init()
{
	gameNode::init(true);


	SCENEMANAGER->addScene("테스트씬", new testScene);
	SCENEMANAGER->addScene("치영테스트", new chiyeongTestScene);
	SCENEMANAGER->changeScene("테스트씬");

	return S_OK;
}


void playGround::release()
{
	gameNode::release();

	SCENEMANAGER->release();
}


void playGround::update()
{
	gameNode::update();
	SCENEMANAGER->update();

}



void playGround::render()
{
	PatBlt(CAMERA->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);

	SCENEMANAGER->render();
	


	TIMEMANAGER->render(CAMERA->getMemDC());
	//===========================================================
	CAMERA->getBackBuffer()->render(CAMERA->getHDC(), 0, 0);
}

