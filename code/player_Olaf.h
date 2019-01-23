#pragma once
#include "playerBase.h"
class player_Olaf : public playerBase
{
private:
	RECT _shield;				//옆일때 방패
	image* _pixelShield;		//방패를 위로 들었을때 픽셀충돌용
	animation* _olafMotion;		//올라프모션

	bool _isShieldUp;			//방패를 위로 들고있는지?
	bool _isLeftCollision;		//왼쪽 부딪혔는지?
	bool _isRightCollision;		//오른쪽 부딪혔는지?
	bool _isAniStart;			//모션 시작했는지?
	bool _isFloor;				//바닥인지?
	bool _isLadderBottom;		//사다리 밑인지?
	bool _isRightMotion;

	float _accleration;			//가속도
	float _minSpeed;			//최저속도
	float _maxSpeed;			//최고속도
	float _shieldGravity;		//방패중력

	float _specialTime;			//특수행동할 시간
	float _specialDelay;		//특수행동 딜레이

public:
	player_Olaf();
	~player_Olaf();

	HRESULT init();
	void release();
	void update();

	void render();
	//방패 출력
	virtual void shieldRender(HDC hdc) override;
	// ========== 키입력 ==========

	//부모꺼는 내가 쓴다
	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//상세키입력
	// 1. 방패 X + 사다리 X
	//   1) Right
	void noLadder_KeyRight();
	//	 2) Left
	void noLadder_KeyLeft();

	// 2. 방패 O + 사다리 O
	//   1) Up
	void ladder_KeyUp();
	//   2) Down
	void ladder_KeyDown();
	//   3) Right
	void ladder_KeyRight();
	//   4) Left
	void ladder_KeyLeft();

	// 3. 방패 O + 낙하 X + 사다리 X
	//   1)Right
	void noFall_Shield_KeyRight();
	//   2)Left
	void noFall_Shield_KeyLeft();

	// 4. 방패 O + 낙하 X + 사다리 O
	//   1)Up
	void noFall_Shield_KeyUp();
	//   2)Down
	void noFall_Shield_KeyDown();


	// 5. 방패 O + 낙하 O + 사다리 X
	//   1)Right
	void noLadder_Shield_KeyRight();
	//   2)Left
	void noLadder_Shield_KeyLeft();

	// 6. 방패 O + 낙하 O + 사다리 O
	//   1)Right
	void fall_Shield_KeyRight();
	//   2)Left
	void fall_Shield_KeyLeft();





	// ========== 올라프와 방패 ==========

	//올라프 초기화
	void initOlaf();
	//올라프 이미지초기화
	void initImgOlaf();
	//방패 초기화
	void initShield();

	//올라프 상태
	void stateOlaf();
	//올라프 특수모션
	void specialMotion_Olaf();
	//방패 상태
	void stateShield();
	//올라프 애니메이션
	void startAniOlaf(string aniKey);

	// ========== 충돌함수 ==========

	//좌우벽충돌(픽셀용)
	virtual void pixelLeftWallCollision() override;
	virtual void pixelRightWallCollision() override;

	//바닥충돌(픽셀용)
	virtual void pixelBottomCollision() override;

	//불충돌(픽셀용)
	void pixelFireCollision();

	//사다리충돌(렉트용)
	void playerCollisionLadder();

};