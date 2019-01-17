#include "stdafx.h"
#include "testScene.h"


testScene::testScene()
{
}


testScene::~testScene()
{
}

HRESULT testScene::init()
{
	IMAGEMANAGER->addImage("stage1PixelData", "image/stage1PixelData.bmp", 2048, 1528, false, RGB(255, 0, 255));
	_pixelMap = IMAGEMANAGER->addImage("stage1PixelMap", "image/stage1PixelMap.bmp", 2048, 1528, false, RGB(255, 0, 255));		//�̳༮�� ������ �����ͼ� ������ ��.

	IMAGEMANAGER->addImage("mapV2", "image/mapV2.bmp", 2048, 1528, false, RGB(255, 0, 255));

	CAMERA->setMaxMapSize(2048, 1528 + 128);
	
	_pm = new playerManager;
	_pm->init();

	CAMERA->setPosX(*_pm->getVPlayer()[PLAYER_NAME_ERIC]->getPosX());
	CAMERA->setPosY(*_pm->getVPlayer()[PLAYER_NAME_ERIC]->getPosY());

	_pm->getVPlayer()[PLAYER_NAME_ERIC]->setPixelDataLink(_pixelMap);
	_pm->getVPlayer()[PLAYER_NAME_BALEOG]->setPixelDataLink(_pixelMap);
	_pm->getVPlayer()[PLAYER_NAME_OLAF]->setPixelDataLink(_pixelMap);


	_itemManager = new itemManager;
	_itemManager->init();

	_objManager = new objectManager;
	_objManager->init();

	_mainUI = new mainUI;
	_mainUI->init();

	_pm->setMainUIAdressLink(_mainUI);
	_pm->setItemManagerLink(_itemManager);
	_pm->setObjectManagerLink(_objManager);
	return S_OK;
}

void testScene::release()
{
	_itemManager->release();
	_objManager->release();
}

void testScene::update()
{
	CAMERA->update();

	_pm->keyPressCtrl();

	_pm->update();

	//if (���� �ȴ�������)
	{
		_pm->keyUpdate();
	}
	
	_mainUI->update();

	_objManager->update();
}

void testScene::render()
{
	IMAGEMANAGER->findImage("stage1PixelData")->render(_pixelMap->getMemDC());

	//--------------------------���и���� �׸��Ÿ� ���⼭ �׸���---------------------
	//pixelMap�� DC���ٰ� �׷��ٰ� ����Ÿ�� �ٴ��������ֱ�
	_pm->shieldPixelRender();
	//------------------------------------------------------------------------------
	//-----------------------------������ ���⿡-------------------------------------
	//���ǻ��� : ���� �츮�� getMemDC()�� �׷��Խ��ϴ�
	//������ �츮�� ���� ī�޶� ������ ���� ������ CAMERA->getMemDC()�� �׸����� �սô�
	IMAGEMANAGER->findImage("mapV2")->render(CAMERA->getMemDC(), 0, 0);
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		_pixelMap->render(CAMERA->getMemDC(), 0, 0);
	}
	_itemManager->render();
	_objManager->render();;
	_pm->render();
	_mainUI->render();
	//------------------------------------------------------------------------------
}
