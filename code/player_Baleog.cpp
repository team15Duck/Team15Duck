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
	
	_speed = 2.f;
	pixelBottomCollision();
	rectBrokenWallCollision();
	_playerRect = RectMakeCenter(_x, _y, 50, 70);
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	KEYANIMANAGER->update("player_Baleog");
	
}



void player_Baleog::render()
{
	RectangleBrush(CAMERA->getMemDC(), _playerRect, RGB(255, 0, 0), false);
	//RectangleBrush(CAMERA->getMemDC(), _tempWall, RGB(0, 255, 0), false);
	//RectangleBrush(CAMERA->getMemDC(), _tempLadder, RGB(100, 50, 10), false);
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _playerAni);
}



void player_Baleog::keyPressMove()
{

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))		//왼쪽 움직임에서 손을 떼면
	{
		_speed = 2.0f;								//스피드 값을 다시 줌(벽에 부딪힌 경우 speed값을 0으로 두었기 때문에 되돌려주는 코드임)
		_state = PLAYER_IDLE_LEFT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation("player_Baleog","normalIdleLeft");
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//왼쪽으로 움직임
	{
		//왼쪽으로 움직이다가 image 밖으로 나가려고 하면 speed 값을 0으로 줌
		if (_playerRect.left <= 0)
		{
			_speed = 0;
		}
		pixelLeftWallCollision();
		_state = PLAYER_MOVE_LEFT;					//상태값을 왼쪽 움직임 넣음
		_x -= _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))		//오른쪽 움직임에서 손을 떼면
	{
		_speed = 2.0f;								//스피드값을 다시 줌(벽에 부딪힌 경우 speed 값을 0으로 바꾸었기 때문에 되돌려 줘야함)
		_state = PLAYER_IDLE_RIGHT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation("player_Baleog", "normalIdleRight");
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//오른쪽으로 움직이다가 image 밖으로 나가려고 하면 speed 값을 0으로 줌
		if (_playerRect.right >= _pixelData->GetWidth())
		{
			_speed = 0;
		}
		pixelRightWallCollision();
		_state = PLAYER_MOVE_RIGHT;					//상태값을 오른쪽 움직임으로 줌.
		_x += _speed;

	}

	//일단 위로도 움직여 보자
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//사다리와 충돌 됐는지 여부를 체크할 임시 RECT
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
	//일반 공격
	//0 혹은 1 중에서 일정 확률로 0일 때는 가로 긋기, 1일 때는 세로 긋기
}

void player_Baleog::keyPressD()
{
	//활쏘기
}

void player_Baleog::initBaleog()
{
	//_x = 1950;
	_x = WINSIZEX / 2 - 200;
	_y = 1350;
	_speed = 2.f;
	_gravity = 0;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//pixel 충돌 탐지할 변수
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	//임시 충돌 체크용 Rect
	//_tempWall = RectMakeCenter(300, 1325, 50, 100);
	//_tempLadder = RectMakeCenter(192, 840, 50, 1130);

	_isLadder = false;
	_isLadderTop = false;


	
	keyAniSetting();

}


void player_Baleog::pixelLeftWallCollision()
{
	//왼쪽 벽 충돌(픽셀충돌)
	for (int i = _proveLeft; i < _proveLeft + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_LEFT;			//상태값은 벽을 미는 상태(왼쪽)로 줌
			_speed = 0.f;							//막혀서 더이상 못움직임
			break;
		}
	}
}

void player_Baleog::pixelRightWallCollision()
{
	//오른쪽 벽 충돌(픽셀충돌)
	for (int i = _playerRect.right - 5; i < _playerRect.right; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_RIGHT;		//상태값은 벽을 미는 상태(오른쪽)로 줌
			_speed = 0.f;
			break;
		}
	}

}

void player_Baleog::rectBrokenWallCollision()
{
	//부서지는 벽은 rect인데 그 벽이랑 부딪힌 경우
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
	//바닥충돌처리(픽셀충돌)
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

void player_Baleog::keyAniSetting()
{
	/*
	//공통
	PLAYER_IDLE_RIGHT,	PLAYER_IDLE_LEFT,
	PLAYER_IDLE_SPECIAL_RIGHT,	PLAYER_IDLE_SPECIAL_LEFT,
	PLAYER_MOVE_RIGHT,	PLAYER_MOVE_LEFT,
	PLAYER_FALL_RIGHT,	PLAYER_FALL_LEFT,
	PLAYER_HIGH_FALL_RIGHT,	PLAYER_HIGH_FALL_LEFT,
	PLAYER_PUSH_WALL_RIGHT,	PLAYER_PUSH_WALL_LEFT,
	PLAYER_LADDER_UP,	PLAYER_LADDER_DOWN, 	PLAYER_LADDER_END,
	PLAYER_HIT_RIGHT,	PLAYER_HIT_LEFT,
	PLAYER_HIT_DEATH_RIGHT, 	PLAYER_HIT_DEATH_LEFT,
	PLAYER_FALL_DEATH_RIGHT,	PLAYER_FALL_DEATH_LEFT,
	PLAYER_FIRE_DEATH_RIGHT,	PLAYER_FIRE_DEATH_LEFT,

	PLAYER_LOOK_FRONT_RIGHT,	PLAYER_LOOK_FRONT_LEFT,
	PLAYER_ATTACK_RIGHT,	PLAYER_ATTACK_LEFT,
	PLAYER_ARROW_RIGHT,	PLAYER_ARROW_LEFT,

	*/
	//이미지 추가
	_imageKey = "baleog";
	_aniImageKey = "player_Baleog";
	_player = IMAGEMANAGER->addFrameImage(_imageKey, "image/baleog.bmp", 630, 1260, 9, 18, true, RGB(255, 0, 255));

	//키 이름의 캐릭터를 생성함(맵)
	KEYANIMANAGER->addAnimationType(_aniImageKey);



	//=========================요 밑에 마저 추가하기=============================//


	int normalIdleRight[] = { 0, 1};										//enume : PLAYER_IDLE_RIGHT 0
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "normalIdleRight", _imageKey, normalIdleRight, 2, 2, true);
		
	int normalIdleLeft[] = { 3, 4 };										//enume : PLAYER_IDLE_LEFT 1
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "normalIdleLeft", _imageKey, normalIdleLeft, 2, 2, true);

	int specialIdleRight[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };			//enume : PLAYER_PLAYER_IDLE_SPECIAL_RIGHT 2
	KEYANIMANAGER->addArrayFrameAnimation("player_Baleog", "specialIdleRight", "baleog", specialIdleRight, 9, 6, true);
	//
	int specialIdleLeft[]{ 18, 19, 20, 21, 22, 23, 24, 25, 26 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Baleog", "specialIdleLeft", "baleog", specialIdleLeft, 9, 6, true);


	//_state = PLAYER_IDLE_RIGHT;
	_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
	_playerAni->start();
}
