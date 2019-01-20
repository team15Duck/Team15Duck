#include "stdafx.h"
#include "player_Baleog.h"
//#include "objectManager.h"

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

	KEYANIMANAGER->update(_aniImageKey);
	
}



void player_Baleog::render()
{
	RectangleBrush(CAMERA->getMemDC(), _playerRect, RGB(255, 0, 0), false);
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _playerAni);
}



void player_Baleog::keyPressMove()
{
	//============== 왼 쪽 ================
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))			//왼쪽 움직임을 처음 시작하면 _state와 _playerAni의 값을 바꿔 주기 위해서 넣었습니다.
	{
		pixelLeftWallCollision();
		if (!_isChangeAni && !_isPushWall)
		{
			_state = PLAYER_MOVE_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "moveLeft");
			_playerAni->start();
		}
		else if (_isPushWall && _speed == 0)
		{
			_state = PLAYER_PUSH_WALL_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallLeft");
			_playerAni->start();
			_isChangeAni = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//왼쪽으로 움직임(지속)
	{
		//왼쪽으로 움직이다가 image 밖으로 나가려고 하면 speed 값을 0으로 줌
		if (_playerRect.left <= 0)
		{
			_speed = 0;
			if (!_isPushWall)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallLeft");
				_playerAni->start();
				_isPushWall = true;
			}
		}
		pixelLeftWallCollision();
		if (_isPushWall)
		{
			if (!_isChangeAni && _speed == 0)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallLeft");
				_playerAni->start();
				_isChangeAni = true;
			}
		}
		_x -= _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))			//왼쪽 움직임에서 손을 떼면
	{
		_speed = 2.0f;								//스피드 값을 다시 줌(벽에 부딪힌 경우 speed값을 0으로 두었기 때문에 되돌려주는 코드임)
		_state = PLAYER_IDLE_LEFT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleLeft");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
	}
	//============== 오 른 쪽 ================
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))		//오른쪽 움직임을 처음 시작하면 _state와 _playerAni의 값을 바꿔주기 위해서 넣었습니다.
	{
		pixelRightWallCollision();
		if (!_isChangeAni && !_isPushWall)
		{
			_state = PLAYER_MOVE_RIGHT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "moveRight");
			_playerAni->start();
		}
		else if (_isPushWall)
		{
			_state = PLAYER_PUSH_WALL_RIGHT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallRight");
			_playerAni->start();
			_isChangeAni = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//오른쪽으로 움직임 지속
	{
		//오른쪽으로 움직이다가 image 밖으로 나가려고 하면 speed 값을 0으로 줌
		if (_playerRect.right >= _pixelData->GetWidth())
		{
			_speed = 0;
			if (!_isPushWall)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallRight");
				_playerAni->start();
				_isPushWall = true;
			}
		}
		pixelRightWallCollision();
		if (_isPushWall)
		{
			if (!_isChangeAni)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallRight");
				_playerAni->start();
				_isChangeAni = true;
			}
		}
		_x += _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))			//오른쪽 움직임에서 손을 떼면
	{
		_speed = 2.0f;								//스피드값을 다시 줌(벽에 부딪힌 경우 speed 값을 0으로 바꾸었기 때문에 되돌려 줘야함)
		_state = PLAYER_IDLE_RIGHT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
	}

	//playerCollisionLadder();
	//============== 위 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = PLAYER_LADDER_UP;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//사다리와 충돌 됐는지 여부를 체크할 임시 RECT
		RECT collisionTempRect;
		//int tempIndex = _object->getFieldLadders().size();
		//for (int i = 0; i < tempIndex; ++i)
		{
			//if (IntersectRect(&collisionTempRect, (&_object->getFieldLadders()[i]->getObjectRect()), &_playerRect))
			//{
				_y -= _speed;

			//}
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_playerAni->pause();
	}

	//============== 아 래 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_state = PLAYER_LADDER_DOWN;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderDown");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_playerAni->pause();
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
	_x = 1950;
	//_x = WINSIZEX / 2 - 200;
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

	_isLadder = false;			//사다리 탔어?
	_isLadderTop = false;		//사다리의 맨위야?
	_isChangeAni = false;		//애니메이션 바꿔야댐??
	_isPushWall = false;		//벽 밀고 있어?

	
	keyAniSetting();

}


