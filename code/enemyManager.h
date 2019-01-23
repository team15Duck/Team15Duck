#pragma once
#include "enemy.h"
#include "bullet.h"

class playerManager;

class enemyManager
{
private:
	vector<enemy*> _vEnemy;			//적 저장할 벡터
	vector<bullet*> _vBullet;		//적총알 저장할 벡터

	playerManager* _pm;
	image* _pixelData;		

public:
	enemyManager();
	~enemyManager();
	
	HRESULT init();
	void release();
	void update();
	void render();

	vector<enemy*> getVEnemy() { return _vEnemy; }

	void setPlayerManagerAdressLink(playerManager* pm) { _pm = pm; }
	void setPixelDataAdressLink(image* pixelData) { _pixelData = pixelData; }


};

