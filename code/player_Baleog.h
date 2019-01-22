#pragma once
#include "playerBase.h"


class player_Baleog : public playerBase
{
private:
	animation*		_playerAni;
	const char*		_imageKey;
	const char*		_aniImageKey;

	//float			_gravity;				//�������� �߷°��� �ʿ��ؿ�
	float			_acceleration;			//���ӵ�
	float			_minSpeed;				//�����ӵ�
	float			_maxSpeed;				//�ְ�ӵ�

	float			_fallStartY;			//�������� �����Ҷ� ���̸� ������ ����
	float			_curFallingY;				//������ ���� ����	
	float			_damageHeight;			//�������� �Դ� ����


	bool			_isGround;				//�ٴڿ� �پ��ּ�?
	bool			_isChangeAni;			//�ִϸ��̼� �ٲ�?
	bool			_isPushWall;			//�� �̴� ����?
	bool			_isLadder;				//��ٸ� ����?
	//bool			_isLadderDownEnd;		//��ٸ� �Ʒ�����?

	bool			_isRight;				//��ٸ� �ö󰡰� ���� ������ ���̵� ��Ƕ����� �� bool ��
	bool			_isFire;				//�߻��߳�?

	int				_ladderIndex;			//�浹�� ��ٸ� �ε��� ��ȣ

	

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

	//�ٴ�üũ
	virtual void pixelBottomCollision() override;	// << �ٴ� �ȼ� �浹

	virtual void pixelFireCollision();				// << �Ұ� �ε��� ��� 


	//virtual void rectBrokenWallCollision() override; // << ��Ʈ �ν����� �� �浹 

	//keyAni �̹��� ����� �Լ�
	void keyAniSetting();

	//��ٸ� �浹 üũ�� �Լ�
	virtual void collisionLadder(vector<RECT*> ladder);
	virtual void attackKey();

	virtual bool getIsAttackRight() override;
	virtual bool getIsFire() override;
	virtual void setIsFire(bool isFire) override;
	
};

