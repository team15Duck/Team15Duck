#include "stdafx.h"
#include "player_Eric.h"
#include "objectManager.h"
#include "mainUI.h"


player_Eric::player_Eric()
{
}


player_Eric::~player_Eric()
{
}


HRESULT player_Eric::init()
{
	//캐릭터 설정 관련 초기화
	ericInit();
	//캐릭터 애니메이션 관련 초기화
	EricAniinit();
	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{
	/*
	KEYANIMANAGER->update("player_eric");

	if (_state == PLAYER_FIRE_DEATH_LEFT || _state == PLAYER_FIRE_DEATH_RIGHT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isAlive = false;
		}
	}
	else
	{
		jump();
		pixelBottomCollision();
		pixelDieCollision();

		_proveRight = _playerRect.right;
		_proveLeft = _playerRect.left;
		_proveTop = _playerRect.top;
		_proveBottom = _playerRect.bottom;

		//애니메이션
		EricAni();

	}
	*/

	KEYANIMANAGER->update("player_eric");

	//이동관련 처리
	if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_HEAD_BUTT_RIGHT)
	{
		if (_isRightMove)
		{
			//스피드가 맥스 스피드보다 작을때 속도 상승처리
			if (_speed < MAX_SPEED)
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
			}
			//속도 예외 처리
			else
			{
				_speed = MAX_SPEED;
			}
			//벽 픽셀충돌 처리
			if (!_isRCollision)
			{
				for (int i = _proveRight; i > _proveRight - 32; --i)
				{
					COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//========================================================== 실질적인 충돌처리 부분
					if ((r == 0 && g == 255 && b == 255))
					{
						_isRCollision = true;						//충돌했음을 확인

						_x = i - (_size.x / 2);						//플레이어 x 값 보정

						if (_isRCollision && _isRightMove && !_isRSkill)
						{
							_state = PLAYER_PUSH_WALL_RIGHT;
						}
						if (_state == PLAYER_HEAD_BUTT_RIGHT)
						{
							_state = PLAYER_STUN_RIGHT;
							_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "stun_right");
							KEYANIMANAGER->start("player_eric", "stun_right");
						}
					}
					else
					{
						_isRCollision = false;
					}
				}
			}
			//실질적인 이동
			_x += _speed * TIMEMANAGER->getElpasedTime();
		}
		//================================================================= 맵 이동 예외처리 
		if (_x + (_size.x / 2) > _pixelData->GetWidth())
		{
			_x = _pixelData->GetWidth() - (_size.x / 2);
		}
	}
	else if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_HEAD_BUTT_LEFT)
	{
		if (_isLeftMove)
		{
			//스피드가 맥스 스피드보다 작을때 속도 상승처리
			if (_speed < MAX_SPEED)
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
			}
			//속도 예외 처리
			else
			{
				_speed = MAX_SPEED;
			}
			//벽 픽셀충돌 처리
			if (!_isLCollision)
			{
				for (int i = _proveLeft; i < _proveLeft + 32; ++i)
				{
					COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//========================================================== 실질적인 충돌처리 부분
					if ((r == 0 && g == 255 && b == 255))
					{
						_isLCollision = true;						//충돌했음을 확인
						_x = i + (_size.x / 2);						//플레이어 x좌표 보정

						if (_isLCollision && _isLeftMove && !_isLSkill)
						{
							_state = PLAYER_PUSH_WALL_LEFT;
						}
						if (_state == PLAYER_HEAD_BUTT_LEFT)
						{
							_state = PLAYER_STUN_LEFT;
							_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "stun_left");
							KEYANIMANAGER->start("player_eric", "stun_left");
						}
					}
					else
					{
						_isLCollision = false;						//그게아니라면 충돌안했다
					}
				}
			}
			//실질적인 이동
			_x -= _speed * TIMEMANAGER->getElpasedTime();
			//================================================================= 맵 이동 예외처리 
			if (_x - (_size.x / 2) < 0)
			{
				_x = 0 + (_size.x / 2);
			}
		}
	}
	//사다리관련 처리
	if (_state == PLAYER_LADDER_UP)
	{
		upMove(_ladder);
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");	_gravity = GRAVITY;_jumpPower = 0;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");	_gravity = GRAVITY;_jumpPower = 0;
		}
	}
	else if (_state == PLAYER_LADDER_DOWN)
	{
		downMove(_ladder);
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
			_jumpPower = 0;	_gravity = GRAVITY;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");
			_jumpPower = 0;	_gravity = GRAVITY;
		}
	}
	else if (_state == PLYAER_LADDER_STAY)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
			_jumpPower = 0;
			_gravity = GRAVITY;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");
			_jumpPower = 0;
			_gravity = GRAVITY;
		}
	}
	if (_state == PLAYER_LADDER_END)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isladderup = false;
			_isladderUse = false;
			_state = PLAYER_IDLE_RIGHT;
			_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idle_right");
			KEYANIMANAGER->start("player_eric", "idle_right");
		}
	}
	//점프관련 처리
	if (_state == PLAYER_JUMP_RIGHT)
	{
		_y -= _jumpPower * TIMEMANAGER->getElpasedTime();
		_jumpPower -= _gravity * TIMEMANAGER->getElpasedTime();

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = PLAYER_JUMP_LEFT;
			EricAniStart("jump_left");
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_x += MAX_SPEED * TIMEMANAGER->getElpasedTime();
			jumpRightPixelCollision();
		}

		if (_jumpPower > 0)
		{
			pixelTopWallCollision();
		}
		else
		{
			_isJump = false;
			_isFall = true;
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");
		}
	}
	else if (_state == PLAYER_JUMP_LEFT)
	{
		_y -= _jumpPower * TIMEMANAGER->getElpasedTime();
		_jumpPower -= _gravity * TIMEMANAGER->getElpasedTime();

		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= MAX_SPEED * TIMEMANAGER->getElpasedTime();
			jumpLeftPixelCollision();
		}

		if (_jumpPower > 0)
		{
			pixelTopWallCollision();
		}
		else
		{
			_isJump = false;
			_isFall = true;
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
		}
	}
	if (_state == PLAYER_FALL_RIGHT)
	{
		_y -= _jumpPower * TIMEMANAGER->getElpasedTime();
		_jumpPower -= _gravity * TIMEMANAGER->getElpasedTime();
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_x += MAX_SPEED * TIMEMANAGER->getElpasedTime();
			jumpRightPixelCollision();
		}
		if (_jumpPower < 0)
		{
			pixelBottomCollision();
		}
	}
	else if (_state == PLAYER_FALL_LEFT)
	{
		_y -= _jumpPower * TIMEMANAGER->getElpasedTime();
		_jumpPower -= _gravity * TIMEMANAGER->getElpasedTime();
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");
		}
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_x -= MAX_SPEED * TIMEMANAGER->getElpasedTime();
			jumpLeftPixelCollision();
		}
		if (_jumpPower < 0)
		{
			pixelBottomCollision();
		}
	}
	//스킬관련 처리
	if (_state == PLAYER_HEAD_BUTT_RIGHT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isRSkill = false;
			_isSign = true;
			_state = PLAYER_MOVE_RIGHT;
			EricAniStart("move_right");

		}
	}
	else if (_state == PLAYER_HEAD_BUTT_LEFT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isLSkill = false;
			_isSign = true;
			_state = PLAYER_MOVE_LEFT;
			EricAniStart("move_left");
		}
	}
	//벽밀기 처리
	if (_state == PLAYER_PUSH_WALL_RIGHT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "push_wall_right");
		if (!_EricMotion->isPlay())
		{
			KEYANIMANAGER->start("player_eric", "push_wall_right");
		}
	}
	else if (_state == PLAYER_PUSH_WALL_LEFT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "push_wall_left");
		if (!_EricMotion->isPlay())
		{
			KEYANIMANAGER->start("player_eric", "push_wall_left");
		}
	}
	//스턴 처리
	if (_state == PLAYER_STUN_RIGHT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_state = PLAYER_IDLE_RIGHT;
			EricAniStart("idle_right");
		}
	}
	else if (_state == PLAYER_STUN_LEFT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_state = PLAYER_IDLE_LEFT;
			EricAniStart("idle_left");
		}
	}
	//한숨처리
	if (_state == PLAYER_SIGN_RIGHT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isSign = false;
			_state = PLAYER_IDLE_RIGHT;
			EricAniStart("idle_right");
		}
	}
	else if (_state == PLAYER_SIGN_LEFT)
	{
		if (_EricMotion->isPlay() == false)
		{
			_isSign = false;
			_state = PLAYER_IDLE_LEFT;
			EricAniStart("idle_left");
		}
	}

	//충돌 처리
	collisioninit();
	pixelBottomCollision();
	//플레이어 렉트 갱신
	_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);
}

