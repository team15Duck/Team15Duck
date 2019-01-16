#pragma once
#include "playerBase.h"
class player_Olaf :	public playerBase
{
public:
	player_Olaf();
	~player_Olaf();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC cameraDC);
};

