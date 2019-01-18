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
	_x = 450;
	_y = 1400;
	_speed = MIN_SPEED;
	_jumpPower = _gravity = 0;
	_isJump = false;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//�浹ó���� �ʱ�ȭ 
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;
	_proveTop = _playerRect.top;

	_isRCollision = false;
	_isLCollision = false;

	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{
	jump();
	pixelBottomCollision();


	if (_isRCollision)
	{
		_speed = 0;
		_state = PLAYER_PUSH_WALL_RIGHT;
	}
	if (_isLCollision)
	{
		_speed = 0;
		_state = PLAYER_PUSH_WALL_LEFT;
	}
	_proveBottom = _playerRect.bottom;
	_proveTop = _playerRect.top;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Eric::render()
{
	Rectangle(CAMERA->getMemDC(), _playerRect);
}

void player_Eric::keyPressMove()
{
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))								// ����Ű ��߼ӵ� ����
	{
		_isRCollision = false;
		_speed = MIN_SPEED;
		if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_LEFT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))								//�������� ���ӵ� ���̸� �̵��ϴ� Ű����  
	{
		if (_speed < MAX_SPEED)											//���࿡ �ӵ��� �ƽ� �ӵ����� �۴ٸ�
		{
			if (!_isLCollision)											//���࿡ ���� �ȹھҴٸ�
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();	//���ǵ带 ��� �����ִµ� ���ӵ� * �ð�
			}
		}
		else															//�ƽ� �ӵ����� ������ �ƴ϶��
		{
			_speed = MAX_SPEED;											//���ǵ�� ���̻� Ŀ���� �ʰ� �ִ� �ӵ��� �����Ѵ�.
		}
		if (!_isLCollision)											//���࿡ ���� �ȹھҴٸ�
		{
			_x -= _speed * TIMEMANAGER->getElpasedTime();			// ĳ���ʹ� ��� �ӵ� * �ð����� �����δ�.
			for (int i = _proveLeft; i < _proveLeft + 30; ++i)
			{
				COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				// ���࿡ ���� �������Ķ����̶�� �浹�Ͻÿ� 
				if ((r == 0 && g == 255 && b == 255))
				{
					_isLCollision = true;
					_x = i + 25;
				}
				else
				{
					_isLCollision = false;
				}
			}
		}
		if (_x - 25 < 0)												// ���࿡ ĳ���Ͱ� ũ�⸦ �Ѿ���� �Ѵٸ�
		{
			_x = 25;													// x�� ���� 25�� �����Ѵ�.
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))							//������Ű ��߼ӵ� ����
	{
		_isLCollision = false;
		_speed = MIN_SPEED;
		if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_RIGHT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		if (_speed < MAX_SPEED)
		{
			if (!_isRCollision)
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
			}
		}
		else
		{
			_speed = MAX_SPEED;
		}
		if (!_isRCollision)
		{
			_x += _speed * TIMEMANAGER->getElpasedTime();
			for (int i = _proveRight - 30; i < _proveRight; ++i)
			{
				COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				// ���࿡ ���� �������Ķ����̶�� �浹�Ͻÿ� 
				if ((r == 0 && g == 255 && b == 255))
				{
					_isRCollision = true;
					_x = i - 25;
				}
				else
				{
					_isRCollision = false;
				}
			}
		}
		if (_x + 25 > _pixelData->GetWidth())
		{
			_x = _pixelData->GetWidth() - 25;
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
		_jumpPower = START_JUMPP;
		_gravity = GRAVITY;
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


void player_Eric::rectBrokenWallCollision()
{
}

void player_Eric::pixelTopWallCollision()
{
	for (int i = _proveTop; i < _proveTop + 30; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// ���࿡ ���� ����Ÿ��� �浹�Ͻÿ� 
		if ((r == 255 && g == 255 && b == 0))
		{
			_y = i + 35;
			_jumpPower = 0;
			break;
		}
	}
}

void player_Eric::pixelBottomCollision()
{
	//���࿡ �����Ѵٸ� �ȼ��浹�Ͻø����� 
	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT) return;

	for (int i = _proveBottom - 30; i < _proveBottom + 4; ++i)
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

void player_Eric::jump()
{
	if (_isJump)
	{
		_y -= _jumpPower * TIMEMANAGER->getElpasedTime();
		_jumpPower -= _gravity * TIMEMANAGER->getElpasedTime();

		if (_jumpPower > 0)
		{
			pixelTopWallCollision();
		}
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
}
