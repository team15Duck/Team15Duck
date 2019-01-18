#pragma once
#include "playerBase.h"
class player_Baleog : public playerBase
{
private:

	//부서지는 벽 TEST할 임시 RECT
	RECT	_tempWall;
	//사다리 TEST할 임시 RECT
	RECT	_tempLadder;
	bool	_isLadder;


public:
	player_Baleog();
	~player_Baleog();

	HRESULT init();
	void release();
	void update();
	void render();



	//얘네는 공통적으로 작동되는거 이외에 작성하면됨
	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//플레이어 초기화 정보 함수
	void initBaleog();



	//좌우체크
	virtual void pixelLeftWallCollision() override;
	virtual void pixelRightWallCollision() override;

	virtual void rectBrokenWallCollision() override; // << 렉트 부숴지는 벽 충돌 

	//바닥체크
	virtual void pixelBottomCollision() override; // << 바닥 픽셀 충돌

};