void player_Eric::render()
{
	char str[256];
	SetTextColor(CAMERA->getMemDC(), RGB(255, 255, 255));
	sprintf_s(str, "speed : %.1f", _speed);
	TextOut(CAMERA->getMemDC(), 400, 0, str, strlen(str));
	sprintf_s(str, "state : %d", _state);
	TextOut(CAMERA->getMemDC(), 400, 50, str, strlen(str));

	Rectangle(CAMERA->getMemDC(), _playerRect, false);
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _EricMotion);
}

void player_Eric::keyPressMove()
{

	if (_state == PLAYER_JUMP_LEFT || _state == PLAYER_JUMP_RIGHT ||
		_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT) return;

	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		RECT temp;
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				_isladderup = true;
				_isladderUse = true;
				break;
			}
		}
		if (_isladderup)
		{
			_state = PLAYER_LADDER_UP;
			EricAniStart("ladder_up");
		}
		if (_isladderup && _isladderUse)
		{
			_state = PLAYER_LADDER_UP;
			_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "ladder_up");
			KEYANIMANAGER->resume("player_eric", "ladder_up");
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_state == PLAYER_LADDER_UP)
		{
			_isladderup = false;
			_isladderUse = true;
			_state = PLYAER_LADDER_STAY;
			KEYANIMANAGER->pause("player_eric", "ladder_up");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		RECT temp;
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				_isladderdown = true;
				_isladderUse = true;
				break;
			}
		}
		if (_isladderdown)
		{
			_state = PLAYER_LADDER_DOWN;
			EricAniStart("ladder_down");
		}
		if (_isladderdown && _isladderUse)
		{
			_state = PLAYER_LADDER_DOWN;
			_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "ladder_down");
			KEYANIMANAGER->resume("player_eric", "ladder_down");
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_state == PLAYER_LADDER_DOWN)
		{
			_isladderdown = false;
			_isladderUse = true;
			_state = PLYAER_LADDER_STAY;
			KEYANIMANAGER->pause("player_eric", "ladder_down");
		}
	}

	if (_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN || _state == PLYAER_LADDER_STAY) return;
	//오른쪽 이동 
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_isRightMove = true;
		_isRCollision = false;
		if (_isRightMove)
		{
			_speed = MIN_SPEED;
			_state = PLAYER_MOVE_RIGHT;
			EricAniStart("move_right");
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_PUSH_WALL_RIGHT)
		{
			_speed = MIN_SPEED;
			_isRightMove = false;
			_isRCollision = false;
			_state = PLAYER_IDLE_RIGHT;
			EricAniStart("idle_right");
		}
		if (_isSign)
		{
			_state = PLAYER_SIGN_RIGHT;
			EricAniStart("sign_right");
		}
	}
	//왼쪽 이동
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_isLeftMove = true;
		_isLCollision = false;
		if (_isLeftMove)
		{
			_speed = MIN_SPEED;
			_state = PLAYER_MOVE_LEFT;
			EricAniStart("move_left");
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_PUSH_WALL_LEFT)
		{
			_speed = MIN_SPEED;
			_isLeftMove = false;
			_state = PLAYER_IDLE_LEFT;
			EricAniStart("idle_left");
		}
		if (_isSign)
		{
			_state = PLAYER_SIGN_LEFT;
			EricAniStart("sign_left");
		}
	}

	//위로 이동
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		RECT temp;
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				_isladderup = true;
				_isladderUse = true;
				break;
			}
		}
		if (_isladderup)
		{
			_state = PLAYER_LADDER_UP;
			EricAniStart("ladder_up");
		}
		if (_isladderup && _isladderUse)
		{
			_state = PLAYER_LADDER_UP;
			_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "ladder_up");
			KEYANIMANAGER->resume("player_eric", "ladder_up");
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		if (_state == PLAYER_LADDER_UP)
		{
			_isladderup = false;
			_isladderUse = true;
			_state = PLYAER_LADDER_STAY;
			KEYANIMANAGER->pause("player_eric", "ladder_up");
		}
	}

	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		RECT temp;
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				_isladderdown = true;
				_isladderUse = true;
				break;
			}
		}
		if (_isladderdown)
		{
			_state = PLAYER_LADDER_DOWN;
			EricAniStart("ladder_down");
		}
		if (_isladderdown && _isladderUse)
		{
			_state = PLAYER_LADDER_DOWN;
			_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "ladder_down");
			KEYANIMANAGER->resume("player_eric", "ladder_down");
		}
	}
	else if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		if (_state == PLAYER_LADDER_DOWN)
		{
			_isladderdown = false;
			_isladderUse = true;
			_state = PLYAER_LADDER_STAY;
			KEYANIMANAGER->pause("player_eric", "ladder_down");
		}
	}
}

