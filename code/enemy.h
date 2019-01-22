#pragma once
#define ENEMY_SPEED 80.0f

enum ENEMY_STATE
{
	ENEMY_LEFT_MOVE,
	ENEMY_LEFT_ATTACK,
	ENEMY_RIGHT_MOVE,
	ENEMY_RIGHT_ATTACK,
	ENEMY_NONE,
	ENEMY_COUNT = ENEMY_NONE
};


class enemy
{
private:
	POINTF		_pos;				//좌표

	float		_startX;			//얘네는 좌우로만 움직이기때문에 y축은 필요없다
	float		_endX;				//얘네는 좌우로만 움직이기때문에 y축은 필요없다

	ENEMY_STATE _state;				//스테이트
	RECT		_rc;				//에너미 렉트

	image*		_img;
	animation*  _ani;				//애니메이션
	string		_aniType;
	bool		_isAlive;			//살았니 죽었니

	POINTF*		_playerPos[3];		//플레이어 좌표의 주소를 연결시켜서 판단하면 됨

	bool		_isAttack;			//공격할수있냐
	float		_fireTimeDelay;		//일정범위에 오면 총알을 무한대로 발사할 우려가 있으니 총알발사에 딜레이를 주기위해 그 시간을 정해주는 변수
	float		_fireTimeCount;		//시간을 세어줄 녀석

public:
	enemy();
	~enemy();

	HRESULT init(int num, float posX, float posY, float startX, float endX);
	void release();
	void update();
	void render();

	void move();
	int isFire(float x, float y);			//총알 발사할지 말지 판단해줄 함수 트루로 뱉는순간 공격애니메이션 재생해주고  원래 애니메이션 틀어주면됨
	
	void enemyAniInit();

	POINTF getPos() { return _pos; }

	bool getIsAlive() { return _isAlive; }
	void setIsAlive(bool alive) { _isAlive = alive; }

	ENEMY_STATE getState() { return _state; }
	void setState(ENEMY_STATE state) { _state = state; }
	
	animation* getAni() { return _ani; }
	void setAni(animation* ani) { _ani = ani; }

	string getAniType() { return _aniType; }
	
	static void enemyRightAttack(void* obj);
	static void enemyLeftAttack(void* obj);
};

