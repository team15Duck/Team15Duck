#pragma once
#include "playerBase.h"


class player_Eric : public playerBase
{
private:

	int _aniCount;
	int _ladderIndex;		//��ٸ��ε���

	float _jumpPower;

	bool _isJump;			//���� üũ��

	bool _isladderup;		//��ٸ� �ö󰡴� ��
	bool _isladderdown;		//��ٸ� �������� ��
	bool _isUsladder;		//�ö󰥶������� ��ٸ�üũ
	bool _isUeladder;		//�ö󰥶����� ��ٸ� üũ
	bool _isDsladder;		//�����ö� ������ ��ٸ�üũ
	bool _isDeladder;		//�����ö� ���� ��ٸ�üũ
	bool _isladderUse;		//�ڳ� ���� ��ٸ� ������ΰ�? �Ŵ޷��ִ°�?

	bool _isRCollision;		//������ �浹 üũ�� 
	bool _isLCollision;		//���� �浹 üũ��
	bool _isBCollision;		//�ٴ� �浹 üũ��
	bool _isFCollision;		//�״� �ٴ� �浹 üũ��

	//�̵� ����ó���� �Ұ�
	bool _isRightMove;
	bool _isLeftMove;

	//��ų Ȯ�ο� �Ұ�
	bool _isRSkill;
	bool _isLSkill;


	POINT _size;

	animation* _EricMotion;	//�������
	object* _ladder;

public:
	player_Eric();
	~player_Eric();

	HRESULT init();
	void release();
	void update();
	void render();

	//��״� ���������� �۵��Ǵ°� �̿ܿ� �ۼ��ϸ��
	virtual void keyPressMove()		override;
	virtual void keyPressSpace()	override;
	virtual void keyPressD()		override;
	virtual void keyPressE()		override;
	virtual void keyPressS()		override;



	//�¿�üũ
	virtual void rectBrokenWallCollision()			override; // << ��Ʈ �ν����� �� �浹 
	//������üũ(õ��) 
	virtual void pixelTopWallCollision()			override; // �ȼ� õ�� �浹 
	//�ٴ�üũ
	virtual void pixelBottomCollision()				override; // << �ٴ� �ȼ� �浹 

	//�״� �Լ�	
	void pixelDieCollision();

	// �̵����� �Լ�
	void leftMove();
	void rightMove();
	void upMove(object * ladder);
	void downMove(object * ladder);

	void jump();

	//�ִϸ��̼ǰ��� �Լ�
	void EricAniinit();
	void EricAni();
	void EricAniStart(string key);

};

