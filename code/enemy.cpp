#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(int num, float posX, float posY, float startX, float endX)
{
	_pos.x = posX;
	_pos.y = posY;
	_startX = startX;
	_endX = endX;
	_fireTimeCount = 0;
	_fireTimeDelay = 5.0f;
	_aniType = "enemy" + to_string(num);
	enemyAniInit();
	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	KEYANIMANAGER->update(_aniType);
	move();
}

void enemy::render()
{
	_img->aniRender(CAMERA->getMemDC(), _pos.x - 31, _pos.y - 31, _ani);
}

void enemy::move()
{
	switch (_state)
	{
		case ENEMY_LEFT_MOVE:
			if (_pos.x > _startX)
			{
				_pos.x -= TIMEMANAGER->getElpasedTime() * ENEMY_SPEED;
				if (_pos.x <= _startX)
				{
					_state = ENEMY_RIGHT_MOVE;
					_ani = KEYANIMANAGER->findAnimation(_aniType, "enemyRightMove");
					_ani->start();
				}
			}
		break;
		case ENEMY_RIGHT_MOVE:
			if (_pos.x < _endX)
			{
				_pos.x += TIMEMANAGER->getElpasedTime() * ENEMY_SPEED;
				if (_pos.x >= _endX)
				{
					_state = ENEMY_LEFT_MOVE;
					_ani = KEYANIMANAGER->findAnimation(_aniType, "enemyLeftMove");
					_ani->start();
				}
			}
		break;
	}
	_rc = RectMakeCenter(_pos.x, _pos.y, 62, 62);
}

int enemy::isFire(float x, float y)
{
	_fireTimeCount += TIMEMANAGER->getElpasedTime();
	if (_fireTimeCount >= _fireTimeDelay)
	{
		_isAttack = true; _fireTimeCount = 0;
	}
	if(_state == ENEMY_LEFT_MOVE && x < _pos.x && _pos.x - x < 300 && y - 35  < _pos.y && _pos.y < y + 35 && _isAttack)
	{
	  	_isAttack = false;
		_state = ENEMY_LEFT_ATTACK;
		_ani = KEYANIMANAGER->findAnimation(_aniType, "enemyLeftAttack");
		_ani->start();
		return 1;
	}
	else if (_state == ENEMY_RIGHT_MOVE && x > _pos.x && x - _pos.x < 300 && y - 35 < _pos.y && _pos.y < y + 35 && _isAttack)
	{
		_isAttack = false;
		_state = ENEMY_RIGHT_ATTACK;
		_ani = KEYANIMANAGER->findAnimation(_aniType, "enemyRightAttack");
		_ani->start();
		return 2;
	}
	else return 0;
}

void enemy::enemyAniInit()
{
	_img = IMAGEMANAGER->addFrameImage("enemy", "image/enemy.bmp", 620, 62, 10, 1, true, RGB(255, 0, 255));
	KEYANIMANAGER->addAnimationType(_aniType);

	int arrEnemyRightMove[] = { 0, 1, 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniType, "enemyRightMove", "enemy", arrEnemyRightMove, 3, 8, true);
	int arrEnemyLeftMove[] = { 9, 8, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniType, "enemyLeftMove", "enemy", arrEnemyLeftMove, 3, 8, true);


	int arrEnemyRightAttack[] = { 3, 4 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniType, "enemyRightAttack", "enemy", arrEnemyRightAttack, 2, 10, false, enemyRightAttack, this);
	int arrEnemyLeftAttack[] = { 6, 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniType, "enemyLeftAttack", "enemy", arrEnemyLeftAttack, 2, 10, false, enemyLeftAttack, this);

	_state = ENEMY_LEFT_MOVE;
	_ani = KEYANIMANAGER->findAnimation(_aniType, "enemyLeftMove");
	_ani->start();
}

void enemy::enemyRightAttack(void* obj)
{
	enemy* e = (enemy*)obj;
	e->setState(ENEMY_RIGHT_MOVE);
	e->setAni(KEYANIMANAGER->findAnimation(e->getAniType(), "enemyRightMove"));
	e->getAni()->start();
}

void enemy::enemyLeftAttack(void* obj)
{
	enemy* e = (enemy*)obj;
	e->setState(ENEMY_LEFT_MOVE);
	e->setAni(KEYANIMANAGER->findAnimation(e->getAniType(), "enemyLeftMove"));
	e->getAni()->start();
}
