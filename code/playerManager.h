#pragma once
#include "player_Baleog.h"
#include "player_Eric.h"
#include "player_Olaf.h"
#include <vector>

class mainUI;

class playerManager
{
private:

	vector<playerBase*> _vPlayer;

	PLAYER_NAME _currentSelectPlayer;


	mainUI* _mainUI;

public:
	playerManager();
	~playerManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyUpdate();
	void keyPressCtrl();


	vector<playerBase*> getVPlayer() { return _vPlayer; }

	void setMainUIAdressLink(mainUI* ui) { _mainUI = ui; }
};

