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
	_pixelMap = IMAGEMANAGER->addImage("stage1PixelMap", "image/stage1PixelMap.bmp", 2048, 1528, false, RGB(255, 0, 255));		//이녀석의 정보를 가져와서 판정할 것.

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

	for (int i = 0; i < _objManager->getFieldLadders().size(); ++i)
	{
		RECT* adress = _objManager->getFieldLadders()[i]->getObjectRect();
		_pm->getVPlayer()[PLAYER_NAME_ERIC]->setLadderRectAdressLink(adress);
		_pm->getVPlayer()[PLAYER_NAME_BALEOG]->setLadderRectAdressLink(adress);
		_pm->getVPlayer()[PLAYER_NAME_OLAF]->setLadderRectAdressLink(adress);
	}
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

	//if (탭을 안눌럿을때)
	{
		_pm->keyUpdate();
	}
	
	_mainUI->update();

	_objManager->update();
}

void testScene::render()
{
	IMAGEMANAGER->findImage("stage1PixelData")->render(_pixelMap->getMemDC());

	//--------------------------방패모양을 그릴거면 여기서 그릴것---------------------
	//pixelMap의 DC에다가 그려줄것 마젠타로 바닥판정해주기
	_pm->shieldPixelRender(_pixelMap->getMemDC());
	_objManager->objectPixelRender(_pixelMap->getMemDC());
	//------------------------------------------------------------------------------
	//-----------------------------렌더는 여기에-------------------------------------
	//주의사항 : 여태 우리는 getMemDC()에 그려왔습니다
	//하지만 우리는 이제 카메라 개념을 쓰기 때문에 CAMERA->getMemDC()에 그리도록 합시다
	IMAGEMANAGER->findImage("mapV2")->render(CAMERA->getMemDC(), 0, 0);
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		_pixelMap->render(CAMERA->getMemDC(), 0, 0);
	}
	_itemManager->render();
	_objManager->render();;
	_pm->render();
	_mainUI->render();


	char str[256];
	SetTextColor(CAMERA->getMemDC(), RGB(255, 255, 255));
	sprintf_s(str, "cameraposX : %.1f", CAMERA->getPosX());
	TextOut(CAMERA->getMemDC(), 0, 60, str, strlen(str));
	sprintf_s(str, "cameraposY : %.1f", CAMERA->getPosY());
	TextOut(CAMERA->getMemDC(),0, 80, str, strlen(str));
	sprintf_s(str, "cameraAngle : %.1f", CAMERA->getAngle());
	TextOut(CAMERA->getMemDC(), 0, 100, str, strlen(str));
	//------------------------------------------------------------------------------
}
