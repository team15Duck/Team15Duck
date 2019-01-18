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

	_size = { 64, 64 };
	_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);


	_player = IMAGEMANAGER->addFrameImage("player_eric", "image/eric.bmp", 704, 1024, 11, 16, true, RGB(255, 0, 255));
	EricAniinit();


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
	pixelBottomCollision();
	jump();
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

	EricAni();
	_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);
}

void player_Eric::render()
{
	//Rectangle(CAMERA->getMemDC(), _playerRect, false);
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _EricMotion);
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
		EricAniStart("move_left");
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
					_x = i + (_size.x / 2);
				}
				else
				{
					_isLCollision = false;
				}
			}
		}
		if (_x - (_size.x / 2) < 0)												// 만약에 캐릭터가 크기를 넘어가려고 한다면
		{
			_x = _size.x / 2;													// x의 값을 25로 고정한다.
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_state == PLAYER_MOVE_LEFT)
		{
			_state = PLAYER_IDLE_LEFT;
		}
		EricAniStart("idleleft");
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))							//오른쪽키 출발속도 세팅
	{
		_isLCollision = false;
		_speed = MIN_SPEED;
		if (_state != PLAYER_JUMP_RIGHT || _state != PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_MOVE_RIGHT;
		}
		EricAniStart("move_right");
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
					_x = i - (_size.x / 2);
				}
				else
				{
					_isRCollision = false;
				}
			}
		}
		if (_x + (_size.x / 2) > _pixelData->GetWidth())
		{
			_x = _pixelData->GetWidth() - (_size.x / 2);
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_state == PLAYER_MOVE_RIGHT)
		{
			_state = PLAYER_IDLE_RIGHT;
		}
		EricAniStart("idleright");
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
			EricAniStart("jump_left");

		}
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
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
			_y = i + (_size.y / 2);
			_jumpPower = 0;
			break;
		}
	}
}

void player_Eric::pixelBottomCollision()
{
	//만약에 점프한다면 픽셀충돌하시마씨오 
	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT) return;

	for (int i = _proveBottom - 5; i < _proveBottom + 10; ++i)
	{
		bool collision = false;

		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			// 만약에 색이 마젠타라면 충돌하시오 
			if ((r == 255 && g == 0 && b == 255))
			{
				_y = i - (_size.y / 2);
				_isJump = false;

				//만약에 왼쪽을 바라보는 모양으로 떨어진다면 
				if (_state == PLAYER_FALL_LEFT)
				{
					_state = PLAYER_IDLE_LEFT;
					EricAniStart("idleleft");
				}
				//만약에 오른쪽을 바라보는 모양으로 떨어진다면 
				if (_state == PLAYER_FALL_RIGHT)
				{
					_state = PLAYER_IDLE_RIGHT;
					EricAniStart("idleright");
				}
				collision = true;
				break;
			}
		}
		if (collision)
		{
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
			EricAniStart("jump_fall_right");
		}
		else if (_state == PLAYER_JUMP_LEFT)
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
		}
	}
}

void player_Eric::EricAniinit()
{
	KEYANIMANAGER->addAnimationType("player_eric");
	_state = PLAYER_IDLE_RIGHT;

	int idle_right[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "idleright", "player_eric", idle_right, 2, 2, true);
	int idle_left[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "idleleft", "player_eric", idle_left, 2, 2, true);
	int move_right[] = { 11, 12, 13, 14, 15, 16, 17, 18 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "move_right", "player_eric", move_right, 8, 10, true);
	int move_left[] = { 22, 23, 24, 25, 26, 27, 28, 29 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "move_left", "player_eric", move_left, 8, 10, true);
	int jump_right[] = { 55,56 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "jump_right", "player_eric", jump_right, 2, 10, false);
	int jump_fall_right[] = { 57,58 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "jump_fall_right", "player_eric", jump_fall_right, 2, 2, false);
	int jump_left[] = { 59,60 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "jump_left", "player_eric", jump_left, 2, 10, false);
	int jump_fall_left[] = { 61,62 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "jump_fall_left", "player_eric", jump_fall_left, 2, 2, false);

	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleright");
}

void player_Eric::EricAni()
{
	if (_state == PLAYER_IDLE_RIGHT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleright");
		KEYANIMANAGER->start("player_eric", "idleright");

	}
	if (_state == PLAYER_IDLE_LEFT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleleft");
		KEYANIMANAGER->start("player_eric", "idleleft");
	}
	KEYANIMANAGER->update("player_eric");
}

void player_Eric::EricAniStart(string key)
{
	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", key);
	KEYANIMANAGER->start("player_eric", key);
}
