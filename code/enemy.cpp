#include "stdafx.h"
#include "enemy.h"


enemy::enemy()
{
}


enemy::~enemy()
{
}

HRESULT enemy::init(float startX, float endX)
{

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	move();
}

void enemy::render()
{
}

void enemy::move()
{
	switch (_state)
	{
		case ENEMY_LEFT_MOVE:
			//이동 + 이동조건 작성
		break;
		case ENEMY_RIGHT_MOVE:
			//이동 + 이동조건 작성
		break;
	}
}

bool enemy::isFire()
{
	//적은 방향에 따라 그범위안에 캐릭터가 들어오면
//반응하고 공격한뒤 다시 움직인다
//ex) _fireTimeCount += TIMEMANAGER->getElpasedTime();
//if(_fireTimeCount == _fireTimeDelay)
//{
//	_isAttack = true; _fireTimeCount = 0;
//}
//if(_state == ENEMY_LEFT_MOVE && 플레이어X < _posX && _posX - 플레이어X < 공격거리 && 플레이어Y - 렉트크기절반  < _posY && _posY < 플레이어Y + 렉트크기절반 && attack)
//{
//  	 _isAttack = false;
//		//공격애니메이션 발동
//		return true;
//}
//else return false;
	return false;
}
