#include "stdafx.h"
#include "testScene.h"
#include "player_Baleog.h"
#include "player_Olaf.h"
#include "player_Eric.h"

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
	CAMERA->setPosY(1100);
	
	_baleog = new player_Baleog;
	_baleog->init();

	_olaf = new player_Olaf;
	_olaf->init();

	_eric = new player_Eric;
	_eric->init();

	_olaf->setPixelDataLink(_pixelMap);

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	CAMERA->update();
	_baleog->update();
	_baleog->keyUpdate();

	_olaf->update();
	_olaf->keyUpdate();

	_eric->update();
	_eric->keyUpdate();

}

void testScene::render()
{
	IMAGEMANAGER->findImage("stage1PixelData")->render(_pixelMap->getMemDC());

	//--------------------------방패모양을 그릴거면 여기서 그릴것---------------------
	//pixelMap의 DC에다가 그려줄것 마젠타로 바닥판정해주기

	

	//------------------------------------------------------------------------------
	//-----------------------------렌더는 여기에-------------------------------------
	//주의사항 : 여태 우리는 getMemDC()에 그려왔습니다
	//하지만 우리는 이제 카메라 개념을 쓰기 때문에 CAMERA->getMemDC()에 그리도록 합시다
	IMAGEMANAGER->findImage("mapV2")->render(CAMERA->getMemDC(), 0, 0);
	_baleog->render(CAMERA->getMemDC());
	_olaf->render(CAMERA->getMemDC());
	_eric->render(CAMERA->getMemDC());
	//------------------------------------------------------------------------------
}
