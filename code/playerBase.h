#pragma once
#include "item.h"
//#include "mainUI.h"
//#include "objectManager.h"

//�˾Ƽ� �����ϼ�
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
	//����
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

	//�Ͽ�ĳ��
	PLAYER_JUMP_RIGHT,
	PLAYER_JUMP_LEFT,
	PLAYER_SIGN_RIGHT,
	PLAYER_SIGN_LEFT,
	PLAYER_HEAD_BUTT_RIGHT,
	PLAYER_HEAD_BUTT_LEFT,
	PLAYER_STUN_RIGHT,
	PLAYER_STUN_LEFT,

	//���ĳ��	Į���°� ���� ���δ� �������� 0 , 1 �༭ ó��
	PLAYER_LOOK_FRONT_RIGHT,
	PLAYER_LOOK_FRONT_LEFT,
	PLAYER_ATTACK_RIGHT,
	PLAYER_ATTACK_LEFT,
	PLAYER_ARROW_RIGHT,
	PLAYER_ARROW_LEFT,

	//����ĳ��
	//���ϴ���̵� ���岼���� �Ȳ������� bool������ ������Ʈ��ü�Ҷ� ����
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


	float			_x;							//��ǥ
	float			_y;							//��ǥ
	float			_saveY;						//���������Ǵ� �������� ������ y�� ��ġ���� ��������
	float			_speed;
	float			_gravity;
	float			_proveTop;				    //�ȼ��浹 Ȯ�ο� 
	float			_proveBottom;			    //�ȼ��浹 Ȯ�ο� 
	float			_proveLeft;					//�ȼ��浹 Ȯ�ο� 
	float			_proveRight;			    //�ȼ��浹 Ȯ�ο� 

	bool			_isFall;
	bool			_isAlive;
	bool			_deathMotion;

	bool			_isLadder;					//��ٸ� Ÿ���ִ�?
	bool			_isLadderTop;				//��ٸ� ������ �ִ�?
	bool			_isAttackRight;

	int				_lifeCount;					//ü��
	int				_currentSelectItemSlot;		//���� ���õ� �����۽��Թ�ȣ 0~3
	PLAYER_STATE	_state;
	RECT			_playerRect;
	RECT			_shieldRect;				//���϶� ����

	item*			_invenItem[4];

	mainUI*			_mainUI;					//�����̴��� ������ó���Ұ��� 
	objectManager* _objm;						//������Ʈ �Ŵ������� ������ ���ó���Ұ��� 

	vector<RECT*>	_ladderRc;
	vector<object*>	_objectRc;

public:
	playerBase();
	~playerBase();

	virtual HRESULT init() = 0;
	virtual void release() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	//key������Ʈ���� ���Ǵ��Լ� ���� �־ �۵��ǰ��ϰ�
	//�ڽĿ��Դ� ������ ����.
	virtual void keyUpdate();

	//��״� ���������� �۵��Ǵ°� �̿ܿ� �ۼ��ϸ��
	virtual void keyPressMove();
	virtual void keyPressSpace();
	virtual void keyPressD();
	virtual void keyPressE();
	virtual void keyPressS();




	//�¿�üũ
	virtual void pixelLeftWallCollision();	 //�ȼ����浹(����)
	virtual void pixelRightWallCollision();	 //�ȼ����浹(������)
	virtual void rectBrokenWallCollision(); // << ��Ʈ �ν����� �� �浹 
	//������üũ(õ��) << �������̵� �޾Ƽ� ���� ���� 
	virtual void pixelTopWallCollision(); // �ȼ� õ�� �浹 
	//�ٴ�üũ
	virtual void pixelBottomCollision(); // << �ٴ� �ȼ� �浹 

	//����浹 üũ��
	virtual void playerCollisionLadder(object* ladder);
	virtual void setLadderRectAdressLink(RECT* rc);
	virtual void shieldRender(HDC hdc);

	//������Ʈ ��� �浹 üũ��
	virtual void setObjectRectAdressLink(object* rc);
	virtual void setObjectManagerAdressLink(objectManager* objm);

	//ó�´��Լ�
	virtual void takeDamage(int damage);

	//��Ҵ� �׾��� �״����̴�?






	//�ټ��� ���Ϲؿ� �ۼ��ϼ���
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
