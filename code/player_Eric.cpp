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
	// 왼쪽키 출발속도 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_speed = MIN_SPEED;
		/*if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_LEFT;
		}*/
	}
	// 왼쪽으로 가속도 붙이며 이동하는 키세팅  
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//만약에 속도가 맥스 속도보다 작다면
		if (_speed < MAX_SPEED)
		{
			//스피드를 계속 더해주는데 가속도 * 시간
			_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
		}
		// 맥스 속도보다 작은게 아니라면
		else
		{
			//스피드는 더이상 커지지 않게 최대 속도로 고정한다.
			_speed = MAX_SPEED;
		}
		//만약에 플레이어 렉트의 왼쪽이 맵의 왼쪽 크기를 넘어가려고 한다면
		if (_x - 25 < 0)
		{
			// 넘어가지 못하게 막는다
			_x += _speed;
		}
		// 맵의 크기를 넘어가려고 하지않는다면 
		else
		{
			// 캐릭터는 계속 속도 * 시간으로 움직인다.
			_x -= _speed * TIMEMANAGER->getElpasedTime();
			// 만약에 캐릭터가 크기를 넘어가려고 한다면
			if (_x - 25 < 0)
			{
				// x의 값을 25로 고정한다.
				_x = 25;
			}
		}
	}
	//오른쪽키 출발속도 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_speed = MIN_SPEED;
	}
	// 오른쪽으로 가속도 붙이며 이동하는 키세팅
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//만약에 스피드가 최대 속도보다 작다면
		if (_speed < MAX_SPEED)
		{
			// 속도늘리기
			_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
		}
		//그게 아니라면
		else
		{
			// 속도는 최대 속도로 고정한다.
			_speed = MAX_SPEED;
		}
		//만약에 플레이어 렉트의 오른쪽이 맵의 오른쪽 크기를 넘어가려고 한다면
		if (_x + 25 > _pixelData->GetWidth())
		{
			// 넘어가지 못하게 막는다
			_x -= _speed;
		}
		// 맵의 크기를 넘어가려고 하지않는다면 
		else
		{
			// 캐릭터는 계속 속도 * 시간으로 움직인다.
			_x += _speed * TIMEMANAGER->getElpasedTime();
			// 만약에 캐릭터가 크기를 넘어가려고 한다면
			if (_x + 25 > _pixelData->GetWidth())
			{
				// x의 값을 맵 전체크기 -25로 고정한다.
				_x = _pixelData->GetWidth() - 25;
			}
		}
	}
}

void player_Eric::keyPressSpace()
{
	//예외처리 
	if (!(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT ||
		_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT))
	{
		return;
	}
	//만약에 스페이스바를 누르면 점프해라
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
	//만약에 점프한다면 픽셀충돌하시마씨오 
	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT) return;

	for (int i = _proveBottom - 10; i < _proveBottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		// 만약에 색이 마젠타라면 충돌하시오 
		if ((r == 255 && g == 0 && b == 255))
		{
			_y = i - 35;
			_isJump = false;

			//만약에 왼쪽을 바라보는 모양으로 떨어진다면 
			if (_state == PLAYER_FALL_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;
			}
			//만약에 오른쪽을 바라보는 모양으로 떨어진다면 
			if (_state == PLAYER_FALL_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;
			}

			break;
		}
	}
}
