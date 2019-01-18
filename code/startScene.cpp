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
	_imgNum = 0;		//처음그림부터그려야함
	_alpha = 255;		//처음엔 까매야함
	_isBlack = false;	//투명하게바꿔야함
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
	//검은색으로 그리지마 + 알파 > 0
	if (!_isBlack && _alpha > 0)
	{
		_alpha -= 2.125f; //투명하게해줌
	}
	//검은색으로칠해 + 알파 < 255
	if (_isBlack && _alpha < 255)
	{
		_alpha += 2.125f; //까맣게 해줌
	}

	//마지막이미지까지 못갔으면?
	if (_imgNum < 2)
	{
		if (_alpha <= 0)		//투명하면?
		{
			_isBlack = true;	//다시까맣게
		}
		if (_alpha >= 255)		//까맣다?
		{
			_imgNum++;			//다음이미지로 넘어가고
			_isBlack = false;	//다시투명하게
		}
	}

	//엔터키를 눌럿을때 + 마지막그림일때 + 검은색칠 안했을때
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN) && _imgNum == 2 && _alpha == 0)
	{
		_isBlack = true;	//까매져라
	}
	//까매져라    +  진짜 다칠했네  +   마지막그림이네
	if (_isBlack && _alpha == 255 && _imgNum == 2)
	{
		//게임시작
		SCENEMANAGER->changeScene("테스트씬");
	}
}

void startScene::render()
{
	//이미지 순서에따라 그려줌
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
	//페이드 인 아웃을 위한 검은색 이미지를 알파값에 따라 뿌려줌
	IMAGEMANAGER->findImage("black")->alphaRender(CAMERA->getMemDC(), 0, 0, _alpha);
}
