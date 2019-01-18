#include "stdafx.h"
#include "player_Baleog.h"


player_Baleog::player_Baleog()
{
}


player_Baleog::~player_Baleog()
{
}

HRESULT player_Baleog::init()
{
	initBaleog();

	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	_speed = 2.0f;
	pixelBottomCollision();
	rectBrokenWallCollision();
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;
}



void player_Baleog::render()
{
	RectangleBrush(CAMERA->getMemDC(), _playerRect, RGB(255, 0, 0));
	RectangleBrush(CAMERA->getMemDC(), _tempWall, RGB(0, 255, 0));
	RectangleBrush(CAMERA->getMemDC(), _tempLadder, RGB(100, 50, 10));
}



void player_Baleog::keyPressMove()
{

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))		//���� �����ӿ��� ���� ����
	{
		_speed = 2.0f;								//���ǵ� ���� �ٽ� ��(���� �ε��� ��� speed���� 0���� �ξ��� ������ �ǵ����ִ� �ڵ���)
		_state = PLAYER_IDLE_LEFT;					//���°��� idle
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//�������� ������
	{
		//�������� �����̴ٰ� image ������ �������� �ϸ� speed ���� 0���� ��
		if (_playerRect.left <= 0)
		{
			_speed = 0;
		}
		pixelLeftWallCollision();
		_state = PLAYER_MOVE_LEFT;					//���°��� ���� ������ ����
		_x -= _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))		//������ �����ӿ��� ���� ����
	{
		_speed = 2.0f;								//���ǵ尪�� �ٽ� ��(���� �ε��� ��� speed ���� 0���� �ٲپ��� ������ �ǵ��� �����)
		_state = PLAYER_IDLE_RIGHT;					//���°��� idle
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//���������� �����̴ٰ� image ������ �������� �ϸ� speed ���� 0���� ��
		if (_playerRect.right >= _pixelData->GetWidth())
		{
			_speed = 0;
		}
		pixelRightWallCollision();
		_state = PLAYER_MOVE_RIGHT;					//���°��� ������ ���������� ��.
		_x += _speed;

	}

	//�ϴ� ���ε� ������ ����
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//��ٸ��� �浹 �ƴ��� ���θ� üũ�� �ӽ� RECT
		RECT collisionTempRect;

		float halfWidth = (_playerRect.right - _playerRect.left) / 2;
		if ((_playerRect.right - halfWidth >= _tempLadder.left &&
			_playerRect.left + halfWidth <= _tempLadder.right) ||
			_playerRect.bottom >= _tempLadder.top)
		{
			_y -= _speed;
			_state = PLAYER_LADDER_UP;
		}
	}
}

void player_Baleog::keyPressSpace()
{
	//�Ϲ� ����
	//0 Ȥ�� 1 �߿��� ���� Ȯ���� 0�� ���� ���� �߱�, 1�� ���� ���� �߱�
}

void player_Baleog::keyPressD()
{
	//Ȱ���
}

void player_Baleog::initBaleog()
{
	//_x = 1950;
	_x = WINSIZEX / 2 - 200;
	_y = 1350;
	_speed = 2.f;
	_gravity = 0;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//pixel �浹 Ž���� ����
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	//�ӽ� �浹 üũ�� Rect
	//_tempWall = RectMakeCenter(300, 1325, 50, 100);
	//_tempLadder = RectMakeCenter(192, 840, 50, 1130);

	_isLadder = false;
	_isLadderTop = false;

}


void player_Baleog::pixelLeftWallCollision()
{
	//���� �� �浹(�ȼ��浹)
	for (int i = _proveLeft; i < _proveLeft + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_LEFT;			//���°��� ���� �̴� ����(����)�� ��
			_speed = 0.f;							//������ ���̻� ��������
			break;
		}
	}
}

void player_Baleog::pixelRightWallCollision()
{
	//������ �� �浹(�ȼ��浹)
	for (int i = _playerRect.right - 5; i < _playerRect.right; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_RIGHT;		//���°��� ���� �̴� ����(������)�� ��
			_speed = 0.f;
			break;
		}
	}

}

void player_Baleog::rectBrokenWallCollision()
{
	//�μ����� ���� rect�ε� �� ���̶� �ε��� ���
	if (_state == PLAYER_MOVE_LEFT)
	{
		if (_x > _tempWall.right && _playerRect.left <= _tempWall.right)
		{
			//_state = PLAYER_PUSH_WALL_LEFT;
			//_speed = 0.f;
		}
	}
	if (_state == PLAYER_MOVE_RIGHT)
	{
		if (_x < _tempWall.left && _playerRect.right >= _tempWall.left)
		{
			//_state = PLAYER_PUSH_WALL_RIGHT;
			//_speed = 0.f;
		}
	}
}

void player_Baleog::pixelBottomCollision()
{
	//�ٴ��浹ó��(�ȼ��浹)
	for (int i = _proveBottom - 5; i < _proveBottom + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			if (_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_END || _state == PLAYER_LADDER_DOWN)
			{
				break;
			}
			_y = i - 35;
			break;
		}
	}
}
