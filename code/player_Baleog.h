#pragma once
#include "playerBase.h"

//class objectManager;

class player_Baleog : public playerBase
{
private:

	animation*		_playerAni;
	const char*		_imageKey;
	const char*		_aniImageKey;

	float			_gravity;				//떨어질때 중력값이 필요해영


	bool			_isGround;				//바닥에 붙어있숑?
	bool			_isChangeAni;			//애니메이션 바뀜?
	bool			_isPushWall;			//벽 미는 중임?
	bool			_isLadder;				//사다리 탔음?
	bool			_isRight;				//사다리 올라가고 나서 나오는 아이들 모션때문에 들어간 bool 값



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

	//바닥체크
	virtual void pixelBottomCollision() override;	// << 바닥 픽셀 충돌

	virtual void pixelFireCollision();				// << 불과 부딪힌 경우 


	//virtual void rectBrokenWallCollision() override; // << 렉트 부숴지는 벽 충돌 

	//keyAni 이미지 출력할 함수
	void keyAniSetting();

	//사다리 충돌 체크할 함수
	virtual void collisionLadder(vector<RECT*> ladder);
	virtual void attackKey();

	//링크할 함수
	//void setObjectAdderssLink(objectManager* obj) { _object = obj; }
};