void player_Baleog::pixelLeftWallCollision()
{
	//왼쪽 벽 충돌(픽셀충돌)
	for (int i = _proveLeft + 5; i > _proveLeft; --i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_LEFT;			//상태값은 벽을 미는 상태(왼쪽)로 줌
			_speed = 0.f;							//막혀서 더이상 못움직임
			
			_isPushWall = true;
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

			_isPushWall = true;
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
	//이미지 추가
	_imageKey = "baleog";
	_aniImageKey = "player_Baleog";
	_player = IMAGEMANAGER->addFrameImage(_imageKey, "image/baleog.bmp", 630, 1260, 9, 18, true, RGB(255, 0, 255));

	//키 이름의 캐릭터를 생성함(맵)
	KEYANIMANAGER->addAnimationType(_aniImageKey);
	/*
	//공통
		//PLAYER_IDLE_RIGHT,	PLAYER_IDLE_LEFT,
		//PLAYER_IDLE_SPECIAL_RIGHT,	PLAYER_IDLE_SPECIAL_LEFT,
		//PLAYER_MOVE_RIGHT,	PLAYER_MOVE_LEFT,
		//PLAYER_FALL_RIGHT,	PLAYER_FALL_LEFT,
		//PLAYER_HIGH_FALL_RIGHT,	PLAYER_HIGH_FALL_LEFT,
		//PLAYER_PUSH_WALL_RIGHT,	PLAYER_PUSH_WALL_LEFT,
		//PLAYER_LADDER_UP,	PLAYER_LADDER_DOWN, 	PLAYER_LADDER_END,
		//PLAYER_HIT_RIGHT,	PLAYER_HIT_LEFT,
		//PLAYER_HIT_DEATH_RIGHT, 	PLAYER_HIT_DEATH_LEFT,
		//PLAYER_FALL_DEATH_RIGHT,	PLAYER_FALL_DEATH_LEFT,
		//PLAYER_FIRE_DEATH_RIGHT,	PLAYER_FIRE_DEATH_LEFT,

		//PLAYER_LOOK_FRONT_RIGHT,	PLAYER_LOOK_FRONT_LEFT,
		//PLAYER_ATTACK_RIGHT,	PLAYER_ATTACK_LEFT,
		//PLAYER_ARROW_RIGHT,	PLAYER_ARROW_LEFT,
	*/

	int normalIdleRight[] = { 0, 1};										//enume : PLAYER_IDLE_RIGHT 0
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "normalIdleRight", _imageKey, normalIdleRight, 2, 2, true);
		
	int normalIdleLeft[] = { 3, 4 };										//enume : PLAYER_IDLE_LEFT 1
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "normalIdleLeft", _imageKey, normalIdleLeft, 2, 2, true);

	int specialIdleRight[] = { 9, 10, 11, 12, 13, 14, 15, 16, 17 };			//enume : PLAYER_PLAYER_IDLE_SPECIAL_RIGHT 2
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleRight", _imageKey, specialIdleRight, 9, 6, true);
	//
	int specialIdleLeft[]{ 18, 19, 20, 21, 22, 23, 24, 25, 26 };			//enume : PLAYER_PLAYER_IDLE_SPECIAL_LEFT 3
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleLeft", _imageKey, specialIdleLeft, 9, 6, true);

	int moveRight[] = { 27, 28, 29, 30, 31, 32, 33, 34 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "moveRight", _imageKey, moveRight, 8, 10, true);

	int moveLeft[] = { 36, 37, 38, 39, 40, 41, 42, 43 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "moveLeft", _imageKey, moveLeft, 8, 10, true);

	int fallRight[] = { 63, 64 };		//낮은 곳에서 떨어지는 중
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallRight", _imageKey, fallRight, 2, 8, true);

	int fallLeft[] = { 72, 73 };		//낮은 곳에서 떨어지는 중
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallLeft", _imageKey, fallLeft, 2, 8, true);

	int highFallRight[] = { 65 };		//높은 곳에서 떨어지는 중
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallRight", _imageKey, highFallRight, 1, 6, true);

	int highFallLeft[] = { 74 };		//높은 곳에서 떨어지는 중
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallLeft", _imageKey, highFallLeft, 1, 6, true);

	int highFallEndRight[] = { 66, 67, 68, 69, 70 };				//높은 곳에서 떨어지면서 rect의 bottom이 바닥에 닿은 경우에 이 애니메이션 추가(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndRight", _imageKey, highFallEndRight, 5, 6, true);

	int highFallEndLeft[] = { 75, 76, 77, 78, 79 };					//높은 곳에서 떨어지면서 rect의 bottom이 바닥에 닿은 경우에 이 애니메이션 추가(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndLeft", _imageKey, highFallEndLeft, 5, 6, true);

	int pushWallRight[] = { 45, 46, 47, 48 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "pushWallRight", _imageKey, pushWallRight, 4, 7, true);

	int pushWallLeft[] = { 49, 50, 51, 52 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "pushWallLeft", _imageKey, pushWallLeft, 4, 7, true);

	int ladderUp[] = { 54, 55, 56, 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderUp", _imageKey, ladderUp, 4, 7, true);

	int ladderDown[] = { 57, 56, 55, 54 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderDown", _imageKey, ladderDown, 4, 7, true);

	int ladderEnd[] = { 58, 59 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderEnd", _imageKey, ladderEnd, 2, 7, true);				//아직 끝 부분 조건을 안걸어서 잘 나오는지 확인 못해영 (사다리 다 처리하고 나면 확인할게영)

	int hitRight[] = { 123 };												//몬스터에게 맞으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitRight", _imageKey, hitRight, 1, 3, true);

	int hitLeft[] = { 132 };												//몬스터에게 맞으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitLeft", _imageKey, hitLeft, 1, 3, true);

	int hitDeathRight[] = { 117, 118, 119, 120, 121, 122 };					//몬스터에게 맞고 죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathRight", _imageKey, hitDeathRight, 6, 3, true);

	int hitDeathLeft[] = { 126, 127, 128, 129, 130, 131 };					//몬스터에게 맞고 죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathLeft", _imageKey, hitDeathLeft, 6, 3, true);

	int fallDeathRight[] = { 135, 136, 137, 138, 139 };						//떨어지다가 죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathRight", _imageKey, fallDeathRight, 5, 3, true);

	int fallDeathLeft[] = { 140, 141, 142, 143, 144 };						//떨어지다가 죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathLeft", _imageKey, fallDeathLeft, 5, 3, true);

	int fireDeathRight[] = { 145, 146, 147, 148, 149, 150, 151, 152 };		//불타죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathRight", _imageKey, fireDeathRight, 8, 6, true);

	int fireDeathLeft[] = { 153, 154, 155, 156, 157, 158, 159, 160 };		//불타죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathLeft", _imageKey, fireDeathLeft, 8, 6, true);

	int lookFrontRight[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontRight", _imageKey, lookFrontRight, 1, 6, true);

	int lookFrontLeft[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontLeft", _imageKey, lookFrontLeft, 1, 6, true);

	int attackLengthRight[] = { 81, 82, 83, 84 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthRight", _imageKey, attackLengthRight, 4, 6, true);

	int attackLengthLeft[] = { 85, 86, 87, 88 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthLeft", _imageKey, attackLengthLeft, 4, 6, true);

	int attackWidthRight[] = { 90, 91, 92, 93 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthRight", _imageKey, attackWidthRight, 4, 6, true);

	int attackWidthLeft[] = { 94, 95, 96, 97 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthLeft", _imageKey, attackWidthLeft, 4, 6, true);

	int arrowRight[] = { 99, 100, 101, 102, 103, 104, 105, 106 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowRight", _imageKey, arrowRight, 8, 6, true);

	int arrowLeft[] = { 108, 109, 110, 111, 112, 113, 114, 115 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowLeft", _imageKey, arrowLeft, 8, 6, true);

	//_state = PLAYER_IDLE_RIGHT;
	_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
	_playerAni->start();
}

/*
void player_Baleog::playerCollisionLadder(object * ladder)
{
	//============== 위 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = PLAYER_LADDER_UP;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//사다리와 충돌 됐는지 여부를 체크할 임시 RECT
		RECT collisionTempRect;
		//int tempIndex = _object->getFieldLadders().size();
		
		_y -= _speed;

		
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_playerAni->pause();
	}

	//============== 아 래 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_state = PLAYER_LADDER_DOWN;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderDown");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += _speed;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_playerAni->pause();
	}
}
*/