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
	playerBase::init();

	//플레이어 기본 설정 초기화
	_size = { 64, 64 };		//플레이어 사이즈
	_x = 450;				//플레이어 x좌표
	_y = 1320;				//플레이어 y좌표

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

	//애니메이션 초기화
	EricAniinit();

	return S_OK;
}


void player_Eric::release()
{

}


void player_Eric::update()
{
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

		//플레이어 렉트 갱신
		_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);
	}

}

void player_Eric::render()
{
	if (_isAlive)
	{
		//Rectangle(CAMERA->getMemDC(), _playerRect, false);
		_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _EricMotion);
	}
	//속도 테스트용 출력 
	char str[256];
	SetTextColor(CAMERA->getMemDC(), RGB(255, 255, 255));
	sprintf_s(str, "speed : %.1f", _speed);
	TextOut(CAMERA->getMemDC(), 0, 200, str, strlen(str));
	sprintf_s(str, "state : %d", _state);
	TextOut(CAMERA->getMemDC(), 0, 250, str, strlen(str));
	sprintf_s(str, "anicount : %d", _aniCount);
	TextOut(CAMERA->getMemDC(), 0, 225, str, strlen(str));
	sprintf_s(str, "anicount : %d", _isFall);
	TextOut(CAMERA->getMemDC(), 0, 260, str, strlen(str));
}

void player_Eric::keyPressMove()
{
	if (_isAlive)
	{
		rightMove();
		leftMove();
		upMove(_ladder);
		downMove(_ladder);
	}
}

void player_Eric::keyPressSpace()
{
	//================================================================ 점프 예외처리 
	if (!(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT ||
		_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT || _isFCollision ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN))
	{
		return;
	}
	//================================================================ 점프 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//만야에 플레이어가 왼쪽을 보거나 왼쪽으로 이동하고 있다면
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_state = PLAYER_JUMP_LEFT;
			EricAniStart("jump_left");
		}
		//만약에 플레이어가 오른쪽을 보거나 오른쪽으로 이동하고있다면
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
		}
		//만약에 플레이어가 사다리로 올라가고있거나 내려오고있다면
		if (_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
		}

		_isJump = true;												//점프 상태임을 확인
		_jumpPower = START_JUMPP;									//점프 파워는 스타트 파워 세팅
		_gravity = GRAVITY * TIMEMANAGER->getElpasedTime();			//낙하를 위해 중력 세팅 

		//=========================================================== 예외처리?
		if (_isJump && _isladderUse)
		{
			_isFall = true;
			_isladderUse = false;
			_isladderup = false;
			_jumpPower = 0;
			_gravity = GRAVITY * TIMEMANAGER->getElpasedTime();
		}
	}
}

