#pragma once
#include "item.h"
#include "playerBase.h"

struct tagItemSelect
{
	PLAYER_NAME name;	//ĳ����
	int invenPos;		//�κ������� 4������ ������
	POINTF renderPos;	//�׷��� ������
	bool isRender;		//�������ٰŴ�
};

class mainUI
{
private:
	image* _main;					//���� UI �̹���
	int _currentMainFrameIndex;		//���� UI ������ �������� == �÷��̾� �Ŵ������� ���� ���õȾָ� �޾Ƽ� ��������

	
	bool _isItemSelectOn;			//���� ������ �������̴�?
	bool _isItemMove;				//������ �ű�� ���̴�?
	tagItemSelect _itemSelect[3];	//������ ����

	float _blinkedCount;			//������ �������϶� �����̱� ���� ī��Ʈ

	item* _playerItem[3][4];		//�÷��̾����������

	int _playerHP[3];				//�÷��̾� ü������
	bool _isPlayerAlive[3];			//�÷��̾� ��������
	
public:
	mainUI();
	~mainUI();

	HRESULT init();
	void release();
	void update();
	void render();

	void setEricItemInfo(item** it);
	void setBaleogItemInfo(item** it);
	void setOlafItemInfo(item** it);

	bool getIsItemSelectOn() { return _isItemSelectOn; }
	void setIsItemSelectOn(bool isItemSelectOn);

	bool getIsItemMove() { return _isItemMove; }									
	void setIsItemMove(bool isItemMove) { _isItemMove = isItemMove; }

	void setCurrentMainFrameIndex(int index) { _currentMainFrameIndex = index; }		//�÷��̾� �Ŵ������� ���õȾְ� ������ �˾Ƽ� �־��� �Լ�

	void setEricUIHP(int hp) { _playerHP[PLAYER_NAME_ERIC] = hp; }
	void setBaleogUIHP(int hp) { _playerHP[PLAYER_NAME_BALEOG] = hp; }
	void setOlafUIHP(int hp) { _playerHP[PLAYER_NAME_OLAF] = hp; }

	void setEricUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_ERIC] = alive; }
	void setBaleogUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_BALEOG] = alive; }
	void setOlafUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_OLAF] = alive; }

	int getInvenPos(PLAYER_NAME name);

};

