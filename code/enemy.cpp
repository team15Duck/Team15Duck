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
			//�̵� + �̵����� �ۼ�
		break;
		case ENEMY_RIGHT_MOVE:
			//�̵� + �̵����� �ۼ�
		break;
	}
}

bool enemy::isFire()
{
	//���� ���⿡ ���� �׹����ȿ� ĳ���Ͱ� ������
//�����ϰ� �����ѵ� �ٽ� �����δ�
//ex) _fireTimeCount += TIMEMANAGER->getElpasedTime();
//if(_fireTimeCount == _fireTimeDelay)
//{
//	_isAttack = true; _fireTimeCount = 0;
//}
//if(_state == ENEMY_LEFT_MOVE && �÷��̾�X < _posX && _posX - �÷��̾�X < ���ݰŸ� && �÷��̾�Y - ��Ʈũ������  < _posY && _posY < �÷��̾�Y + ��Ʈũ������ && attack)
//{
//  	 _isAttack = false;
//		//���ݾִϸ��̼� �ߵ�
//		return true;
//}
//else return false;
	return false;
}