void player_Eric::keyPressD()
{
	//특수 스킬이 발동되는 조건 >> 캐릭터의 속도가 맥스 스피드일때
	if (_speed == MAX_SPEED)
	{
		//만약에 D 키를 누른다면
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (!(_state == PLAYER_MOVE_RIGHT || _state == PLAYER_MOVE_LEFT))
			{
				return;
			}
			// 오른쪽으로 이동하는 상태라면
			if (_state == PLAYER_MOVE_RIGHT)
			{
				//상태를 오른쪽 박치기로 바꿔주고 애니메이션 출력
				_state = PLAYER_HEAD_BUTT_RIGHT;
				EricAniStart("head_butt_right");
				_isRSkill = true;
			}
			else if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_HEAD_BUTT_LEFT;
				EricAniStart("head_butt_left");
				_isLSkill = true;
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

void player_Eric::leftMove()
{
	//만약에 사다리 올라가고있다면 왼쪽이동 불가능
	if ((_isladderup && _isUpMove) || (_isladderdown && _isDownMove))
	{
		return;
	}
	if (!_isRightMove && !_isUpMove && !_isDownMove)
	{
		//================================================ 기본속도 및 이동 세팅
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isBCollision)						//캐릭터가 바닥 픽셀충돌중이라면 
			{
				_isLeftMove = true;					//왼쪽으로 이동한다.
				_speed = MIN_SPEED;					//스피드는 미니멈 스피드로 시작
				_state = PLAYER_MOVE_LEFT;			//상태는 왼쪽으로 이동중으로 변경
				EricAniStart("move_left");			//애니메이션은 왼쪽으로 이동하는 애니메이션

				//======================================= 예외처리용
				_isFall = false;		//떨어지고 있지 않으므로
				_isladderUse = false;	//사다리 사용중이 아니므로
			}
			//만약에 캐릭터가 사다리에 매달려있을때 왼쪽키를 누르면 
			if (_isladderUse)
			{
				_state = PLAYER_FALL_LEFT;
			}
		}
		//================================================ 실제 움직임 세팅
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//만약에 바닥 충돌중에 
			if (_isBCollision)
			{
				//스피드가 맥스 스피드보다 작다면
				if (_speed < MAX_SPEED)
				{
					//속도는 가속도 * 시간으로 계속 더해서 상승한다.
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
				//속도가 맥스 스피드보다 큰 상태라면
				else
				{
					//스피드를 맥스스피드로 고정한다.
					_speed = MAX_SPEED;

					if (_isladderUse || _isladderup)
					{
						_speed = MIN_SPEED;
					}
				}
				//만약에 왼쪽으로 박치기하는 상태라면
				if (_state == PLAYER_HEAD_BUTT_LEFT)
				{
					if (_EricMotion->isPlay() == false)
					{
						EricAniStart("move_left");
					}
				}
			}
			//============================================ 맵내 이동 제한 처리
			//만약에 캐릭터가 맵 크기의 왼쪽을 넘어가지 못하도록 처리 
			if (_x - (_size.x / 2) < 0)
			{
				_x = 0 + (_size.x / 2);
			}
			//============================================ 벽 픽셀충돌 처리
			//만약에 사다리를 사용하지않고 올라가지도 않고 있다면 
			//만약에 왼쪽 벽과 픽셀충돌을 하지 않고 있다면
			if (!_isLCollision)
			{
				_x -= _speed * TIMEMANAGER->getElpasedTime();

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

						if (_isLCollision && _isLeftMove)
						{
							_state = PLAYER_PUSH_WALL_LEFT;
							_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "push_wall_left");

							if (!_EricMotion->isPlay())
							{
								KEYANIMANAGER->start("player_eric", "push_wall_left");
							}
						}

					}
					else
					{
						_isLCollision = false;						//그게아니라면 충돌안했다
					}
				}
			}

		}
		//================================================ 기본속도 및 이동 리셋
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_isLeftMove = false;						//왼쪽으로 이동안함.
			_speed = MIN_SPEED;							//스피드는 미니멈 스피드로 리셋
			if (_state == PLAYER_HEAD_BUTT_LEFT)
			{
				_state = PLAYER_SIGN_LEFT;
				EricAniStart("sign_left");
				_aniCount += 1;
			}
			else
			{
				_state = PLAYER_IDLE_LEFT;				//상태는 왼쪽 바라보는 애니메이션 출력
			}
		}
		if (_state == PLAYER_SIGN_LEFT)
		{
			if (_EricMotion->isPlay() == false)
			{
				if (_aniCount < 3)
				{
					EricAniStart("sign_left");
					_aniCount += 1;
				}
				else if (_aniCount == 3)
				{
					_aniCount = 0;
					_state = PLAYER_IDLE_LEFT;
					EricAniStart("idleleft");
				}
			}
		}
		if (_isFall)
		{
			_state = PLAYER_FALL_LEFT;
			EricAniStart("jump_fall_left");
		}
	}
}

