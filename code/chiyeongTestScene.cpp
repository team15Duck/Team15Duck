#include "stdafx.h"
#include "chiyeongTestScene.h"


chiyeongTestScene::chiyeongTestScene()
{
}


chiyeongTestScene::~chiyeongTestScene()
{
}

HRESULT chiyeongTestScene::init()
{
	_mainUI = new mainUI;
	_mainUI->init();
	return S_OK;
}

void chiyeongTestScene::release()
{
}

void chiyeongTestScene::update()
{
	_mainUI->update();
}

void chiyeongTestScene::render()
{
	_mainUI->render();
}
