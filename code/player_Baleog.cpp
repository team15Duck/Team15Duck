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
	_x = WINSIZEX/2;
	_y = 1340;
	_speed = 1.f;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//rect�� ������ proveBottom
	_proveBottom = _playerRect.bottom + 5;
	

	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	pixelBottomCollision();
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom + 5;
}

void player_Baleog::render()
{
	
}

void player_Baleog::render(HDC cameraDC)
{
	Rectangle(cameraDC, _playerRect);
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
	//for(int i = _proveLeft - )
}

void player_Baleog::rectBrokenWallCollision()
{
	//�μ����� ���� rect�ε� �� ���̶� �ε��� ���
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
