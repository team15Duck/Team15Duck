#pragma once
#include "gameNode.h"
#include "itemManager.h"
#include "objectManager.h"
#include "playerManager.h"
#include "enemyManager.h"
#include "mainUI.h"

#define STAGE1_MAPSIZEX 2048
#define STAGE1_MAPSIZEY 1528




class testScene : public gameNode
{
private:

	image*			_pixelMap;			//여기다가 계속 맵데이터를 복사할것임 여기서 픽셀정보를 가져와서 판정할것.
	mainUI*			_mainUI;
	playerManager*	_pm;
	itemManager*	_itemManager;
	objectManager*	_objManager;
	enemyManager*	_em;

	// 맵에서 쏘는 총알알알
	vector<bullet*> _vBullets;				// 총알들
	vector<bullet*>::iterator _iterBullet;	// iter
	float _fireTime;						// 발사 시각 카운트
	float _fireReloadTime;					// 발사 시각 리로드

public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();


private:
	// 총알 발싸아아
	void fireBullet();
	// 총알 업데이트
	void updateBullet();
	// 총알 렌더어
	void renderBullet();
};