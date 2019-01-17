#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "objectManager.h"
#include "playerManager.h"
#include "mainUI.h"

#define STAGE1_MAPSIZEX 2048
#define STAGE1_MAPSIZEY 1528




class testScene : public gameNode
{
private:

	image*			_pixelMap;			//����ٰ� ��� �ʵ����͸� �����Ұ��� ���⼭ �ȼ������� �����ͼ� �����Ұ�.
	mainUI*			_mainUI;
	playerManager*	_pm;
	itemManager*	_itemManager;
	objectManager*	_objManager;

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};