void player_Eric::keyPressSpace()
{

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_state == PLAYER_IDLE_RIGHT || _state == PLAYER_MOVE_RIGHT)
		{
			_state = PLAYER_JUMP_RIGHT;
			_isJump = true;												//점프 상태임을 확인
			_jumpPower = START_JUMPP;									//점프 파워는 스타트 파워 세팅
			_gravity = GRAVITY;											//낙하를 위해 중력 세팅 
			EricAniStart("jump_right");
		}
		else if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT)
		{
			_state = PLAYER_JUMP_LEFT;
			_isJump = true;												//점프 상태임을 확인
			_jumpPower = START_JUMPP;									//점프 파워는 스타트 파워 세팅
			_gravity = GRAVITY;											//낙하를 위해 중력 세팅 
			EricAniStart("jump_left");
		}
	}
}

void player_Eric::keyPressD()
{
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_isRightMove)
		{
			if (_speed == MAX_SPEED)
			{
				_isRSkill = true;
				_state = PLAYER_HEAD_BUTT_RIGHT;
				//애니메이션 처리
				EricAniStart("head_butt_right");
			}
		}
		if (_isLeftMove)
		{
			if (_speed == MAX_SPEED)
			{
				_isLSkill = true;
				_state = PLAYER_HEAD_BUTT_LEFT;
				//애니메이션 처리
				EricAniStart("head_butt_left");
			}
		}
	}
}

