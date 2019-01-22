#pragma once
#include "playerBase.h"


class player_Baleog : public playerBase
{
private:
	animation*		_playerAni;
	const char*		_imageKey;
	const char*		_aniImageKey;

	//float			_gravity;				//떨어질때 중력값이 필요해영
	float			_acceleration;			//가속도
	float			_minSpeed;				//최저속도
	float			_maxSpeed;				//최고속도

	float			_fallStartY;			//떨어지기 시작할때 높이를 저장할 변수
	float			_curFallingY;				//착지한 곳의 높이	
	float			_damageHeight;			//데미지를 입는 높이


	bool			_isGround;				//바닥에 붙어있숑?
	bool			_isChangeAni;			//애니메이션 바뀜?
	bool			_isPushWall;			//벽 미는 중임?
	bool			_isLadder;				//사다리 탔음?
	//bool			_isLadderDownEnd;		//사다리 아래쪽임?

	bool			_isRight;				//사다리 올라가고 나서 나오는 아이들 모션때문에 들어간 bool 값
	bool			_isFire;				//발사했냐?

	int				_ladderIndex;			//충돌된 사다리 인덱스 번호

	

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

	virtual bool getIsAttackRight() override;
	virtual bool getIsFire() override;
	virtual void setIsFire(bool isFire) override;
	
};

