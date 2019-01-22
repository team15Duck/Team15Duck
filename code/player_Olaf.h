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
								
	float _accleration;			//가속도
	float _minSpeed;			//최저속도
	float _maxSpeed;			//최고속도
	float _shieldGravity;		//방패중력

public:
	player_Olaf();
	~player_Olaf();

	HRESULT init();
	void release();
	void update();

	void render();
	// ========== 키입력 ==========

	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;


	// ========== 올라프와 방패 ==========

	//올라프 초기화
	void initOlaf();

	//올라프 상태
	void stateOlaf();

	//방패 초기화
	void initShield();

	//방패 상태
	void stateShield();

	//방패 출력
	virtual void shieldRender(HDC hdc) override;

	//============ 애니메이션 ============

	//올라프 이미지초기화
	void initImgOlaf();

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



	// ========== GET & SET ==========


};