void player_Eric::keyPressE()
{

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		int index = _mainUI->getInvenPos(PLAYER_NAME_ERIC);

		if (_invenItem[index] != nullptr)
		{
			switch (_invenItem[index]->getItemType())
			{
			case ITEM_TYPE_FRUIT_SMALL: case ITEM_TYPE_FRUIT_BIG:
			{
				if (_lifeCount == 3)
				{
					return;
				}
				else
				{
					_lifeCount += 1;
					SAFE_RELEASE(_invenItem[index]);
					SAFE_DELETE(_invenItem[index]);
					_mainUI->setEricItemInfo(_invenItem);
				}
				break;
			}
			case ITEM_TYPE_MEAT:
			{
				if (_lifeCount == 3)
				{
					return;
				}
				else
				{
					if (_lifeCount == 2)
					{
						_lifeCount += 1;
					}
					else
					{
						_lifeCount += _invenItem[index]->getItemValue();
					}
					SAFE_RELEASE(_invenItem[index]);
					SAFE_DELETE(_invenItem[index]);
					_mainUI->setEricItemInfo(_invenItem);
				}
				break;
			}
			case ITEM_TYPE_SHIELD:
			{
				break;
			}
			case ITEM_TYPE_KEY_RED:
			case ITEM_TYPE_KEY_YELLOW:
			case ITEM_TYPE_KEY_BLUE:
			{
				RECT temp;
				for (int i = 0; i < _objectRc.size(); ++i)
				{
					if (IntersectRect(&temp, _objectRc[i]->getObjectRect(), &_playerRect))
					{
						if (_objectRc[i]->getObjectValue() == _invenItem[index]->getItemValue())
						{
							_objm->interactionObject(_objectRc[i]);
							SAFE_RELEASE(_invenItem[index]);
							SAFE_DELETE(_invenItem[index]);
							_mainUI->setEricItemInfo(_invenItem);
						}
					}
				}
				break;
			}

			}
		}
	}
}

