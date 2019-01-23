#pragma once
#include "player_Baleog.h"
#include "player_Eric.h"
#include "player_Olaf.h"
#include "bullet.h"
#include <vector>

class mainUI;
class itemManager;
class objectManager;
class enemyManager;

class playerManager
{
private:

	vector<playerBase*> _vPlayer;

	PLAYER_NAME			_currentSelectPlayer;

	bullet*				_arrow;
	mainUI*				_mainUI;
	itemManager*		_im;
	objectManager*		_om;
	enemyManager*		_em;

	image*				_pixelData;

	vector<bullet*>		_vArrow;

	int _itemSelectNum;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void shieldPixelRender(HDC hdc);

	void keyUpdate();
	void keyPressCtrl();
	void attackKey();
	void colArrowEnemy();
	void colEnemyPlayer();
	void uiKeyControl();



	vector<playerBase*> getVPlayer() { return _vPlayer; }

	void setMainUIAdressLink(mainUI* ui) { _mainUI = ui; }
	void setItemManagerLink(itemManager* im) { _im = im; }
	void setObjectManagerLink(objectManager* om) { _om = om; }
	void setEnemyManagerLink(enemyManager* em) { _em = em; }


	void setPixelDataLink(image* pixelData) { _pixelData = pixelData; }

};

