#pragma once
#include "playerBase.h"
class player_Baleog : public playerBase
{
private:
	

public:
	player_Baleog();
	~player_Baleog();

	HRESULT init();
	void release();
	void update();
	void render();
	void render(HDC cameraDC);


	//��״� ���������� �۵��Ǵ°� �̿ܿ� �ۼ��ϸ��
	virtual void keyPressSpace() override;
	virtual void keyPressD() override;

	//ȭ������� �������� �ϴ� �Լ�
	void moveRange();

	//�¿�üũ
	virtual void pixelHorizenWallCollision() override; // << �ȼ� �� �浹 
	virtual void rectBrokenWallCollision() override; // << ��Ʈ �ν����� �� �浹 
	
	//�ٴ�üũ
	virtual void pixelBottomCollision() override; // << �ٴ� �ȼ� �浹

};