void player_Eric::keyPressS()
{
}


void player_Eric::rectBrokenWallCollision()
{
}

void player_Eric::pixelTopWallCollision()
{
	for (int i = _proveTop; i < _proveTop + 32; ++i)
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
	/*
	//================================================================= 예외처리
	if (_state == PLAYER_JUMP_RIGHT || _state == PLAYER_JUMP_LEFT ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
	{
		return;
	}
	//================================================================= 픽셀충돌
	_isBCollision = false;
	for (int i = _proveBottom - 15; i < _proveBottom + 10; ++i)
	{
		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//========================================================= 실질적인 충돌부분
			if (r == 255 && g == 0 && b == 255)
			{
				_y = i - (_size.y / 2);					//플레이어의 y값을 보정해주고
				_isBCollision = true;					//바닥과 충돌하고있음을 확인함
				_isJump = false;						//점프가 가능하도록 점프변수를 false로 변겅
				_isFall = false;						//바닥에 닿으면 떨어지고 있는 중이 아니다.
				_isUpMove = false;
				_isDownMove = false;
				_gravity = 0;

				if (_state == PLAYER_FALL_RIGHT)
				{
					_state = PLAYER_IDLE_RIGHT;
				}
				else if (_state == PLAYER_FALL_LEFT)
				{
					_state = PLAYER_IDLE_LEFT;
				}
				else if (_state == PLAYER_LADDER_DOWN)
				{
					_state = PLAYER_IDLE_RIGHT;
				}

				break;									//더이상 x축의 검사를 안한다.
			}
		}
		//충돌중에 있다면
		if (_isBCollision)
		{
			break;										//더이상 y축의 검사를 안하고 부드럽게 이동함 ** 여기서 브레이크안걸면 덜덜떰
		}
	}
	//================================================================= 바닥과 픽셀충돌중이 아닐때의 처리
	if (!_isBCollision)
	{
		_gravity = GRAVITY;											//중력값 세팅
		_y += _gravity * TIMEMANAGER->getElpasedTime();				//중력값 만큼 떨어진다.
	}
	*/
	//================================================================= 예외처리
	if (_state == PLAYER_JUMP_RIGHT || _state == PLAYER_JUMP_LEFT ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
	{
		return;
	}
	//================================================================= 픽셀충돌
	_isBCollision = false;
	for (int i = _proveBottom - 5; i < _proveBottom + 10; ++i)
	{
		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//========================================================= 실질적인 충돌부분
			if (r == 255 && g == 0 && b == 255)
			{
				_y = i - (_size.y / 2);					//플레이어의 y값을 보정해주고
				_isBCollision = true;					//바닥과 충돌하고있음을 확인함
				_isJump = false;
				_isladderup = false;
				_isladderUse = false;
				_isladderdown = false;
				if (_state == PLAYER_FALL_RIGHT)
				{
					_isFall = false;
					_state = PLAYER_IDLE_RIGHT;
					EricAniStart("idle_right");
				}
				else if (_state == PLAYER_FALL_LEFT)
				{
					_isFall = false;
					_state = PLAYER_IDLE_LEFT;
					EricAniStart("idle_left");
				}
				break;									//더이상 x축의 검사를 안한다.
			}
		}
		//충돌중에 있다면
		if (_isBCollision)
		{
			break;										//더이상 y축의 검사를 안하고 부드럽게 이동함 ** 여기서 브레이크안걸면 덜덜떰
		}
	}

}

