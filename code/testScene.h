#pragma once
#include "gameNode.h"

class player_Baleog;
class player_Olaf;
class player_Eric;


class testScene : public gameNode
{
private:

	image*			_pixelMap;			//여기다가 계속 맵데이터를 복사할것임 여기서 픽셀정보를 가져와서 판정할것.
	player_Baleog*	_baleog;
	player_Olaf*	_olaf;
	player_Eric*	_eric;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};