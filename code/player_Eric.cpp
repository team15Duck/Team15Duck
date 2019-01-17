#include "stdafx.h"
#include "player_Eric.h"


player_Eric::player_Eric()
{
}


player_Eric::~player_Eric()
{
}


HRESULT player_Eric::init()
{
	_x = 300;
	_y = 1350;
	_speed = MIN_SPEED;
	_jumpPower = _gravity = 0;
	_isJump = false;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	_proveBottom = _playerRect.bottom;

	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{

	pixelBottomCollision();
	if (_isJump)
	{
		_y -= _jumpPower;
		_jumpPower -= _gravity;
	}
	if (_jumpPower <= 0)
	{
		if (_state == PLAYER_JUMP_RIGHT)
		{
			_state = PLAYER_FALL_RIGHT;
		}
		else if (_state == PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_FALL_LEFT;
		}
	}

	_proveBottom = _playerRect.bottom + 5;
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Eric::render()
{
	Rectangle(CAMERA->getMemDC(), _playerRect);
}

void player_Eric::keyPressMove()
{
	// ����Ű ��߼ӵ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_speed = MIN_SPEED;
		/*if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_LEFT;
		}*/
	}
	// �������� ���ӵ� ���̸� �̵��ϴ� Ű����  
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//���࿡ �ӵ��� �ƽ� �ӵ����� �۴ٸ�
		if (_speed < MAX_SPEED)
		{
			//���ǵ带 ��� �����ִµ� ���ӵ� * �ð�
			_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
		}
		// �ƽ� �ӵ����� ������ �ƴ϶��
		else
		{
			//���ǵ�� ���̻� Ŀ���� �ʰ� �ִ� �ӵ��� �����Ѵ�.
			_speed = MAX_SPEED;
		}
		//���࿡ �÷��̾� ��Ʈ�� ������ ���� ���� ũ�⸦ �Ѿ���� �Ѵٸ�
		if (_x - 25 < 0)
		{
			// �Ѿ�� ���ϰ� ���´�
			_x += _speed;
		}
		// ���� ũ�⸦ �Ѿ���� �����ʴ´ٸ� 
		else
		{
			// ĳ���ʹ� ��� �ӵ� * �ð����� �����δ�.
			_x -= _speed * TIMEMANAGER->getElpasedTime();
			// ���࿡ ĳ���Ͱ� ũ�⸦ �Ѿ���� �Ѵٸ�
			if (_x - 25 < 0)
			{
				// x�� ���� 25�� �����Ѵ�.
				_x = 25;
			}
		}
	}
	//������Ű ��߼ӵ� ����
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_speed = MIN_SPEED;
	}
	// ���������� ���ӵ� ���̸� �̵��ϴ� Ű����
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//���࿡ ���ǵ尡 �ִ� �ӵ����� �۴ٸ�
		if (_speed < MAX_SPEED)
		{
			// �ӵ��ø���
			_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
		}
		//�װ� �ƴ϶��
		else
		{
			// �ӵ��� �ִ� �ӵ��� �����Ѵ�.
			_speed = MAX_SPEED;
		}
		//���࿡ �÷��̾� ��Ʈ�� �������� ���� ������ ũ�⸦ �Ѿ���� �Ѵٸ�
		if (_x + 25 > _pixelData->GetWidth())
		{
			// �Ѿ�� ���ϰ� ���´�
			_x -= _speed;
		}
		// ���� ũ�⸦ �Ѿ���� �����ʴ´ٸ� 
		else
		{
			// ĳ���ʹ� ��� �ӵ� * �ð����� �����δ�.
			_x += _speed * TIMEMANAGER->getElpasedTime();
			// ���࿡ ĳ���Ͱ� ũ�⸦ �Ѿ���� �Ѵٸ�
			if (_x + 25 > _pixelData->GetWidth())
			{
				// x�� ���� �� ��üũ�� -25�� �����Ѵ�.
				_x = _pixelData->GetWidth() - 25;
			}
		}
	}
}

void player_Eric::keyPressSpace()
{
	//����ó�� 
	if (!(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT ||
		_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT))
	{
		return;
	}
	//���࿡ �����̽��ٸ� ������ �����ض�
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_state = PLAYER_JUMP_LEFT;
		}
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_JUMP_RIGHT;
		}

		_isJump = true;
		_jumpPower = 10.0f;
		_gravity = 0.4f;
	}
}

void player_Eric::keyPressD()
{
}

void player_Eric::keyPressE()
{
}

void player_Eric::keyPressS()
{
}


void player_Eric::pixelHorizenWallCollision()
{
}

void player_Eric::rectBrokenWallCollision()
{
}

void player_Eric::pixelTopWallCollision()
{
}

void player_Eric::pixelBottomCollision()
{
	//���࿡ �����Ѵٸ� �ȼ��浹�Ͻø����� 
	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT) return;

	for (int i = _proveBottom - 10; i < _proveBottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// ���࿡ ���� ����Ÿ��� �浹�Ͻÿ� 
		if ((r == 255 && g == 0 && b == 255))
		{
			_y = i - 35;
			_isJump = false;

			//���࿡ ������ �ٶ󺸴� ������� �������ٸ� 
			if (_state == PLAYER_FALL_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;
			}
			//���࿡ �������� �ٶ󺸴� ������� �������ٸ� 
			if (_state == PLAYER_FALL_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;
			}

			break;
		}
	}
}
