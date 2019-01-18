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

	//충돌처리용 초기화 
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
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))								// 왼쪽키 출발속도 세팅
	{
		_isRCollision = false;
		_speed = MIN_SPEED;
		if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_LEFT;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))								//왼쪽으로 가속도 붙이며 이동하는 키세팅  
	{
		if (_speed < MAX_SPEED)											//만약에 속도가 맥스 속도보다 작다면
		{
			if (!_isLCollision)											//만약에 벽에 안박았다면
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();	//스피드를 계속 더해주는데 가속도 * 시간
			}
		}
		else															//맥스 속도보다 작은게 아니라면
		{
			_speed = MAX_SPEED;											//스피드는 더이상 커지지 않게 최대 속도로 고정한다.
		}
		if (!_isLCollision)											//만약에 벽에 안박았다면
		{
			_x -= _speed * TIMEMANAGER->getElpasedTime();			// 캐릭터는 계속 속도 * 시간으로 움직인다.
			for (int i = _proveLeft; i < _proveLeft + 30; ++i)
			{
				COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

				int r = GetRValue(color);
				int g = GetGValue(color);
				int b = GetBValue(color);

				// 만약에 색이 눈아픈파랑색이라면 충돌하시오 
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
		if (_x - 25 < 0)												// 만약에 캐릭터가 크기를 넘어가려고 한다면
		{
			_x = 25;													// x의 값을 25로 고정한다.
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))							//오른쪽키 출발속도 세팅
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

				// 만약에 색이 눈아픈파랑색이라면 충돌하시오 
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

		// 만약에 색이 마젠타라면 충돌하시오 
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
	//만약에 점프한다면 픽셀충돌하시마씨오 
	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT) return;

	for (int i = _proveBottom - 30; i < _proveBottom + 4; ++i)
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
