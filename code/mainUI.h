#pragma once
#include "item.h"

struct tagItemSelect
{
	int pos;			//ĳ���ͺ�������
	int invenPos;		//�κ������� 4������ ������
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

	
	item* _playerItem[3][4];
	
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

	
};

