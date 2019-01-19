#pragma once

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
	POINTF _pos;				//��ǥ

	float _startX;				//��״� �¿�θ� �����̱⶧���� y���� �ʿ����
	float _endX;				//��״� �¿�θ� �����̱⶧���� y���� �ʿ����

	ENEMY_STATE _state;			//������Ʈ
	RECT _rc;					//���ʹ� ��Ʈ

	animation*  _ani;			//�ִϸ��̼�

	bool _isAlive;				//��Ҵ� �׾���

	POINTF* _playerPos[3];		//�÷��̾� ��ǥ�� �ּҸ� ������Ѽ� �Ǵ��ϸ� ��

	bool _isAttack;				//�����Ҽ��ֳ�
	float _fireTimeDelay;		//���������� ���� �Ѿ��� ���Ѵ�� �߻��� ����� ������ �Ѿ˹߻翡 �����̸� �ֱ����� �� �ð��� �����ִ� ����
	float _fireTimeCount;		//�ð��� ������ �༮

public:
	enemy();
	~enemy();

	HRESULT init(float startX, float endX);
	void release();
	void update();
	void render();

	void move();
	bool isFire();			//�Ѿ� �߻����� ���� �Ǵ����� �Լ� Ʈ��� ��¼��� ���ݾִϸ��̼� ������ְ�  ���� �ִϸ��̼� Ʋ���ָ��

	POINTF getPos() { return _pos; }

	bool getIsAlive() { return _isAlive; }
	void setIsAlive(bool alive) { _isAlive = alive; }
};