void player_Eric::jumpRightPixelCollision()
{
	for (int i = _proveRight; i > _proveRight - 32; --i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//========================================================== 실질적인 충돌처리 부분
		if ((r == 0 && g == 255 && b == 255))
		{

			_x = i - (_size.x / 2);						//플레이어 x 값 보정
		}
	}
}

void player_Eric::jumpLeftPixelCollision()
{
	for (int i = _proveLeft; i < _proveLeft + 32; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		//========================================================== 실질적인 충돌처리 부분
		if ((r == 0 && g == 255 && b == 255))
		{
			_x = i + (_size.x / 2);						//플레이어 x 값 보정
		}
	}
}

void player_Eric::pixelDieCollision()
{
	_isFCollision = false;
	for (int i = _proveBottom - 15; i < _proveBottom + 10; ++i)
	{
		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//========================================================= 실질적인 충돌부분
			if (r == 255 && g == 0 && b == 0)
			{
				_y = i - (_size.y / 2);					//플레이어의 y값을 보정해주고
				_isFCollision = true;					//불바닥이랑 충돌하고있음을 확인하기 
				_lifeCount = 0;

				if (_state == PLAYER_FALL_RIGHT || _state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
				{
					_state = PLAYER_FIRE_DEATH_RIGHT;
					EricAniStart("die_fire_right");
				}
				if (_state == PLAYER_FALL_LEFT || _state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
				{
					_state = PLAYER_FIRE_DEATH_LEFT;
					EricAniStart("die_fire_left");

				}

				break;									//더이상 x축의 검사를 안한다.
			}
		}
	}

}

void player_Eric::ericInit()
{
	playerBase::init();

	//플레이어 기본 설정 초기화
	_size = { 64, 64 };		//플레이어 사이즈
	_x = 150;				//플레이어 x좌표
	_y = 1375;				//플레이어 y좌표

	_speed = MIN_SPEED;		//플레이어 기본 스피드
	_jumpPower = 0;				//플레이어 점프파워
	_gravity = 0;				//플레이어 중력
	_isAlive = true;				//플레이어 살아있는지 체크용 불값 
	_lifeCount = 3;				//플레이어 생명은 최대 3
	_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);

	//충돌처리용 초기화 
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;
	_proveTop = _playerRect.top;

	//픽셀충돌체크 불값 초기화
	_isRCollision = false;		//오른쪽 벽
	_isLCollision = false;		//왼쪽 벽
	_isBCollision = false;		//바닥
	_isFCollision = false;		//죽는바닥

	//이동관련 불값 초기화

	_isJump = false;
	_isFall = false;
	_isRightMove = false;
	_isLeftMove = false;
	_isUpMove = false;
	_isDownMove = false;

	//사다리타기용 불값

	_isladderup = false;
	_isladderdown = false;
	_isUsladder = false;
	_isUeladder = false;
	_isDsladder = false;
	_isDeladder = false;
	_isladderUse = false;

	//스킬사용 불값

	_isRSkill = false;
	_isLSkill = false;
	_isSign = false;

	_state = PLAYER_IDLE_RIGHT;
}

