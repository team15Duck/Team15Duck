#include "stdafx.h"
#include "startScene.h"


startScene::startScene()
{
}


startScene::~startScene()
{
}

HRESULT startScene::init()
{
	_imgNum = 0;
	_alpha = 255;
	_isBlack = false;
	IMAGEMANAGER->addImage("black", "image/black.bmp", 640, 480, false, RGB(255, 0, 255), true);
	IMAGEMANAGER->addImage("startImg1", "image/startImg1.bmp", 640, 480, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startImg2", "image/startImg2.bmp", 640, 480, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("startImg3", "image/startImg3.bmp", 640, 480, false, RGB(255, 0, 255));

	return S_OK;
}

void startScene::release()
{
}

void startScene::update()
{
	if (!_isBlack && _alpha > 0)
	{
		_alpha -= 2.125f;
	}
	if (_isBlack && _alpha < 255)
	{
		_alpha += 2.125f;
	}
	if (_imgNum < 2)
	{
		if (_alpha <= 0)
		{
			_isBlack = true;
		}
		
		if (_alpha >= 255)
		{
			_isBlack = false;
			_imgNum++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _imgNum == 2 && _alpha == 0)
	{
		_isBlack = true;
	}
	if (_isBlack && _alpha == 255 && _imgNum == 2)
	{
		SCENEMANAGER->changeScene("Å×½ºÆ®¾À");
	}
}

void startScene::render()
{
	if (_imgNum == 0)
	{
		IMAGEMANAGER->findImage("startImg1")->render(CAMERA->getMemDC(), 0, 0);
	}
	else if (_imgNum == 1)
	{
		IMAGEMANAGER->findImage("startImg2")->render(CAMERA->getMemDC(), 0, 0);
	}
	else if (_imgNum == 2)
	{
		IMAGEMANAGER->findImage("startImg3")->render(CAMERA->getMemDC(), 0, 0);
	}
	IMAGEMANAGER->findImage("black")->alphaRender(CAMERA->getMemDC(), 0, 0, _alpha);
}
