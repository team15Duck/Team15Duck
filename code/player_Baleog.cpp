#include "stdafx.h"
#include "player_Baleog.h"

player_Baleog::player_Baleog()
: _isFire(false)
{
}


player_Baleog::~player_Baleog()
{
}

HRESULT player_Baleog::init()
{
	playerBase::init();
	initBaleog();
	
	
	return S_OK;
}

void player_Baleog::release()
{
}

void player_Baleog::update()
{
	if (!_isLadder)
	{
		pixelBottomCollision();
	}
	//rectBrokenWallCollision();

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
	//다시 움직여 보고 싶어서 넣은 키 나중에 지우기!!
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_isAlive = true;
		_deathMotion = false;
	}
	//==================== 만약에 죽었고 죽는 모션이 끝났으면 더이상의 키 입력은 없당!!!!! ====================
	if (!_isAlive && !_deathMotion)
		return;
	//==================== 만약에 죽었는데 죽는 모션이 나와야 하면 아래 실행문대로 키 애니 시작해랑(여기서 모션을 false로 바꿔줌 ====================
	if (!_isAlive && _deathMotion)
	{	
		if (_state == PLAYER_FIRE_DEATH_LEFT)
		{
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "fireDeathLeft");
			_playerAni->start();
		}
		if (_state == PLAYER_FIRE_DEATH_RIGHT)
		{
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "fireDeathRight");
			_playerAni->start();
		}
		_deathMotion = false;
		return;
	}

	//==================== 살아있다면 키 입력을 받아보장!! ====================
	collisionLadder(_ladderRc);
	//============== <<왼 쪽>> ================
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))			//왼쪽 움직임을 처음 시작하면 _state와 _playerAni의 값을 바꿔 주기 위해서 넣었습니다.
	{
		_isRight = false;
		//일단 최저 속도로 시작합시당
		_speed = _minSpeed;
		//왼쪽벽 부딪히는지 체크하장
		pixelLeftWallCollision();
		if (!_isChangeAni && !_isPushWall)
		{
			_state = PLAYER_MOVE_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "moveLeft");
			_playerAni->start();
		}
		else if (_isPushWall)
		{
			_state = PLAYER_PUSH_WALL_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "pushWallLeft");
			_playerAni->start();
			_isChangeAni = false;
		}

		if (_isLadder)
		{
			_state = PLAYER_FALL_LEFT;
			_fallStartY = _y;				//떨어지기 시작할때의 높이를 변수에 저장
			_isLadder = false;
		}

		pixelBottomCollision();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//왼쪽으로 움직임(지속)
	{
		if (_isRight)
		{
			_speed += _acceleration * TIMEMANAGER->getElpasedTime();
			if (_speed >= _maxSpeed)
			{
				_speed = _maxSpeed;
			}
			_x += _speed;
			
		}
		_speed += _acceleration * TIMEMANAGER->getElpasedTime();
		if (_speed >= _maxSpeed)
		{
			_speed = _maxSpeed;
		}
		//움직이면서 바닥 체크하고
		pixelBottomCollision();
		//방향키를 누르던 도중에 공격이 들어오면
		if (_state == PLAYER_ATTACK_LEFT || _state == PLAYER_ARROW_LEFT)
		{
			_speed = 0;
			if (!_playerAni->isPlay())
			{
				if (!_isChangeAni)
				{
					_state = PLAYER_MOVE_LEFT;
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "moveLeft");
					_playerAni->start();
					_isChangeAni = true;
				}
			}
		}

		if (!_isGround)
		{
			_state = PLAYER_FALL_LEFT;
			_isLadder = false;
		}
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
			if (!_isChangeAni)
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
		if ((_state == PLAYER_ATTACK_LEFT || _state == PLAYER_ARROW_LEFT )&& _playerAni->isPlay())
		{
			return;
		}
		_speed = 0.f;								//스피드 값을 다시 줌(벽에 부딪힌 경우 speed값을 0으로 두었기 때문에 되돌려주는 코드임)
		_state = PLAYER_IDLE_LEFT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleLeft");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
		if (!_isGround)
		{
			_state = PLAYER_FALL_LEFT;
			_isLadder = false;
		}
	}
	//============== <오 른 쪽> ================
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))		//오른쪽 움직임을 처음 시작하면 _state와 _playerAni의 값을 바꿔주기 위해서 넣었습니다.
	{
		_isRight = true;
		//스피는 최저속도로 시작합니다
		_speed = _minSpeed;
		//오른쪽 벽 충돌 체크
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
		if (_isLadder)
		{
			_state = PLAYER_FALL_RIGHT;
			_fallStartY = _y;				//떨어지기 시작할때의 높이를 변수에 저장
			_isLadder = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//오른쪽으로 움직임 지속
	{
		if (!_isRight)
		{
			_speed += _acceleration * TIMEMANAGER->getElpasedTime();
			if (_speed >= _maxSpeed)
			{
				_speed = _maxSpeed;
			}
			_x += _speed;

		}
		//속도에 가속도를 넣어보자아아
		_speed += _acceleration * TIMEMANAGER->getElpasedTime();
		if (_speed >= _maxSpeed)
		{
			_speed = _maxSpeed;
		}
		//움직이면서 바닥 체크하고
		pixelBottomCollision();
		//움직이다가 공격이 들어오면
		if (_state == PLAYER_ATTACK_RIGHT || _state == PLAYER_ARROW_RIGHT)
		{
			_speed = 0;
			if (!_playerAni->isPlay())
			{
				if (!_isChangeAni)
				{
					_state = PLAYER_MOVE_RIGHT;
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "moveRight");
					_playerAni->start();
					_isChangeAni = true;
				}
			}
		}
		if (!_isGround)
		{
			_state = PLAYER_FALL_RIGHT;
			_isLadder = false;
		}
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
		if ((_state == PLAYER_ATTACK_RIGHT || _state == PLAYER_ARROW_RIGHT) && _playerAni->isPlay())
		{
			return;
		}
		_speed = 0.f;								//스피드값을 다시 줌(벽에 부딪힌 경우 speed 값을 0으로 바꾸었기 때문에 되돌려 줘야함)
		_state = PLAYER_IDLE_RIGHT;					//상태값은 idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
		if (!_isGround)
		{
			_state = PLAYER_FALL_RIGHT;
			_isLadder = false;
		}
	}
	
	//공격키 함수
	attackKey();

	if (_state == PLAYER_FALL_LEFT  || _state == PLAYER_FALL_RIGHT)
	{
		_y += _gravity * TIMEMANAGER->getElpasedTime();
		_curFallingY = _y;				//현재 떨어지고있을 때 높이 저장
		if (_curFallingY - _fallStartY >= _damageHeight)
		{
			//떨어지는 부분 나눠서 애니메이션 나오게 하기
			if (_state == PLAYER_FALL_RIGHT)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "highFallRight");
			}
			if (_state == PLAYER_FALL_LEFT)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "highFallLeft");
			}
		}
		pixelFireCollision();
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
	//_x = 1500;
	_x = WINSIZEX / 2 + 100;
	_y = 1370;
	_speed = 0.f;
	
	_acceleration = 3.5f;		//가속도
	_minSpeed = 1.f;			//최저속도
	_maxSpeed = 4.5f;			//최고속도

	_damageHeight = 315.f;
	_gravity = GRAVITY;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//pixel 충돌 탐지할 변수
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	_isGround = false;			//바닥에 붙어있숑?
	_isLadder = false;			//사다리 탔어?
	_isLadderTop = false;		//사다리의 맨위야?
	_isChangeAni = false;		//애니메이션 바꿔야댐??
	_isPushWall = false;		//벽 밀고 있어?
	_deathMotion = false;		//죽는 모션이 나와야댐?
	_isRight = true;


	_ladderIndex = 0;
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