void player_Eric::collisioninit()
{
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;
	_proveTop = _playerRect.top;
	_proveBottom = _playerRect.bottom;
}

void player_Eric::upMove(object * ladder)
{
	/*
	RECT temp;
	if (_isRightMove || _isLeftMove)
	{
		return;
	}
	//=================================================== 상태 및 좌표 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		//만약에 캐릭터의 상태가 아래와 같을때
		if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_IDLE_RIGHT ||
			_state == PLAYER_MOVE_LEFT || _state == PLAYER_MOVE_RIGHT ||
			_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT ||
			_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
		{
			for (int i = 0; i < _ladderRc.size(); ++i)
			{
				//만약에 사다리렉트와 캐릭터 렉트가 부딪혔을때
				if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
				{
					// 플레이어가 사다리로 올라가고 있지 않다면
					if (!_isladderup)
					{
						//위로 이동하므로 위로 이동하는 불값 true 변경
						_isUpMove = true;
						//몇번째의 사다리인지 체크하기위해 인덱스 설정
						_ladderIndex = i;
						//캐릭터의 x 좌표를 사다리의 x좌표로 맞추어준다.
						float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;
						_x = ladderX;
						//캐릭터의 상태를 사다리 타는중으로 변경하면서 사다리에 매달리는 애니메이션을 출력해주자
						_state = PLAYER_LADDER_UP;
						EricAniStart("ladder_up");
						//캐릭터는 사다리에 매달려 있고, 올라가고 있으므로 체크용 불값도 변경
						_isladderUse = true;
						_isladderup = true;
						//사다리에 매달리면 떨어지고있는중이 아니므로
						_isFall = false;
					}
				}
			}
		}
	}
	//=================================================== 실제 움직임 구현
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//만약에 사다리에 캐릭터가 매달려있고, 위로 올라가는 중이라면
		if (_isladderUse && _isladderup)
		{
			_y -= _speed;
			//만약에 사다리의 인덱스가 0보다 크거나 같고, 최대 개수보다는 작을때
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//만약에 사다리의 윗쪽 값보다 캐릭터의 하단값이 같거나 작다면
				if (_ladderRc[_ladderIndex]->top >= _playerRect.bottom)
				{
					//캐릭터의 상태는 사다리 끝이 되고, 사다리 끝 체크 불값을 true로 바꿔준다.
					_state = PLAYER_LADDER_END;
					_isUeladder = true;
					EricAniStart("ladder_end");
				}
			}
		}
	}
	//=================================================== 리셋
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		//키를 때면 올라가고있지 않으므로 변수를 false처리한다.
		_isUpMove = false;
		_isladderup = false;
		_state = PLAYER_LADDER_UP;
		KEYANIMANAGER->pause("player_eric", "ladder_up");
	}
	//=================================================== 예외처리
	if (_state == PLAYER_LADDER_END)
	{
		if (_EricMotion->isPlay() == false)
		{
			_state = PLAYER_IDLE_RIGHT;
			EricAniStart("idleright");
		}
		//캐릭터의 상태가 사다리끝에 도착했으니 사다리에 매달려 있는것도 아니고, 올라가지도 않고 있으니 체크변수를 false로 변경
		_isladderup = false;
		_isladderUse = false;
	}
	*/
	RECT temp;
	if (_state == PLAYER_LADDER_UP)
	{
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;

				_ladderIndex = i;
				_x = ladderX;
				_speed = MIN_SPEED;
				_y -= _speed;
				break;
			}

		}

		//========================================================== 예외처리
		if (_isladderUse && _isladderup)
		{
			//만약에 사다리의 인덱스가 0보다 크거나 같고, 최대 개수보다는 작을때
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//만약에 사다리의 윗쪽 값보다 캐릭터의 하단값이 같거나 작다면
				if (_ladderRc[_ladderIndex]->top >= _playerRect.bottom)
				{
					_state = PLAYER_LADDER_END;
					EricAniStart("ladder_end");
				}
			}
		}
	}
}


