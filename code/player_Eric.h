#pragma once
#include "playerBase.h"
class player_Eric : public playerBase
{
private:
	float _jumpPower;

	bool _isJump;       //점프 체크용
	bool _isRCollision;	//오른쪽 충돌 체크용 
	bool _isLCollision;	//왼쪽 충돌 체크용

	POINT _size;

	animation* _EricMotion;	//에릭모션

public:
	player_Eric();
	~player_Eric();

	HRESULT init();
	void release();
	void update();
	void render();

	//얘네는 공통적으로 작동되는거 이외에 작성하면됨
	virtual void keyPressMove()		override;
	virtual void keyPressSpace()	override;
	virtual void keyPressD()		override;
	virtual void keyPressE()		override;
	virtual void keyPressS()		override;



	//좌우체크
	virtual void rectBrokenWallCollision()			override; // << 렉트 부숴지는 벽 충돌 
	//위에벽체크(천장) 
	virtual void pixelTopWallCollision()			override; // 픽셀 천장 충돌 
	//바닥체크
	virtual void pixelBottomCollision()				override; // << 바닥 픽셀 충돌 




	//처맞는함수

	void jump();
	void EricAniinit();
	void EricAni();

	void EricAniStart(string key);

};

