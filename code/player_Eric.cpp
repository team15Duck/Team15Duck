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

	//이동 예외처리용 불값 초기화

	_isRightMove = false;
	_isLeftMove = false;

	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{
	//이동
	jump();
	//바닥 픽셀충돌
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

	rightMove();
	leftMove();

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
				//만약에 오른쪽 키를 누르고있다면
				if (_isRightMove && !_isJump)
				{
					_state = PLAYER_MOVE_RIGHT;
					_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "move_right");

				}
				//만약에 오른쪽을 바라보는 모양으로 떨어진다면 
				if (_state == PLAYER_FALL_RIGHT)
				{
					_state = PLAYER_IDLE_RIGHT;
					EricAniStart("idleright");
				}
				//만약에 왼쪽키를 누르고 있다면
				if (_isLeftMove && !_isJump)
				{
					_state = PLAYER_MOVE_LEFT;
					_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "move_left");
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

void player_Eric::leftMove()
{
	//오른쪽 이동이 아닐때만 왼쪽 이동이 가능하다
	if (!_isRightMove)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_isLeftMove = true;
			_isRCollision = false;
			_speed = MIN_SPEED;
			_state = PLAYER_MOVE_LEFT;
			EricAniStart("move_left");
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_isLeftMove = true;
			if (_speed < MAX_SPEED)
			{
				if (!_isLCollision)
				{
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
			}
			else
			{
				_speed = MAX_SPEED;
			}
			if (!_isLCollision)
			{
				_x -= _speed * TIMEMANAGER->getElpasedTime();
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
			if (_x - (_size.x / 2) < 0)
			{
				_x = _size.x / 2;
			}
		}
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_isLeftMove = false;
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;
			}
			EricAniStart("idleleft");
		}
	}
}

void player_Eric::rightMove()
{
	//만약에 왼쪽이동이 아닐때만 오른쪽으로 이동이 가능하다.
	if (!_isLeftMove)
	{
		//오른쪽 출발 세팅
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			//오른쪽이동 가능
			_isRightMove = true;
			//왼쪽벽에 충돌하지 않음
			_isLCollision = false;
			//속도는 미니넘 속도로
			_speed = MIN_SPEED;
			//상태는 오른쪽 이동 상태
			_state = PLAYER_MOVE_RIGHT;
			//출력되는 애니메이션은 오른쪽이동 애니메이션 
			EricAniStart("move_right");
		}
		//오른쪽 이동상태 세팅
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//만약에 스피드가 맥스스피드보다 작다면
			if (_speed < MAX_SPEED)
			{
				//만약에 오른쪽 벽이랑 충돌하고 있지 않은 상태라면
				if (!_isRCollision)
				{
					//속도는 가속도를 현재시간에 곱하면서 상승한다.
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
			}
			//만약 그상황이 아니라면
			else
			{
				//속도는 맥스스피드로 고정한다.
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
		//만약에 오른쪽이동 버튼을 누르지 않는다면 
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			//만약에 캐릭터의 상태가 오른쪽 이동 상태였다면
			if (_state == PLAYER_MOVE_RIGHT)
			{
				//오른쪽 정지상태 이미지를 출력한다.
				_state = PLAYER_IDLE_RIGHT;
			}
			//애니메이션 상태를 오른쪽정지상태 애니메이션을 출력한다.
			EricAniStart("idleright");
			//오른쪽 이동상태를 아니오로 바꿔준다.
			_isRightMove = false;
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
