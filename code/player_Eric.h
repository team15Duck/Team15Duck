#pragma once
#include "playerBase.h"
class player_Eric : public playerBase
{
private:
	float _jumpPower;

	bool _isJump;       //���� üũ��
	bool _isRCollision;	//������ �浹 üũ�� 
	bool _isLCollision;	//���� �浹 üũ��

	//�̵� ����ó���� �Ұ�
	bool _isRightMove;
	bool _isLeftMove;

	POINT _size;

	animation* _EricMotion;	//�������

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

	// �̵����� �Լ�
	void leftMove();
	void rightMove();

	void jump();

	//�ִϸ��̼ǰ��� �Լ�
	void EricAniinit();
	void EricAni();
	void EricAniStart(string key);

};