void player_Eric::rightMove()
{
	//만약에 사다리타고 위로 올라가고있다면오른쪽이동 불가능 
	if ((_isladderup && _isUpMove) || (_isladderdown && _isDownMove))
	{
		return;
	}
	if (!_isLeftMove)
	{
		//================================================ 기본속도 및 이동 세팅
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			//캐릭터가 바닥이랑 충돌중에 
			if (_isBCollision)
			{
				_isRightMove = true;				//오른쪽으로 이동한다.
				_speed = MIN_SPEED;					//스피드는 미니멈 스피드로 시작
				_state = PLAYER_MOVE_RIGHT;			//상태는 오른쪽 이동하는 애니메이션 출력
				EricAniStart("move_right");
			}
			//만약에 캐릭터가 사다리에 매달려있을때 오른쪽키를 누르면 
			if (_isladderUse)
			{
				_isFall = true;
			}
		}
		//================================================ 실제 움직임 세팅
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//바닥이랑 충돌하면서 이동중에 
			if (_isBCollision && _isRightMove)
			{
				//만약에 속도가 맥스 스피드보다 작으면
				if (_speed < MAX_SPEED)
				{
					//속도는 가속도 * 시간으로 계속 더해서 상승한다.
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
				//속도가 맥스 스피드보다 큰 상태라면
				else
				{
					//스피드를 맥스스피드로 고정한다.
					_speed = MAX_SPEED;
				}
				//만약에 상태가 박치기하는 상태라면 
				if (_state == PLAYER_HEAD_BUTT_RIGHT)
				{
					if (_EricMotion->isPlay() == false)
					{
						EricAniStart("move_right");
					}
				}
			}
			//또는 사다리를 올라가고 있는 중이라면
			if (_isUpMove)
			{
				_speed = 5;
				_x += _speed;
				_isFall = true;
			}
			//============================================ 맵내 이동 제한 처리
			//만약에 캐릭터가 맵 크기의 오른쪽을 넘어가지 못하도록 처리 
			if (_x + (_size.x / 2) > _pixelData->GetWidth())
			{
				_x = _pixelData->GetWidth() - (_size.x / 2);
			}
			//============================================ 벽 픽셀충돌 처리
			//만약에 오른쪽 벽과 픽셀충돌을 하지 않고 있다면
			if (!_isRCollision)
			{
				_x += _speed * TIMEMANAGER->getElpasedTime();

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
							_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "push_wall_right");

							if (!_EricMotion->isPlay())
							{
								KEYANIMANAGER->start("player_eric", "push_wall_right");
							}
						}
						//만약에 벽에 충돌하고 이동중이고 오른쪽 스킬을 사용했다면 
						if (_isRCollision && _isRightMove && _isRSkill)
						{
							if (_state != PLAYER_STUN_RIGHT)
							{
								_state = PLAYER_STUN_RIGHT;
								EricAniStart("stun_right");
							}

						}
					}
					else
					{
						_isRCollision = false;
					}
				}
			}
		}
		//================================================ 기본속도 및 이동 리셋
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_isRightMove = false;				//오른쪽으로 이동안함.
			_speed = MIN_SPEED;			//스피드는 미니멈 스피드로 리셋

			//만약에 박치기 달리기중이라면
			if (_state == PLAYER_HEAD_BUTT_RIGHT)
			{
				//상태를 한숨쉬는걸로 바꿔주고 애니메이션 출력후 애니카운트+1
				_state = PLAYER_SIGN_RIGHT;
				EricAniStart("sign_right");
				_aniCount += 1;
			}
			//만약에 스턴에 걸린 상태일때
			else if (_state == PLAYER_STUN_RIGHT)
			{
				//너는 왜 되니?
			}
			else
			{
				_state = PLAYER_IDLE_RIGHT;	//상태는 오른쪽 바라보는 애니메이션 출력
			}
		}
		//================================================ 예외처리
		if (_state == PLAYER_SIGN_RIGHT)
		{
			if (_EricMotion->isPlay() == false)
			{
				if (_aniCount < 3)
				{
					EricAniStart("sign_right");
					_aniCount += 1;
				}
				else if (_aniCount == 3)
				{
					_aniCount = 0;
					_state = PLAYER_IDLE_RIGHT;
					EricAniStart("idleright");
				}
			}
		}
		else if (_state == PLAYER_STUN_RIGHT)
		{
			if (_EricMotion->isPlay() == false)
			{
				_isRSkill = false;
				_state = PLAYER_IDLE_RIGHT;
				EricAniStart("idleright");
			}
		}
		if (_isFall)
		{
			_state = PLAYER_FALL_RIGHT;
			EricAniStart("jump_fall_right");
		}
	}
}