void player_Eric::downMove(object * ladder)
{
	RECT temp;
	if (_state == PLAYER_LADDER_DOWN)
	{
		for (int i = 0; i < _ladderRc.size(); ++i)
		{
			if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
			{
				float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;

				_ladderIndex = i;
				_x = ladderX;
				_speed = MIN_SPEED;
				_y += _speed;
				break;
			}

		}

		//========================================================== 예외처리
		if (_isladderUse && _isladderdown)
		{
			//만약에 사다리의 인덱스가 0보다 크거나 같고, 최대 개수보다는 작을때
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//만약에 사다리의 윗쪽 값보다 캐릭터의 하단값이 같거나 작다면
				if (_ladderRc[_ladderIndex]->bottom <= _playerRect.bottom)
				{
					_state = PLAYER_IDLE_RIGHT;
					EricAniStart("idle_right");
				}
			}
		}
	}
}


void player_Eric::jump()
{
	/*
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
	*/
}

void player_Eric::EricAniinit()
{
	_aniCount = 0;
	//이미지 추가
	_player = IMAGEMANAGER->addFrameImage("player_eric", "image/eric.bmp", 704, 1024, 11, 16, true, RGB(255, 0, 255));
	//애니메이션 타입추가
	KEYANIMANAGER->addAnimationType("player_eric");

	int idle_Right[] = { 0, 1 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "idle_right", "player_eric", idle_Right, 2, 2, true);
	int idle_Left[] = { 2, 3 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "idle_left", "player_eric", idle_Left, 2, 2, true);
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
	int push_wall_right[] = { 77, 78, 79, 80 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "push_wall_right", "player_eric", push_wall_right, 4, 10, true);
	int push_wall_left[] = { 81, 82, 83, 84 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "push_wall_left", "player_eric", push_wall_left, 4, 10, true);
	int die_fire_right[] = { 132, 133, 134, 135, 136, 137, 138, 139 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "die_fire_right", "player_eric", die_fire_right, 8, 10, false);
	int die_fire_left[] = { 143, 144, 145, 146, 147, 148, 149, 150 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "die_fire_left", "player_eric", die_fire_left, 8, 10, false);
	int ladder_up[] = { 66, 67, 68, 69 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "ladder_up", "player_eric", ladder_up, 4, 10, true);
	int ladder_down[] = { 69,68,67,66 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "ladder_down", "player_eric", ladder_down, 4, 10, true);
	int ladder_end[] = { 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "ladder_end", "player_eric", ladder_end, 2, 2, false);
	int head_butt_right[] = { 33,34,35,36,37,38,39,40 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "head_butt_right", "player_eric", head_butt_right, 8, 10, false);
	int head_butt_left[] = { 44,45,46,47,48,49,50,51 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "head_butt_left", "player_eric", head_butt_left, 8, 10, false);
	int stun_right[] = { 88, 89, 90, 91, 92 ,93, 94, 95, 96, 97, 98 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "stun_right", "player_eric", stun_right, 11, 10, false);
	int stun_left[] = { 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "stun_left", "player_eric", stun_left, 11, 10, false);
	int sign_right[] = { 4, 5, 6, 4, 5, 6, 4, 5, 6, 4 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "sign_right", "player_eric", sign_right, 10, 10, false);
	int sign_left[] = { 7, 8, 9, 7, 8, 9, 7, 8, 9, 7 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "sign_left", "player_eric", sign_left, 10, 10, false);

	//기본 애니메이션 설정
	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idle_right");
	KEYANIMANAGER->start("player_eric", "idle_right");
}

void player_Eric::EricAni()
{
	/*if (_state == PLAYER_IDLE_RIGHT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleright");

	}
	if (_state == PLAYER_IDLE_LEFT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleleft");
	}*/

}

void player_Eric::EricAniStart(string key)
{
	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", key);
	KEYANIMANAGER->start("player_eric", key);
}
