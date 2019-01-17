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
	_x = WINSIZEX/2 + 100;
	_y = 1350;
	_speed = 2.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//rect�� ������ proveBottom

	_proveBottom = _playerRect.bottom + 5;
	_proveLeft = _playerRect.left + 5;
	_proveRight = _playerRect.right - 5;

	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	_speed = 2.0f;
	pixelBottomCollision();
	pixelHorizenWallCollision();
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom + 5;
	_proveLeft = _playerRect.left + 5;
	_proveRight = _playerRect.right;
}

void player_Baleog::render()
{
	
}

void player_Baleog::render(HDC cameraDC)
{
	RectangleBrush(cameraDC, _playerRect, RGB(255,0,0));
}



void player_Baleog::keyPressMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_state = PLAYER_MOVE_LEFT;
		_x -= _speed;
	}
	else if(KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_speed = 2.0f;
		_state = PLAYER_IDLE_LEFT;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_state = PLAYER_MOVE_RIGHT;
		_x += _speed;
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_speed = 2.0f;
		_state = PLAYER_IDLE_RIGHT;
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

void player_Baleog::moveRange()
{
}

void player_Baleog::pixelHorizenWallCollision()
{

	//���� �� �浹(�ȼ��浹)
	if (_state == PLAYER_MOVE_LEFT)
	{
		for (int i = _proveLeft - 10; i < _proveLeft + 10; ++i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_state = PLAYER_PUSH_WALL_LEFT;
				_speed = 0.f;

				break;
			}
		}
	}
	if (_state == PLAYER_MOVE_RIGHT)
	{
		for (int i = _playerRect.right - 5; i < _playerRect.right + 5; ++i)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if (r == 0 && g == 255 && b == 255)
			{
				_state = PLAYER_PUSH_WALL_RIGHT;
				_speed = 0.f;

				break;
			}
		}
	}
}

void player_Baleog::rectBrokenWallCollision()
{
	//�μ����� ���� rect�ε� �� ���̶� �ε��� ���
	
	//if ()
	//{
	//	_speed
	//}
}

void player_Baleog::pixelBottomCollision()
{
	//�ٴ��浹ó��(�ȼ��浹)
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
