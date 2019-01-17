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


	SCENEMANAGER->addScene("�׽�Ʈ��", new testScene);
	SCENEMANAGER->addScene("ġ���׽�Ʈ", new chiyeongTestScene);
	SCENEMANAGER->changeScene("�׽�Ʈ��");

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

