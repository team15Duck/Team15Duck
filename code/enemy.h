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
	POINTF		_pos;				//��ǥ

	float		_startX;			//��״� �¿�θ� �����̱⶧���� y���� �ʿ����
	float		_endX;				//��״� �¿�θ� �����̱⶧���� y���� �ʿ����

	ENEMY_STATE _state;				//������Ʈ
	RECT		_rc;				//���ʹ� ��Ʈ

	image*		_img;
	animation*  _ani;				//�ִϸ��̼�
	string		_aniType;
	bool		_isAlive;			//��Ҵ� �׾���

	POINTF*		_playerPos[3];		//�÷��̾� ��ǥ�� �ּҸ� ������Ѽ� �Ǵ��ϸ� ��

	bool		_isAttack;			//�����Ҽ��ֳ�
	float		_fireTimeDelay;		//���������� ���� �Ѿ��� ���Ѵ�� �߻��� ����� ������ �Ѿ˹߻翡 �����̸� �ֱ����� �� �ð��� �����ִ� ����
	float		_fireTimeCount;		//�ð��� ������ �༮

public:
	enemy();
	~enemy();

	HRESULT init(int num, float posX, float posY, float startX, float endX);
	void release();
	void update();
	void render();

	void move();
	int isFire(float x, float y);			//�Ѿ� �߻����� ���� �Ǵ����� �Լ� Ʈ��� ��¼��� ���ݾִϸ��̼� ������ְ�  ���� �ִϸ��̼� Ʋ���ָ��
	
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

