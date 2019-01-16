#pragma once
#include "playerBase.h"
class player_Baleog :
	public playerBase
{
public:
	player_Baleog();
	~player_Baleog();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC cameraDC);
};