void player_Baleog::pixelBottomCollision()
{
	//바닥충돌처리(픽셀충돌)
	for (int i = _proveBottom - 10; i < _proveBottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			if (_isLadder)
			{
				break;
			}
			_isGround = true;
			_y = i - 35;

			if (_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT)
			{
				if (_isRight)
				{
					_state = PLAYER_IDLE_RIGHT;
				}
				else
				{
					_state = PLAYER_IDLE_LEFT;
				}
			}

			break;
		}
		else if (r != 255 && g != 0 && b != 255)				//캐릭터가 바닥 부분에 없으면
		{
			_isGround = false;
		}
	}

	//떨어질때
	if (_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT)
	{
		
		if (_curFallingY - _fallStartY >= _damageHeight)		//떨어져서 데미지를 입을 높이면
		{
			_lifeCount -= 1;			//데미지 입음
			if (_lifeCount == 0)
			{
				_isAlive = false;		//목숨이 없어짐
				//애니 : 
			}

			//애니 :
			if (_state == PLAYER_FALL_LEFT)
			{
				if (!_isChangeAni)
				{
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "highFallEndLeft");
					_playerAni->start();
					//_isChangeAni = true;
				}
			}
			else if (_state == PLAYER_FALL_RIGHT)
			{
				if (!_isChangeAni)
				{
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "highFallEndRight");
					_playerAni->start();
					//_isChangeAni = true;
				}
			}
		}
		//else if (_curFallingY - _fallStartY < _damageHeight)	//떨어져도 데미지 없는 높이면
		//{
		//	if (_state == PLAYER_FALL_LEFT)
		//	{
		//		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "highFallEndLeft");
		//	}
		//	else if (_state == PLAYER_FALL_RIGHT)
		//	{

		//	}
		//}
	}
}

