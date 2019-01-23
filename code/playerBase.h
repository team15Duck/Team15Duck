#pragma once
#include "item.h"
//#include "mainUI.h"
//#include "objectManager.h"

//알아서 조절하셈
#define MAX_SPEED	350.0f
#define MIN_SPEED	5.0f
#define MAX_LIFE	3
#define ACC_SPEED	200.0f
#define START_JUMPP 300.0f
#define GRAVITY		250.0f

enum PLAYER_NAME
{
	PLAYER_NAME_ERIC,
	PLAYER_NAME_BALEOG,
	PLAYER_NAME_OLAF,

	PLAYER_NAME_NONE,
	PLAYER_NAME_COUNT = PLAYER_NAME_NONE
};

enum PLAYER_STATE
{
	//공통
	PLAYER_IDLE_RIGHT,
	PLAYER_IDLE_LEFT,
	PLAYER_IDLE_SPECIAL_RIGHT,
	PLAYER_IDLE_SPECIAL_LEFT,
	PLAYER_MOVE_RIGHT,
	PLAYER_MOVE_LEFT,
	PLAYER_FALL_RIGHT,
	PLAYER_FALL_LEFT,
	PLAYER_HIGH_FALL_RIGHT,
	PLAYER_HIGH_FALL_LEFT,
	PLAYER_PUSH_WALL_RIGHT,
	PLAYER_PUSH_WALL_LEFT,
	PLAYER_LADDER_UP,
	PLAYER_LADDER_DOWN,
	PLAYER_LADDER_END,
	PLAYER_HIT_RIGHT,
	PLAYER_HIT_LEFT,
	PLAYER_HIT_DEATH_RIGHT,
	PLAYER_HIT_DEATH_LEFT,
	PLAYER_FALL_DEATH_RIGHT,
	PLAYER_FALL_DEATH_LEFT,
	PLAYER_FIRE_DEATH_RIGHT,
	PLAYER_FIRE_DEATH_LEFT,

	//하영캐릭
	PLAYER_JUMP_RIGHT,
	PLAYER_JUMP_LEFT,
	PLAYER_SIGN_RIGHT,
	PLAYER_SIGN_LEFT,
	PLAYER_HEAD_BUTT_RIGHT,
	PLAYER_HEAD_BUTT_LEFT,
	PLAYER_STUN_RIGHT,
	PLAYER_STUN_LEFT,

	//재원캐릭	칼쓰는거 가로 세로는 랜덤으로 0 , 1 줘서 처리
	PLAYER_LOOK_FRONT_RIGHT,
	PLAYER_LOOK_FRONT_LEFT,
	PLAYER_ATTACK_RIGHT,
	PLAYER_ATTACK_LEFT,
	PLAYER_ARROW_RIGHT,
	PLAYER_ARROW_LEFT,

	//윤정캐릭
	//낙하대기이동 쉴드꼈을때 안꼇을때는 bool값으로 스테이트교체할때 판정
	PLAYER_SHIELD_IDLE_RIGHT,
	PLAYER_SHIELD_IDLE_LEFT,
	PLAYER_SHIELD_IDLE_SPECIAL_RIGHT,
	PLAYER_SHIELD_IDLE_SPECIAL_LEFT,
	PLAYER_SHIELD_MOVE_RIGHT,
	PLAYER_SHIELD_MOVE_LEFT,
	PLAYER_SHIELD_FALL_RIGHT,
	PLAYER_SHIELD_FALL_LEFT,
	PLAYER_SHIELD_FALL_MOVE_RIGHT,
	PLAYER_SHIELD_FALL_MOVE_LEFT,

};

class objectManager;
class object;
class mainUI;
class playerBase
{
protected:

	image* _pixelData;
	image* _player;

	PLAYER_NAME _name;


	float			_x;							//좌표
	float			_y;							//좌표
	float			_saveY;						//점프직전또는 떨어지기 직전의 y의 위치값을 저장해줌
	float			_speed;
	float			_gravity;
	float			_proveTop;				    //픽셀충돌 확인용 
	float			_proveBottom;			    //픽셀충돌 확인용 
	float			_proveLeft;					//픽셀충돌 확인용 
	float			_proveRight;			    //픽셀충돌 확인용 

	bool			_isFall;
	bool			_isAlive;
	bool			_deathMotion;

	bool			_isLadder;					//사다리 타고있니?
	bool			_isLadderTop;				//사다리 맨위에 있니?
	bool			_isAttackRight;

	int				_lifeCount;					//체력
	int				_currentSelectItemSlot;		//현재 선택된 아이템슬롯번호 0~3
	PLAYER_STATE	_state;
	RECT			_playerRect;
	RECT			_shieldRect;				//옆일때 방패

	item*			_invenItem[4];

	mainUI*			_mainUI;					//유아이뇨속 아이템처리할거임 
	objectManager* _objm;						//오브젝트 매니저뇨속 아이템 사용처리할거임 

	vector<RECT*>	_ladderRc;
	vector<object*>	_objectRc;

public:
	playerBase();
	~playerBase();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//key업데이트에는 사용되는함수 전부 넣어서 작동되게하고
	//자식에게는 만들지 말것.
	virtual void keyUpdate();

	//얘네는 공통적으로 작동되는거 이외에 작성하면됨
	virtual void keyPressMove();
	virtual void keyPressSpace();
	virtual void keyPressD();
	virtual void keyPressE();
	virtual void keyPressS();




	//좌우체크
	virtual void pixelLeftWallCollision();	 //픽셀벽충돌(왼쪽)
	virtual void pixelRightWallCollision();	 //픽셀벽충돌(오른쪽)
	virtual void rectBrokenWallCollision(); // << 렉트 부숴지는 벽 충돌 
	//위에벽체크(천장) << 오버라이드 받아서 나만 쓰기 
	virtual void pixelTopWallCollision(); // 픽셀 천장 충돌 
	//바닥체크
	virtual void pixelBottomCollision(); // << 바닥 픽셀 충돌 

	//사다충돌 체크용
	virtual void playerCollisionLadder(object* ladder);
	virtual void setLadderRectAdressLink(RECT* rc);
	virtual void shieldRender(HDC hdc);

	//오브젝트 사용 충돌 체크용
	virtual void setObjectRectAdressLink(object* rc);
	virtual void setObjectManagerAdressLink(objectManager* objm);

	//처맞는함수
	virtual void takeDamage(int damage);

	//살았니 죽었니 죽는중이니?






	//겟셋은 제일밑에 작성하세요
	float* getPosX() { return &_x; }
	float* getPosY() { return &_y; }

	void setMainUILink(mainUI* ui) { _mainUI = ui; }
	PLAYER_NAME getPlayerName() { return _name; }

	void setPixelDataLink(image* img) { _pixelData = img; }
	
	RECT getPlayerRect()	{ return _playerRect; }
	RECT getShieldRect()	{ return _shieldRect; }
	item** getInvenItem()	{ return _invenItem;  }

	bool getIsAlive() { return _isAlive; }
	virtual bool getIsFire() { return false; }
	virtual	void setIsFire(bool isFire) {}
	virtual bool getIsAttackRight() { return _isAttackRight; }

	void setInvenItem(int pos, item* it) { _invenItem[pos] = it; }

};
