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
	//초기화
	initOlaf();
	initShield();

	_proveBottom = _playerRect.bottom + 5;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;

	return S_OK;
}

void player_Olaf::release()
{
}

void player_Olaf::update()
{
	//충돌처리
	pixelBottomCollision();
	//pixelHorizenWallCollision();
	//갱신
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;

	//방패갱신
	stateShield();
}

void player_Olaf::render()
{
	Rectangle(CAMERA->getMemDC(), _playerRect);
	Rectangle(CAMERA->getMemDC(), _shield);
}

void player_Olaf::keyPressMove()
{
	//방패를 위로 들고 있지 않다면
	if (!_isShieldUp)
	{
		//오른쪽 방향키를 떼면
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = PLAYER_IDLE_RIGHT;							//오른쪽을 본다.
			_speed = 2.0f;

		}
		//오른쪽 방향키를 누르면
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			pixelRightWallCollision();
			_state = PLAYER_MOVE_RIGHT;							//오른쪽으로 이동한다.
			_x += _speed;
		}
		//왼쪽 방향키를 떼면
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = PLAYER_IDLE_LEFT;							//왼쪽을 본다.
			_speed = 2.0f;

		}
		//왼쪽 방향키를 누르면
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			pixelLeftWallCollision();
			_state = PLAYER_MOVE_LEFT;							//왼쪽으로 이동한다.
			_x -= _speed;
		}

	}
	//방패를 위로 들고 있다면
	else
	{
		//오른쪽 방향키를 떼면
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_state = PLAYER_SHIELD_IDLE_RIGHT;					//방패를 들고 오른쪽을 본다.
			_speed = 2.0f;

		}
		//오른쪽 방향키를 누르면
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			pixelRightWallCollision();
			_state = PLAYER_SHIELD_MOVE_RIGHT;					//방패를 들고 오른쪽으로 이동한다.
			_x += _speed;
		}
		//왼쪽 방향키를 떼면
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_state = PLAYER_SHIELD_IDLE_LEFT;					//방패를 들고 왼쪽을 본다.
			_speed = 2.0f;
		}
		//왼쪽 방향키를 누르면
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			pixelLeftWallCollision();
			_state = PLAYER_SHIELD_MOVE_LEFT;					//방패를 들고 왼쪽으로 이동한다.
			_x -= _speed;
		}

	}
}

void player_Olaf::keyPressSpace()
{

	//사타리를 탄 상태에서는 SPACE 눌러도 상태가 바뀌지 않는다.
	//방패를 위로 들고 있지 않다면
	if (!_isShieldUp)
	{
		//스페이스바를 눌렀을때 방패의 위치가 변경된다.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//상태가 변경된다.
			_isShieldUp = true;

			//플레이어 상태가 오른쪽을 보고 있다면
			if (_state == PLAYER_IDLE_RIGHT)
			{
				_state = PLAYER_SHIELD_IDLE_RIGHT;					//방패를 위로 들고 오른쪽을 본다.
			}
			//왼쪽을 보고 있다면
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//방패를 위로 들고 왼쪽을 본다.
			}
			//오른쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//방패를 위로 들고 오른쪽으로 이동한다.
			}
			//왼쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//방패를 위로 들고 왼쪽으로 이동한다.
			}
			//오른쪽으로 떨어지고 있다면
			if (_state == PLAYER_FALL_RIGHT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_SHIELD_FALL_RIGHT;					//방패를 위로 들고 오른쪽으로 천천히 떨어진다.
			}
			//왼쪽으로 떨어지고 있다면
			if (_state == PLAYER_FALL_LEFT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_SHIELD_FALL_LEFT;					//방패를 위로 들고 왼쪽으로 천천히 떨어진다.
			}
		}
	}
	else
	{
		//스페이스바를 눌렀을때 방패의 위치가 변경된다.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//상태가 변경된다.
			_isShieldUp = false;

			//플레이어 상태가 방패를 위로 들고 오른쪽을 보고 있다면
			if (_state == PLAYER_SHIELD_IDLE_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;							//오른쪽을 본다.
			}
			//방패를 위로 들고 왼쪽을 보고 있다면
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//왼쪽을 본다.
			}
			//방패를 위로 들고 오른쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//오른쪽으로 이동한다.
			}
			//방패를 위로 들고 왼쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//왼쪽으로 이동한다.
			}
			//방패를 위로 들고 오른쪽으로 떨어지고 있다면
			if (_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_FALL_RIGHT;							//오른쪽으로 떨어진다.
			}
			//방패를 위로 들고 왼쪽으로 떨어지고 있다면
			if (_state == PLAYER_SHIELD_FALL_LEFT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_FALL_LEFT;							//왼쪽으로 떨어진다.
			}
		}
	}
}

