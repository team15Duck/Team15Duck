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

	bool _isFloor;

	float _shieldX;				//���� X��ǥ
	float _shieldY;				//���� Y��ǥ

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


	// ========== �Լ��߰� ==========

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

	//�ٴ��浹
	virtual void pixelBottomCollision() override;

	//��ٸ��浹
	void playerCollisionLadder();


	// ========== GET & SET ==========


};