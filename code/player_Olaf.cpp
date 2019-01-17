#include "stdafx.h"
#include "player_Olaf.h"


player_Olaf::player_Olaf()
{
}


player_Olaf::~player_Olaf()
{
}

HRESULT player_Olaf::init()
{
	//�ʱ�ȭ
	initOlaf();
	//initShield();

	_proveBottom = _playerRect.bottom + 5;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left + 5;

	return S_OK;
}

void player_Olaf::release()
{
}

void player_Olaf::update()
{
	//�浹ó��
	pixelBottomCollision();
	pixelHorizenWallCollision();

	//����
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom + 5;
	_proveRight = _playerRect.right;// + 5;
	_proveLeft = _playerRect.left;// -5;
	
	//���а���
	stateShield();
}

void player_Olaf::render()
{
	Rectangle(CAMERA->getMemDC(), _playerRect);
	Rectangle(CAMERA->getMemDC(), _shield);
}

void player_Olaf::keyPressMove()
{
	//���и� ���� ��� ���� �ʴٸ�
	if (!_isShieldUp)
	{
		//������ ����Ű�� ������
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = PLAYER_MOVE_RIGHT;							//���������� �̵��Ѵ�.
			_x += _speed;
		}
		//������ ����Ű�� ����
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = PLAYER_IDLE_RIGHT;							//�������� ����.
			_speed = 2.0f;

		}
		//���� ����Ű�� ������
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = PLAYER_MOVE_LEFT;							//�������� �̵��Ѵ�.
			_x -= _speed;
		}
		//���� ����Ű�� ����
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = PLAYER_IDLE_LEFT;							//������ ����.
			_speed = 2.0f;
		
		}
	}
	//���и� ���� ��� �ִٸ�
	else
	{
		//������ ����Ű�� ������
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = PLAYER_SHIELD_MOVE_RIGHT;					//���и� ��� ���������� �̵��Ѵ�.
			_x += _speed;
		}
		//������ ����Ű�� ����
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = PLAYER_SHIELD_IDLE_RIGHT;					//���и� ��� �������� ����.
			_speed = 2.0f;
			
		}
		//���� ����Ű�� ������
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = PLAYER_SHIELD_MOVE_LEFT;					//���и� ��� �������� �̵��Ѵ�.
			_x -= _speed;
		}
		//���� ����Ű�� ����
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = PLAYER_SHIELD_IDLE_LEFT;					//���и� ��� ������ ����.
			_speed = 2.0f;
		}
	}
}

void player_Olaf::keyPressSpace()
{

	//��Ÿ���� ź ���¿����� SPACE ������ ���°� �ٲ��� �ʴ´�.
	//���и� ���� ��� ���� �ʴٸ�
	if (!_isShieldUp)
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//���°� ����ȴ�.
			_isShieldUp = true;

			//�÷��̾� ���°� �������� ���� �ִٸ�
			if (_state == PLAYER_IDLE_RIGHT)
			{
				_state = PLAYER_SHIELD_IDLE_RIGHT;					//���и� ���� ��� �������� ����.
			}
			//������ ���� �ִٸ�
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//���и� ���� ��� ������ ����.
			}
			//���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//���и� ���� ��� ���������� �̵��Ѵ�.
			}
			//�������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//���и� ���� ��� �������� �̵��Ѵ�.
			}
			//���������� �������� �ִٸ�
			if (_state == PLAYER_FALL_RIGHT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_SHIELD_FALL_RIGHT;					//���и� ���� ��� ���������� õõ�� ��������.
			}
			//�������� �������� �ִٸ�
			if (_state == PLAYER_FALL_LEFT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_SHIELD_FALL_LEFT;					//���и� ���� ��� �������� õõ�� ��������.
			}
		}
	}
	else
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//���°� ����ȴ�.
			_isShieldUp = false;

			//�÷��̾� ���°� ���и� ���� ��� �������� ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;							//�������� ����.
			}
			//���и� ���� ��� ������ ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//������ ����.
			}
			//���и� ���� ��� ���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//���������� �̵��Ѵ�.
			}
			//���и� ���� ��� �������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//�������� �̵��Ѵ�.
			}
			//���и� ���� ��� ���������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_RIGHT;							//���������� ��������.
			}
			//���и� ���� ��� �������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_LEFT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_LEFT;							//�������� ��������.
			}
		}
	}
}

