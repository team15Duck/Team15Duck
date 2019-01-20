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



	//��״� ���������� �۵��Ǵ°� �̿ܿ� �ۼ��ϸ��
	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//�÷��̾� �ʱ�ȭ ���� �Լ�
	void initBaleog();



	//�¿�üũ
	virtual void pixelLeftWallCollision() override;
	virtual void pixelRightWallCollision() override;

	virtual void rectBrokenWallCollision() override; // << ��Ʈ �ν����� �� �浹 

	//�ٴ�üũ
	virtual void pixelBottomCollision() override; // << �ٴ� �ȼ� �浹


	//keyAni �̹��� ����� �Լ�
	void keyAniSetting();

	//��ٸ� �浹 üũ�� �Լ�
	//virtual void playerCollisionLadder(object* ladder) override;

	//��ũ�� �Լ�
	//void setObjectAdderssLink(objectManager* obj) { _object = obj; }
};