void player_Baleog::pixelFireCollision()
{
	for (int i = _playerRect.bottom - 10; i < _playerRect.bottom + 10; ++i)
	{
		//바닥에 불 충돌시 죽었다 표시까지 했고 멈추게 할것
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if(r == 255 && g==0 && b == 0)
		{
			//불에 떨어지는 방향에 따라 죽는 모션의 방향이 달라서 조건문 달았음
			if (_state == PLAYER_FALL_LEFT)
			{
				_state = PLAYER_FIRE_DEATH_LEFT;
			}
			if (_state == PLAYER_FALL_RIGHT)
			{
				_state = PLAYER_FIRE_DEATH_RIGHT;
			}
			_isAlive = false;
			_deathMotion = true;
			_speed = 0;
			_y = i - 35;
			break;
			
		}
	}
}

/*
void player_Baleog::rectBrokenWallCollision()
{
	//부서지는 벽은 rect인데 그 벽이랑 부딪힌 경우
	if (_state == PLAYER_MOVE_LEFT)
	{
		
	}
	if (_state == PLAYER_MOVE_RIGHT)
	{
		
	}
}
*/
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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleRight", _imageKey, specialIdleRight, 9, 6, false);
	//
	int specialIdleLeft[]{ 18, 19, 20, 21, 22, 23, 24, 25, 26 };			//enume : PLAYER_PLAYER_IDLE_SPECIAL_LEFT 3
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleLeft", _imageKey, specialIdleLeft, 9, 6, false);

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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndRight", _imageKey, highFallEndRight, 5, 6, false);

	int highFallEndLeft[] = { 75, 76, 77, 78, 79 };					//높은 곳에서 떨어지면서 rect의 bottom이 바닥에 닿은 경우에 이 애니메이션 추가(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndLeft", _imageKey, highFallEndLeft, 5, 6, false);

	int pushWallRight[] = { 45, 46, 47, 48 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "pushWallRight", _imageKey, pushWallRight, 4, 7, true);

	int pushWallLeft[] = { 49, 50, 51, 52 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "pushWallLeft", _imageKey, pushWallLeft, 4, 7, true);

	int ladderUp[] = { 54, 55, 56, 57 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderUp", _imageKey, ladderUp, 4, 7, true);

	int ladderDown[] = { 57, 56, 55, 54 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderDown", _imageKey, ladderDown, 4, 7, true);

	int ladderEnd[] = { 58, 59 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderEnd", _imageKey, ladderEnd, 2, 7, false);				//아직 끝 부분 조건을 안걸어서 잘 나오는지 확인 못해영 (사다리 다 처리하고 나면 확인할게영)

	int hitRight[] = { 123 };												//몬스터에게 맞으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitRight", _imageKey, hitRight, 1, 3, false);

	int hitLeft[] = { 132 };												//몬스터에게 맞으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitLeft", _imageKey, hitLeft, 1, 3, false);

	int hitDeathRight[] = { 117, 118, 119, 120, 121, 122 };					//몬스터에게 맞고 죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathRight", _imageKey, hitDeathRight, 6, 3, false);

	int hitDeathLeft[] = { 126, 127, 128, 129, 130, 131 };					//몬스터에게 맞고 죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathLeft", _imageKey, hitDeathLeft, 6, 3, false);

	int fallDeathRight[] = { 135, 136, 137, 138, 139 };						//떨어지다가 죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathRight", _imageKey, fallDeathRight, 5, 3, false);

	int fallDeathLeft[] = { 140, 141, 142, 143, 144 };						//떨어지다가 죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathLeft", _imageKey, fallDeathLeft, 5, 3, false);

	int fireDeathRight[] = { 145, 146, 147, 148, 149, 150, 151, 152 };		//불타죽으면(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathRight", _imageKey, fireDeathRight, 8, 6, false);

	int fireDeathLeft[] = { 153, 154, 155, 156, 157, 158, 159, 160 };		//불타죽으면(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathLeft", _imageKey, fireDeathLeft, 8, 6, false);

	int lookFrontRight[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontRight", _imageKey, lookFrontRight, 1, 6, true);

	int lookFrontLeft[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontLeft", _imageKey, lookFrontLeft, 1, 6, true);

	int attackLengthRight[] = { 81, 82, 83, 84 };							//세로 공격(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthRight", _imageKey, attackLengthRight, 4, 6, false);

	int attackLengthLeft[] = { 85, 86, 87, 88 };							//세로 공격(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthLeft", _imageKey, attackLengthLeft, 4, 6, false);

	int attackWidthRight[] = { 90, 91, 92, 93 };							//가로 공격(오른쪽)	
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthRight", _imageKey, attackWidthRight, 4, 6, false);

	int attackWidthLeft[] = { 94, 95, 96, 97 };								//가로 공격(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthLeft", _imageKey, attackWidthLeft, 4, 6, false);

	int arrowRight[] = { 99, 100, 101, 102, 103, 104, 105, 106 };			//활 공격(오른쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowRight", _imageKey, arrowRight, 8, 10, false);

	int arrowLeft[] = { 108, 109, 110, 111, 112, 113, 114, 115 };			//활 공격(왼쪽)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowLeft", _imageKey, arrowLeft, 8, 10, false);

	//_state = PLAYER_IDLE_RIGHT;
	_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
	_playerAni->start();
}


void player_Baleog::collisionLadder(vector<RECT*> ladder)
{
	RECT tempColLadder;
	int ladderVSize = ladder.size();
	//============== 위 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		for (int i = 0; i < ladderVSize; ++i)
		{
			if (IntersectRect(&tempColLadder, ladder[i], &_playerRect))		//플레이어와 사다리의 렉트가 충돌했을 때 
			{
				_isLadder = true;			//사다리를 타고 있어영
				_ladderIndex = i;

				_speed = 2.0f;				//_y 에 스피드가 생겼어영

				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");		
				_playerAni->start();		//올라가는 모션을 재생해보아요
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))	//키를 계속 누르고있고
	{
		if (_isLadder)						//사다리를 타고있다면
		{
			if (_playerRect.bottom <= (*ladder[_ladderIndex]).top)		//플레이어의 발이 사다리의 윗부분에 있으면
			{
				_speed = 0;									//더이상 y축 이동은 하지 마세영
				if (!_isLadderTop)							//아직은 bool _isLadderTop이 false라서 이 조건에 들어와영
				{	
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderEnd");		//사다리 윗부분에서의 모션을 
					_playerAni->start();					//재생하세영
					_isLadderTop = true;
					_isLadder = false;						//그때 더이상 사다리 위에 있는게 아니니까  _isLadder = false 로 바꿔주세여
				}
				pixelBottomCollision();

			}
			_y -= _speed;					//y축 이동을 계속 하세영
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_isLadder && !_isLadderTop)
		{
			_playerAni->pause();
		}
		if (_isLadderTop)
		{
			_isLadder = false;
			_isLadderTop = false;
		}
	}

	//============== 아 래 로 ===============
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		for (int i = 0; i < ladderVSize; ++i)
		{
			if (IntersectRect(&tempColLadder, ladder[i], &_playerRect))		//플레이어와 사다리의 렉트가 충돌했을 때 
			{
				_ladderIndex = i;
				if (!_isLadderTop && !_isLadder)
				{
					_speed = 2.0f;				//_y 에 스피드가 생겼어영
					_isLadder = true;			//사다리를 타고 있어영

					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderDown");
					_playerAni->start();		//내려가는 모션을 재생해보아요
				}
				if (_isLadder)
				{
					_playerAni->resume();
				}
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (_isLadder)						//사다리를 타고있다면
		{
			_speed = 2.0f;
			
			if (_playerRect.bottom >= (*ladder[_ladderIndex]).bottom)		//플레이어의 발이 사다리의 아래부분에 있으면
			{
				_speed = 0;									//더이상 y축 이동은 하지 마세영
				if (_isRight)
				{
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
					_playerAni->start();
				}
				else
				{
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleLeft");
					_playerAni->start();
				}
				_isLadder = false;
			}
		
			_y += _speed;					//y축 이동을 계속 하세영
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_isLadder)
		{
			_playerAni->pause();
		}

	}
}

void player_Baleog::attackKey()
{
	//========================== <공 격 키> ===========================
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//============ 오른쪽으로 공격하면 ==============
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_ATTACK_RIGHT;
			if (RND->getInt(2) == 0)				//오른쪽 세로 공격
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackLengthRight");
				_playerAni->start();
				_isChangeAni = false;
			}
			else if (RND->getInt(2) == 1)
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackWidthRight");
				_playerAni->start();
				_isChangeAni = false;
			}
		}
		//============= 왼쪽으로 공격하면 ===============
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_state = PLAYER_ATTACK_LEFT;
			if (RND->getInt(2) == 0)				//왼쪽 세로 공격
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackLengthLeft");
				_playerAni->start(); 
				_isChangeAni = false;
			}
			else if (RND->getInt(2) == 1)			//왼쪽 가로 공격
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackWidthLeft");
				_playerAni->start();
				_isChangeAni = false;
			}
		}
	}
	
	//====================<활 공 격>=======================
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_isAttackRight = true;
			_isFire = true;
			_state = PLAYER_ARROW_RIGHT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "arrowRight");
			_playerAni->start();
			_isChangeAni = false;
			//불렛의 시작점이 rect.right
		}
		if(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_isAttackRight = false;
			_isFire = true;
			_state = PLAYER_ARROW_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "arrowLeft");
			_playerAni->start();
			_isChangeAni = false;
			//불렛의 시작점이 rect.left
		}
	}
	
	if (!_playerAni->isPlay() && !_isLadder)
	{
		_isChangeAni = false;
		if (_isRight)
		{
			_state = PLAYER_IDLE_RIGHT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
			_playerAni->start();
		}
		else
		{
			_state = PLAYER_IDLE_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleLeft");
			_playerAni->start();
		}
	}
}

bool player_Baleog::getIsAttackRight()
{
	 return _isAttackRight;
}

bool player_Baleog::getIsFire()
{
	return _isFire;
}

void player_Baleog::setIsFire(bool isFire)
{
	_isFire = isFire;
}