void player_Olaf::keyPressD()
{

	//D�� ���������� ��Ÿ���� ź ���¿����� ���°� �ٲ��� �ʴ´�.
	//���и� ���� ��� ���� �ʴٸ�
	if (!_isShieldUp)
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//���°� ����ȴ�.
			_isShieldUp = true;

			//�÷��̾� ���°� �������� ���� �ִٸ�
			if (_state == PLAYER_IDLE_RIGHT)
			{
				_state = PLAYER_SHIELD_IDLE_RIGHT;					//���и� ���� ��� �������� ����.
			}
			//������ ���� �ִٸ�
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//���и� ���� ��� ������ ����.
			}
			//���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//���и� ���� ��� ���������� �̵��Ѵ�.
			}
			//�������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//���и� ���� ��� �������� �̵��Ѵ�.
			}
			//���������� �������� �ִٸ�
			if (_state == PLAYER_FALL_RIGHT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_SHIELD_FALL_RIGHT;					//���и� ���� ��� ���������� õõ�� ��������.
			}
			//�������� �������� �ִٸ�
			if (_state == PLAYER_FALL_LEFT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_SHIELD_FALL_LEFT;					//���и� ���� ��� �������� õõ�� ��������.
			}
		}
	}
	else
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//���°� ����ȴ�.
			_isShieldUp = false;

			//�÷��̾� ���°� ���и� ���� ��� �������� ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;							//�������� ����.
			}
			//���и� ���� ��� ������ ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//������ ����.
			}
			//���и� ���� ��� ���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//���������� �̵��Ѵ�.
			}
			//���и� ���� ��� �������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//�������� �̵��Ѵ�.
			}
			//���и� ���� ��� ���������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_RIGHT;							//���������� ��������.
			}
			//���и� ���� ��� �������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_LEFT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_LEFT;							//�������� ��������.
			}
		}
	}
}

void player_Olaf::initOlaf()
{
	_x = WINSIZEX / 2 + 500;
	_y = 1350;
	_speed = 2.0f;
	

	_playerRect = RectMakeCenter(_x, _y, 50, 70);
}

void player_Olaf::initShield()
{
	_isShieldUp = false;
	_shield = RectMakeCenter(_playerRect.right + 4, _playerRect.top + 35, 10, 40);
}

void player_Olaf::stateShield()
{
	if (!_isShieldUp)
	{
		if (_state == PLAYER_IDLE_RIGHT || _state == PLAYER_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right-10, _playerRect.top, 10, 70);
		}
		if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left, _playerRect.top, 10, 70);
		}
	}
	else
	{
		if (_state == PLAYER_SHIELD_IDLE_RIGHT || _state == PLAYER_SHIELD_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right-10, _playerRect.top, 50, 10);
		}
		if (_state == PLAYER_SHIELD_IDLE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left, _playerRect.top, 50, 10);
		}
	}
}

void player_Olaf::pixelHorizenWallCollision()
{
	if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT || _state == PLAYER_MOVE_RIGHT ||
		_state == PLAYER_SHIELD_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT || _state == PLAYER_SHIELD_IDLE_RIGHT)
	{
		for (int i = _proveLeft - 10; i < _proveLeft + 10; ++i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_state == PLAYER_PUSH_WALL_LEFT;
				_speed = 0.f;
				break;
			}
		}
	}
	if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_SHIELD_MOVE_RIGHT || _state == PLAYER_MOVE_LEFT || 
		_state == PLAYER_SHIELD_MOVE_LEFT || _state == PLAYER_IDLE_LEFT || _state == PLAYER_SHIELD_IDLE_LEFT)
	{
		for (int i = _proveRight - 10; i < _proveRight + 10; ++i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_state == PLAYER_PUSH_WALL_RIGHT;
				_speed = 0.f;
				break;
			}
		}
	}
}

void player_Olaf::rectBrokenWallCollision()
{
	

}

void player_Olaf::pixelBottomCollision()
{
	for (int i = _proveBottom - 10; i < _proveBottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_y = i - 35;
			break;
		}
	}
}

