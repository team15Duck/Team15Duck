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


	//얘네는 공통적으로 작동되는거 이외에 작성하면됨
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//화면밖으로 못나가게 하는 함수
	void moveRange();

	//좌우체크
	virtual void pixelHorizenWallCollision() override; // << 픽셀 벽 충돌 
	virtual void rectBrokenWallCollision() override; // << 렉트 부숴지는 벽 충돌 
	
	//바닥체크
	virtual void pixelBottomCollision() override; // << 바닥 픽셀 충돌

};