void player_Olaf::keyPressD()
{

	//D도 마찬가지로 사타리를 탄 상태에서는 상태가 바뀌지 않는다.
	//방패를 위로 들고 있지 않다면
	if (!_isShieldUp)
	{
		//스페이스바를 눌렀을때 방패의 위치가 변경된다.
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//상태가 변경된다.
			_isShieldUp = true;

			//플레이어 상태가 오른쪽을 보고 있다면
			if (_state == PLAYER_IDLE_RIGHT)
			{
				_state = PLAYER_SHIELD_IDLE_RIGHT;					//방패를 위로 들고 오른쪽을 본다.
			}
			//왼쪽을 보고 있다면
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//방패를 위로 들고 왼쪽을 본다.
			}
			//오른쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//방패를 위로 들고 오른쪽으로 이동한다.
			}
			//왼쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//방패를 위로 들고 왼쪽으로 이동한다.
			}
			//오른쪽으로 떨어지고 있다면
			if (_state == PLAYER_FALL_RIGHT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_SHIELD_FALL_RIGHT;					//방패를 위로 들고 오른쪽으로 천천히 떨어진다.
			}
			//왼쪽으로 떨어지고 있다면
			if (_state == PLAYER_FALL_LEFT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_SHIELD_FALL_LEFT;					//방패를 위로 들고 왼쪽으로 천천히 떨어진다.
			}
		}
	}
	else
	{
		//스페이스바를 눌렀을때 방패의 위치가 변경된다.
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			//상태가 변경된다.
			_isShieldUp = false;

			//플레이어 상태가 방패를 위로 들고 오른쪽을 보고 있다면
			if (_state == PLAYER_SHIELD_IDLE_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;							//오른쪽을 본다.
			}
			//방패를 위로 들고 왼쪽을 보고 있다면
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//왼쪽을 본다.
			}
			//방패를 위로 들고 오른쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//오른쪽으로 이동한다.
			}
			//방패를 위로 들고 왼쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//왼쪽으로 이동한다.
			}
			//방패를 위로 들고 오른쪽으로 떨어지고 있다면
			if (_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_FALL_RIGHT;							//오른쪽으로 떨어진다.
			}
			//방패를 위로 들고 왼쪽으로 떨어지고 있다면
			if (_state == PLAYER_SHIELD_FALL_LEFT)
			{
				//여기서 떨어지는 속도값 설정
				_state = PLAYER_FALL_LEFT;							//왼쪽으로 떨어진다.
			}
		}
	}
}

void player_Olaf::initOlaf()
{
	_x = WINSIZEX / 2 + 500;				   //X좌표
	_y = 1350;								   //Y좌표
	_speed = 2.0f;							   //스피드
	_lifeCount = 3;							   //체력


	_playerRect = RectMakeCenter(_x, _y, 50, 70); //올라프렉트생성
}

void player_Olaf::initShield()
{
	_isShieldUp = false;																//방패들었니?
	_shield = RectMake(_playerRect.right - 10, _playerRect.top, 10, 40);				//방패렉트생성
}

void player_Olaf::stateShield()
{
	//방패를 위로 안들었다면
	if (!_isShieldUp)
	{
		//플레이어가 오른쪽을 보고 있다면
		if (_state == PLAYER_IDLE_RIGHT || _state == PLAYER_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right - 10, _playerRect.top, 10, 70);			//오른쪽으로 방패렉트를 갱신한다.
		}
		//플레이어가 왼쪽을 보고 있다면
		if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left, _playerRect.top, 10, 70);				//왼쪽으로 방패렉트를 갱신한다.
		}
	}
	//방패를 위로 들었다면
	else
	{
		//플레이어가 오른쪽을 보고 있다면
		if (_state == PLAYER_SHIELD_IDLE_RIGHT || _state == PLAYER_SHIELD_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right - 50, _playerRect.top, 50, 10);			//오른쪽으로 방패렉트를 갱신한다.
		}
		//플레이어가 왼쪽을 보고 있다면
		if (_state == PLAYER_SHIELD_IDLE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left, _playerRect.top, 50, 10);				//왼쪽으로 방패렉트를 갱신한다.
		}
	}
}

void player_Olaf::pixelLeftWallCollision()
{
	for (int i = _proveLeft; i < _proveLeft + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state == PLAYER_PUSH_WALL_LEFT;				//상태는 왼쪽 벽을 민다.
			_speed = 0.f;									//스피드를 0으로 내려 이동하지 않도록 한다.
			break;
		}
	}
}

void player_Olaf::pixelRightWallCollision()
{
	for (int i = _proveRight - 5; i < _proveRight; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state == PLAYER_PUSH_WALL_RIGHT;				//상태는 오른쪽 벽을 민다.
			_speed = 0.f;									//스피드를 0으로 내려 이동하지 않도록 한다.
			break;
		}
	}
}

void player_Olaf::rectBrokenWallCollision()
{


}

void player_Olaf::pixelBottomCollision()
{
	for (int i = _proveBottom - 5; i < _proveBottom + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_y = i - 35;										   //플레이어 좌표 보정
			break;
		}
	}
}

