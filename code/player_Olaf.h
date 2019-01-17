#pragma once
#include "playerBase.h"
class player_Olaf :	public playerBase
{
private:
	RECT _shield;			//���϶� ����
	image* _pixelShield;	//���и� ���� ������� �ȼ��浹��

	bool _isShieldUp;		//���и� ���� ����ִ���?

	float _shieldX;			//���� X��ǥ
	float _shieldY;			//���� Y��ǥ

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

	//���� �ʱ�ȭ
	void initShield();	

	//���� ����
	void stateShield();


	// ========== �浹�Լ� ==========

	//�¿캮�浹(�ȼ���)
	virtual void pixelHorizenWallCollision() override;
	
	//�¿캮�浹(��Ʈ��)
	virtual void rectBrokenWallCollision() override;
	
	//�ٴ��浹
	virtual void pixelBottomCollision() override;





	// ========== GET & SET ==========

	





};

