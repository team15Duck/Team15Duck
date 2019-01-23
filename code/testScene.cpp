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
	_vBullets.clear();

	IMAGEMANAGER->addImage("stage1PixelData", "image/stage1PixelData.bmp", 2048, 1528, false, RGB(255, 0, 255));
	_pixelMap = IMAGEMANAGER->addImage("stage1PixelMap", "image/stage1PixelMap.bmp", 2048, 1528, false, RGB(255, 0, 255));		//�̳༮�� ������ �����ͼ� ������ ��.

	IMAGEMANAGER->addImage("mapV2", "image/mapV2.bmp", 2048, 1528, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("mapV2Top", "image/mapV2_top.bmp", 2048, 1528, true, RGB(255, 0, 255));

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

	_em = new enemyManager;
	_em->init();

	_em->setPixelDataAdressLink(_pixelMap);
	_em->setPlayerManagerAdressLink(_pm);

	_pm->setPixelDataLink(_pixelMap);
	_pm->setMainUIAdressLink(_mainUI);
	_pm->setItemManagerLink(_itemManager);
	_pm->setObjectManagerLink(_objManager);

	_pm->getVPlayer()[PLAYER_NAME_ERIC]->setMainUILink(_mainUI);
	_pm->getVPlayer()[PLAYER_NAME_ERIC]->setObjectManagerAdressLink(_objManager);

	for (int i = 0; i < _objManager->getFieldLadders().size(); ++i)
	{
		RECT* adress = _objManager->getFieldLadders()[i]->getObjectRect();
		_pm->getVPlayer()[PLAYER_NAME_ERIC]->setLadderRectAdressLink(adress);
		_pm->getVPlayer()[PLAYER_NAME_BALEOG]->setLadderRectAdressLink(adress);
		_pm->getVPlayer()[PLAYER_NAME_OLAF]->setLadderRectAdressLink(adress);
	}

	for (int i = 0; i < _objManager->getFieldObjects().size(); ++i)
	{
		OBJECT_TYPE type = _objManager->getFieldObjects()[i]->geObjectType();

		if ((OBJECT_TYPE_LOCK_RED <= type) && (type <= OBJECT_TYPE_LOCK_BLUE))
		{
			object* adress = _objManager->getFieldObjects()[i];
			_pm->getVPlayer()[PLAYER_NAME_ERIC]->setObjectRectAdressLink(adress);
		}
	}


	// ������ �߻�Ǵ� �Ѿ�
	_fireTime = 0.f;
	_fireReloadTime = 2.5f;

	return S_OK;
}

void testScene::release()
{
	_itemManager->release();
	_objManager->release();
	_em->release();

	for (_iterBullet = _vBullets.begin(); _vBullets.end() != _iterBullet; )
	{
		bullet* blt = (*_iterBullet);
		{
			_iterBullet = _vBullets.erase(_iterBullet);

			SAFE_RELEASE(blt);
			SAFE_DELETE(blt);
		}
	}
	_vBullets.clear();
}

void testScene::update()
{
	CAMERA->update();

	_pm->keyPressCtrl();
	if (!_mainUI->getIsItemSelectOn())
	{
		_pm->update();
		_pm->keyUpdate();
		_em->update();
		_objManager->update();
	}
	_mainUI->update();
<<<<<<< HEAD
	_pm->uiKeyControl();
	
	
=======

	_objManager->update();
	_em->update();

	fireBullet();
	updateBullet();
>>>>>>> a3675cc7bb80312ccd84277f65d026b7769a5dcb
}

void testScene::render()
{
	IMAGEMANAGER->findImage("stage1PixelData")->render(_pixelMap->getMemDC());

	//--------------------------���и���� �׸��Ÿ� ���⼭ �׸���---------------------
	//pixelMap�� DC���ٰ� �׷��ٰ� ����Ÿ�� �ٴ��������ֱ�
	_pm->shieldPixelRender(_pixelMap->getMemDC());
	_objManager->objectPixelRender(_pixelMap->getMemDC());
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
	_objManager->render();
	_em->render();
	renderBullet();
	_pm->render();
	if (!KEYMANAGER->isToggleKey(VK_F6))
	{
		IMAGEMANAGER->findImage("mapV2Top")->render(CAMERA->getMemDC(), 0, 0);
	}

	_mainUI->render();

	char str[256];
	SetTextColor(CAMERA->getMemDC(), RGB(255, 255, 255));
	sprintf_s(str, "cameraposX : %.1f", CAMERA->getPosX());
	TextOut(CAMERA->getMemDC(), 0, 60, str, strlen(str));
	sprintf_s(str, "cameraposY : %.1f", CAMERA->getPosY());
	TextOut(CAMERA->getMemDC(), 0, 80, str, strlen(str));
	sprintf_s(str, "cameraAngle : %.1f", CAMERA->getAngle());
	TextOut(CAMERA->getMemDC(), 0, 100, str, strlen(str));
	//------------------------------------------------------------------------------
}

void testScene::fireBullet()
{
	_fireTime += TIMEMANAGER->getElpasedTime();
	if (_fireReloadTime <= _fireTime)
	{
		_fireTime = 0.f;

		bullet* blt = new bullet;
		POINTF pos = {1400.f, 970.f};
		image* bltImg = IMAGEMANAGER->findImage("bullet");
		blt->init2(bltImg, _pixelMap, false, pos);

		_vBullets.push_back(blt);
	}
}

void testScene::updateBullet()
{
	for (_iterBullet = _vBullets.begin(); _vBullets.end() != _iterBullet;)
	{
		bullet* blt = (*_iterBullet);
		if (blt->isAlive())
		{
			blt->update2();
			++_iterBullet;
		}
		else
		{
			_iterBullet = _vBullets.erase(_iterBullet);

			SAFE_RELEASE(blt);
			SAFE_DELETE(blt);
		}
	}
}

void testScene::renderBullet()
{
	vector<bullet*>::iterator end = _vBullets.end();
	for (_iterBullet = _vBullets.begin(); end != _iterBullet; ++_iterBullet)
	{
		(*_iterBullet)->render2();
	}
}