void player_Eric::upMove(object * ladder)
{
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
}


void player_Eric::downMove(object * ladder)
{
	_ladder = ladder;
	RECT temp;
	if (_isRightMove || _isLeftMove)
	{
		return;
	}
	//=================================================== 상태 및 좌표 세팅
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
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
					// 플레이어가 사다리로 내려가고 있지 않다면 
					if (!_isladderdown)
					{
						//몇번째의 사다리인지 체크하기위해 인덱스 설정
						_ladderIndex = i;
						//캐릭터의 x 좌표를 사다리의 x좌표로 맞추어준다.
						float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;
						_x = ladderX;
						//캐릭터의 상태를 사다리 타는중으로 변경하면서 사다리에 매달리는 애니메이션을 출력해주자
						_state = PLAYER_LADDER_DOWN;
						EricAniStart("ladder_down");
						//캐릭터는 사다리에 매달려 있고, 올라가고 있으므로 체크용 불값도 변경
						_isladderUse = true;
						_isladderdown = true;
						_isDownMove = true;
						//사다리에 매달려있으면 떨어지는중이 아니므로
						_isFall = false;
					}
				}
			}
		}
	}
	//=================================================== 실제 움직임 구현
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//만약에 사다리에 캐릭터가 매달려있고, 위로 올라가는 중이라면
		if (_isladderUse && _isladderdown)
		{
			_y += _speed;
			//만약에 사다리의 인덱스가 0보다 크거나 같고, 최대 개수보다는 작을때
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//만약에 사다리의 윗쪽 값보다 캐릭터의 하단값이 같거나 크다면
				if (_ladderRc[_ladderIndex]->bottom <= _playerRect.bottom)
				{
					//캐릭터의 상태는 사다리 끝이 되고, 사다리 끝 체크 불값을 true로 바꿔준다.
					_state = PLAYER_IDLE_RIGHT;
					_isDeladder = true;
					EricAniStart("idleright");
				}
			}
		}
	}
	//=================================================== 리셋
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		//키를 때면 올라가고있지 않으므로 변수를 false처리한다.
		_isladderdown = false;
		KEYANIMANAGER->pause("player_eric", "ladder_down");
	}
	//=================================================== 예외처리
	if (_state == PLAYER_IDLE_RIGHT)
	{
		_isladderup = false;
		_isladderUse = false;
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
	_aniCount = 0;
	//이미지 추가
	_player = IMAGEMANAGER->addFrameImage("player_eric", "image/eric.bmp", 704, 1024, 11, 16, true, RGB(255, 0, 255));
	//애니메이션 타입추가
	KEYANIMANAGER->addAnimationType("player_eric");

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
	int sign_right[] = { 4, 5, 6 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "sign_right", "player_eric", sign_right, 3, 10, false);
	int sign_left[] = { 7, 8, 9 };
	KEYANIMANAGER->addArrayFrameAnimation("player_eric", "sign_left", "player_eric", sign_left, 3, 10, false);

	//기본 애니메이션 설정
	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleright");
	KEYANIMANAGER->start("player_eric", "idleright");
}

void player_Eric::EricAni()
{
	if (_state == PLAYER_IDLE_RIGHT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleright");

	}
	if (_state == PLAYER_IDLE_LEFT)
	{
		_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "idleleft");
	}

}

void player_Eric::EricAniStart(string key)
{
	_EricMotion = KEYANIMANAGER->findAnimation("player_eric", key);
	KEYANIMANAGER->start("player_eric", key);
}
