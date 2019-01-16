#pragma once
#include "playerBase.h"
class player_Eric :
	public playerBase
{
public:
	player_Eric();
	~player_Eric();
	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC cameraDC);
};

