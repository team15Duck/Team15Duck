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
	bool _isRightMotion;

	float _accleration;			//���ӵ�
	float _minSpeed;			//�����ӵ�
	float _maxSpeed;			//�ְ�ӵ�
	float _shieldGravity;		//�����߷�

	float _specialTime;			//Ư���ൿ�� �ð�
	float _specialDelay;		//Ư���ൿ ������

public:
	player_Olaf();
	~player_Olaf();

	HRESULT init();
	void release();
	void update();

	void render();
	//���� ���
	virtual void shieldRender(HDC hdc) override;
	// ========== Ű�Է� ==========

	//�θ𲨴� ���� ����
	virtual void keyPressMove() override;
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//��Ű�Է�
	// 1. ���� X + ��ٸ� X
	//   1) Right
	void noLadder_KeyRight();
	//	 2) Left
	void noLadder_KeyLeft();

	// 2. ���� O + ��ٸ� O
	//   1) Up
	void ladder_KeyUp();
	//   2) Down
	void ladder_KeyDown();
	//   3) Right
	void ladder_KeyRight();
	//   4) Left
	void ladder_KeyLeft();

	// 3. ���� O + ���� X + ��ٸ� X
	//   1)Right
	void noFall_Shield_KeyRight();
	//   2)Left
	void noFall_Shield_KeyLeft();

	// 4. ���� O + ���� X + ��ٸ� O
	//   1)Up
	void noFall_Shield_KeyUp();
	//   2)Down
	void noFall_Shield_KeyDown();


	// 5. ���� O + ���� O + ��ٸ� X
	//   1)Right
	void noLadder_Shield_KeyRight();
	//   2)Left
	void noLadder_Shield_KeyLeft();

	// 6. ���� O + ���� O + ��ٸ� O
	//   1)Right
	void fall_Shield_KeyRight();
	//   2)Left
	void fall_Shield_KeyLeft();





	// ========== �ö����� ���� ==========

	//�ö��� �ʱ�ȭ
	void initOlaf();
	//�ö��� �̹����ʱ�ȭ
	void initImgOlaf();
	//���� �ʱ�ȭ
	void initShield();

	//�ö��� ����
	void stateOlaf();
	//�ö��� Ư�����
	void specialMotion_Olaf();
	//���� ����
	void stateShield();
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

};