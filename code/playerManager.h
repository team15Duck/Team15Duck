#pragma once
#include "player_Baleog.h"
#include "player_Eric.h"
#include "player_Olaf.h"
#include <vector>



class playerManager
{
private:

	vector<playerBase*> _vPlayer;

	PLAYER_NAME _currentSelectPlayer;

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

	
};

