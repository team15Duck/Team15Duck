#pragma once
#include "playerBase.h"
class player_Baleog : public playerBase
{
private:
	

public:
	player_Baleog();
	~player_Baleog();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC cameraDC);

	
};

