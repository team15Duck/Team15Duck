#pragma once
#include "playerBase.h"
class player_Eric :
	public playerBase
{
public:
	player_Eric();
	~player_Eric();

	HRESULT init();
	void release();
	void update();
	void render(HDC cameraDC);

	//��״� ���������� �۵��Ǵ°� �̿ܿ� �ۼ��ϸ��
	virtual void keyPressMove()		override;
	virtual void keyPressSpace()	override;
	virtual void keyPressD()		override;
	virtual void keyPressE()		override;
	virtual void keyPressS()		override;
	virtual void keyPressCtrl()		override;
	virtual void keyPressTab()		override;



	//�¿�üũ
	virtual void pixelHorizenWallCollision()		override; // << �ȼ� �� �浹 
	virtual void rectBrokenWallCollision()			override; // << ��Ʈ �ν����� �� �浹 
	//������üũ(õ��) 
	virtual void pixelTopWallCollision()			override; // �ȼ� õ�� �浹 
	//�ٴ�üũ
	virtual void pixelBottomCollision()				override; // << �ٴ� �ȼ� �浹 




	//ó�´��Լ�

};

