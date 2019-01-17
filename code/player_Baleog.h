#pragma once
#include "playerBase.h"
class player_Baleog : public playerBase
{
private:
	
	//�μ����� �� TEST�� �ӽ� RECT
	RECT	_tempWall;

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

	

	//�¿�üũ
	virtual void pixelHorizenWallCollision() override; // << �ȼ� �� �浹 
	virtual void rectBrokenWallCollision() override; // << ��Ʈ �ν����� �� �浹 
	
	//�ٴ�üũ
	virtual void pixelBottomCollision() override; // << �ٴ� �ȼ� �浹

};

