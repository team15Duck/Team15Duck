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
	_pixelMap = IMAGEMANAGER->addImage("testMapPixelMap", "image/pixelMap.bmp", 2000, 1000, false, RGB(255, 0, 255));		//�̳༮�� ������ �����ͼ� ������ ��.

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

	//--------------------------���и���� �׸��Ÿ� ���⼭ �׸���---------------------
	//pixelMap�� DC���ٰ� �׷��ٰ� ����Ÿ�� �ٴ��������ֱ�

	

	//------------------------------------------------------------------------------
	//-----------------------------������ ���⿡-------------------------------------
	//���ǻ��� : ���� �츮�� getMemDC()�� �׷��Խ��ϴ�
	//������ �츮�� ���� ī�޶� ������ ���� ������ CAMERA->getMemDC()�� �׸����� �սô�
	IMAGEMANAGER->findImage("mapV2")->render(CAMERA->getMemDC(), 0, 0);

	//------------------------------------------------------------------------------
}
