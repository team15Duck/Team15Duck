#pragma once
#include "playerBase.h"
class player_Olaf : public playerBase
{
private:
	RECT _shield;				//���϶� ����
	image* _pixelShield;		//���и� ���� ������� �ȼ��浹��
	animation* _olafMotion;		//�ö������

	bool _isShieldUp;			//���и� ���� ����ִ���?
	bool _isLeftCollision;		//���� �ε�������?
	bool _isRightCollision;		//������ �ε�������?
	bool _isAniStart;			//��� �����ߴ���?
	bool _isFloor;				//�ٴ�����?
	bool _isLadderBottom;		//��ٸ� ������?
								
	float _accleration;			//���ӵ�
	float _minSpeed;			//�����ӵ�
	float _maxSpeed;			//�ְ�ӵ�
	float _shieldGravity;		//�����߷�

public:
	player_Olaf();
	~player_Olaf();

	HRESULT init();
	void release();
	void update();

	void render();
	// ========== Ű�Է� ==========

	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;


	// ========== �ö����� ���� ==========

	//�ö��� �ʱ�ȭ
	void initOlaf();

	//�ö��� ����
	void stateOlaf();

	//���� �ʱ�ȭ
	void initShield();

	//���� ����
	void stateShield();

	//���� ���
	virtual void shieldRender(HDC hdc) override;

	//============ �ִϸ��̼� ============

	//�ö��� �̹����ʱ�ȭ
	void initImgOlaf();

	//�ö��� �ִϸ��̼�
	void startAniOlaf(string aniKey);

	// ========== �浹�Լ� ==========

	//�¿캮�浹(�ȼ���)
	virtual void pixelLeftWallCollision() override;
	virtual void pixelRightWallCollision() override;

	//�ٴ��浹(�ȼ���)
	virtual void pixelBottomCollision() override;

	//���浹(�ȼ���)
	void pixelFireCollision();

	//��ٸ��浹(��Ʈ��)
	void playerCollisionLadder();



	// ========== GET & SET ==========


};