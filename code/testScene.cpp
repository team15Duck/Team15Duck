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
	IMAGEMANAGER->addImage("testMapData", "image/mapDataImage.bmp", 2000, 1000, false, RGB(255, 0, 255));
	_pixelMap = IMAGEMANAGER->addImage("testMapPixelMap", "image/pixelMap.bmp", 2000, 1000, false, RGB(255, 0, 255));		//이녀석의 정보를 가져와서 판정할 것.

	IMAGEMANAGER->addImage("mapV2", "image/mapV2.bmp", 2048, 1528, false, RGB(255, 0, 255));

	CAMERA->setMaxMapSize(2048, 1728);
	CAMERA->setPosY(1200);

	return S_OK;
}

void testScene::release()
{
}

void testScene::update()
{
	CAMERA->update();
	
}

void testScene::render()
{
	IMAGEMANAGER->findImage("testMapData")->render(_pixelMap->getMemDC());

	//--------------------------방패모양을 그릴거면 여기서 그릴것---------------------
	//pixelMap의 DC에다가 그려줄것 마젠타로 바닥판정해주기

	

	//------------------------------------------------------------------------------
	//-----------------------------렌더는 여기에-------------------------------------
	//주의사항 : 여태 우리는 getMemDC()에 그려왔습니다
	//하지만 우리는 이제 카메라 개념을 쓰기 때문에 CAMERA->getMemDC()에 그리도록 합시다
	IMAGEMANAGER->findImage("mapV2")->render(CAMERA->getMemDC(), 0, 0);

	//------------------------------------------------------------------------------
}
