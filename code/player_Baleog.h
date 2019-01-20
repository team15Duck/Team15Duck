#pragma once
#include "playerBase.h"

//class objectManager;

class player_Baleog : public playerBase
{
private:
	bool			_isLadder;

	animation*		_playerAni;
	const char*		_imageKey;
	const char*		_aniImageKey;

	bool			_isChangeAni;
	bool			_isPushWall;


	//objectManager*	_object;

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


	//keyAni 이미지 출력할 함수
	void keyAniSetting();

	//사다리 충돌 체크할 함수
	//virtual void playerCollisionLadder(object* ladder) override;

	//링크할 함수
	//void setObjectAdderssLink(objectManager* obj) { _object = obj; }
};

