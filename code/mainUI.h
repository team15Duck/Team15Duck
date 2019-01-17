#pragma once
#include "item.h"
#include "playerBase.h"

struct tagItemSelect
{
	PLAYER_NAME name;	//캐릭터
	int invenPos;		//인벤에서의 4가지의 포지션
	POINTF renderPos;	//그려줄 포지션
	bool isRender;		//렌더해줄거니
};

class mainUI
{
private:
	image* _main;					//메인 UI 이미지
	int _currentMainFrameIndex;		//메인 UI 프레임 돌릴숫자 == 플레이어 매니저에서 현재 선택된애를 받아서 넣을것임

	
	bool _isItemSelectOn;			//현재 아이템 선택중이니?
	bool _isItemMove;				//아이템 옮기는 중이니?
	tagItemSelect _itemSelect[3];	//아이템 선택

	float _blinkedCount;			//아이템 선택중일때 깜박이기 위한 카운트

	item* _playerItem[3][4];		//플레이어아이템정보

	int _playerHP[3];				//플레이어 체력정보
	bool _isPlayerAlive[3];			//플레이어 생존정보
	
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

	void setCurrentMainFrameIndex(int index) { _currentMainFrameIndex = index; }		//플레이어 매니저에서 선택된애가 누군지 알아서 넣어줄 함수

	void setEricUIHP(int hp) { _playerHP[PLAYER_NAME_ERIC] = hp; }
	void setBaleogUIHP(int hp) { _playerHP[PLAYER_NAME_BALEOG] = hp; }
	void setOlafUIHP(int hp) { _playerHP[PLAYER_NAME_OLAF] = hp; }

	void setEricUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_ERIC] = alive; }
	void setBaleogUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_BALEOG] = alive; }
	void setOlafUIIsAlive(bool alive) { _isPlayerAlive[PLAYER_NAME_OLAF] = alive; }

	int getInvenPos(PLAYER_NAME name);

};

