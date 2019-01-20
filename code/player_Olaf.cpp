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
	initImgOlaf();

	return S_OK;
}

void player_Olaf::release()
{
}

void player_Olaf::update()
{
	//충돌처리
	pixelBottomCollision();
	stateOlaf();

	//갱신
	_playerRect = RectMakeCenter(_x, _y, 70, 70);
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;

	//애니메이션업데이트
	KEYANIMANAGER->update("player_Olaf");

	//방패갱신
	stateShield();
}

void player_Olaf::render()
{
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _olafMotion);

	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERA->getMemDC(), _playerRect, false);
		if (!_isShieldUp)
			Rectangle(CAMERA->getMemDC(), _shield, false);

	}
}

void player_Olaf::keyPressMove()
{

	//방패를 위로 들고 있지 않다면
	if (!_isShieldUp)
	{
		// ============================ 좌우 ============================
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_gravity = GRAVITY;
			_speed = 2.0f;
			_state = PLAYER_IDLE_RIGHT;
			startAniOlaf("idle_Right");

		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = PLAYER_MOVE_RIGHT;
			pixelRightWallCollision();
			playerCollisionLadder();
			if (_isRightCollision || _pixelData->GetWidth() <= _playerRect.right)
			{
				if (!_isAniStart)
				{
					_speed = 0;
					_state == PLAYER_PUSH_WALL_RIGHT;
					startAniOlaf("push_Wall_Right");
					_isAniStart = true;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRightCollision)
			{
				_state = PLAYER_PUSH_WALL_RIGHT;
				startAniOlaf("push_Wall_Right");
			}
			else
			{
				_isAniStart = false;
				_state = PLAYER_MOVE_RIGHT;
				startAniOlaf("move_Right");
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_speed = 2.0f;
			_state = PLAYER_IDLE_LEFT;
			startAniOlaf("idle_Left");
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = PLAYER_MOVE_LEFT;
			pixelLeftWallCollision();
			playerCollisionLadder();
			if (_isLeftCollision || _playerRect.left <= 0)
			{
				if (!_isAniStart)
				{
					_speed = 0.f;
					_state == PLAYER_PUSH_WALL_LEFT;
					startAniOlaf("push_Wall_Left");
					_isAniStart = true;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isLeftCollision)
			{
				_state = PLAYER_PUSH_WALL_LEFT;
				startAniOlaf("push_Wall_Left");
			}
			else
			{
				_isAniStart = false;
				_state = PLAYER_MOVE_LEFT;
				startAniOlaf("move_Left");
			}
		}
		// ============================ 상하 ============================

		if (KEYMANAGER->isOnceKeyUp(VK_UP))
		{
			_state = PLAYER_IDLE_LEFT;
			startAniOlaf("idle_Left");
		}

		if (_isLadder)
		{
			if (KEYMANAGER->isStayKeyDown(VK_UP))
			{
				_state = PLAYER_LADDER_UP;
			}
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{

				_state = PLAYER_LADDER_UP;
				startAniOlaf("ladder_Up");
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
		{
			_state = PLAYER_IDLE_LEFT;
			startAniOlaf("idle_Left");
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_state = PLAYER_LADDER_DOWN;
		}
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_state = PLAYER_LADDER_DOWN;
			startAniOlaf("ladder_Down");
		}

	}
	//방패를 위로 들고 있다면
	else
	{
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_speed = 2.0f;
			_state = PLAYER_SHIELD_IDLE_RIGHT;
			startAniOlaf("idle_Shield_Right");

		}
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			_state = PLAYER_SHIELD_MOVE_RIGHT;
			pixelRightWallCollision();
			if (_isRightCollision || _pixelData->GetWidth() <= _playerRect.right)
			{
				if (!_isAniStart)
				{
					_speed = 0;
					_state == PLAYER_PUSH_WALL_RIGHT;
					startAniOlaf("push_Wall_Right");
					_isAniStart = true;
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			if (_isRightCollision)
			{
				_state = PLAYER_PUSH_WALL_RIGHT;
				startAniOlaf("push_Wall_Right");
			}
			else
			{
				_isAniStart = false;
				_state = PLAYER_SHIELD_MOVE_RIGHT;
				startAniOlaf("move_Shield_Right");
			}
		}

		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_speed = 2.0f;
			_state = PLAYER_SHIELD_IDLE_LEFT;
			startAniOlaf("idle_Shield_Left");
		}

		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			_state = PLAYER_SHIELD_MOVE_LEFT;
			pixelLeftWallCollision();
			if (_isLeftCollision || _playerRect.left <= 0)
			{
				if (!_isAniStart)
				{
					_speed = 0.f;
					_state == PLAYER_PUSH_WALL_LEFT;
					startAniOlaf("push_Wall_Left");
					_isAniStart = true;
				}
			}
		}

		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isLeftCollision)
			{
				_state = PLAYER_PUSH_WALL_LEFT;
				startAniOlaf("push_Wall_Left");
			}
			else
			{
				_isAniStart = false;
				_state = PLAYER_SHIELD_MOVE_LEFT;
				startAniOlaf("move_Shield_Left");
			}
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
				startAniOlaf("idle_Shield_Right");
			}
			//왼쪽을 보고 있다면
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//방패를 위로 들고 왼쪽을 본다.
				startAniOlaf("idle_Shield_Left");
			}
			//오른쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//방패를 위로 들고 오른쪽으로 이동한다.
				startAniOlaf("move_Shield_Right");
			}
			//왼쪽으로 이동하고 있다면
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//방패를 위로 들고 왼쪽으로 이동한다.
				startAniOlaf("move_Shield_Left");
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
				startAniOlaf("idle_Right");
			}
			//방패를 위로 들고 왼쪽을 보고 있다면
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//왼쪽을 본다.
				startAniOlaf("idle_Left");
			}
			//방패를 위로 들고 오른쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//오른쪽으로 이동한다.
				startAniOlaf("move_Right");
			}
			//방패를 위로 들고 왼쪽으로 이동하고 있다면
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//왼쪽으로 이동한다.
				startAniOlaf("move_Left");
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
	_y = 1400;								   //Y좌표
	_speed = 2.0f;							   //스피드
	_lifeCount = 3;							   //체력

	_proveBottom = _playerRect.bottom + 5;		//충돌처리
	_proveRight = _playerRect.right;			//충돌처리
	_proveLeft = _playerRect.left;				//충돌처리


	_playerRect = RectMakeCenter(_x, _y, 70, 70); //올라프렉트생성
}

void player_Olaf::stateOlaf()
{
	switch (_state)
	{
		case PLAYER_IDLE_RIGHT:
		case PLAYER_IDLE_LEFT:
		case PLAYER_SHIELD_IDLE_RIGHT:
		case PLAYER_SHIELD_IDLE_LEFT:
			break;

		case PLAYER_MOVE_RIGHT:
		case PLAYER_SHIELD_MOVE_RIGHT:
		{
			_x += _speed;
			break;
		}
		case PLAYER_MOVE_LEFT:
		case PLAYER_SHIELD_MOVE_LEFT:
		{
			_x -= _speed;
			break;
		}
		case PLAYER_LADDER_UP:
		{
			if (_isLadder)
			{
				_y -= _speed;
			}
			break;
		}
		case PLAYER_LADDER_DOWN:
		{
			_y += _speed;
			break;
		}

	}



}

void player_Olaf::initImgOlaf()
{
	KEYANIMANAGER->addAnimationType("player_Olaf");
	_player = IMAGEMANAGER->addFrameImage("olaf", "image/olaf.bmp", 1960, 420, 28, 6, true, RGB(255, 0, 255));
	_state = PLAYER_IDLE_RIGHT;

	int idle_Right[] = { 1 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "idle_Right", "olaf", idle_Right, 1, 10, true);
	int idle_Left[] = { 29 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "idle_Left", "olaf", idle_Left, 1, 10, true);
	int move_Right[] = { 13, 14, 15, 16, 17, 18, 19, 20 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "move_Right", "olaf", move_Right, 8, 10, true);
	int move_Left[] = { 41, 42, 43, 44, 45, 46, 47, 48 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "move_Left", "olaf", move_Left, 8, 10, true);
	int idle_Shield_Right[] = { 99 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "idle_Shield_Right", "olaf", idle_Shield_Right, 1, 10, true);
	int idle_Shield_Left[] = { 127 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "idle_Shield_Left", "olaf", idle_Shield_Left, 1, 10, true);
	int move_Shield_Right[] = { 103, 104, 105, 106, 107, 108, 109, 110 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "move_Shield_Right", "olaf", move_Shield_Right, 8, 10, true);
	int move_Shield_Left[] = { 131, 132, 133, 134, 135, 136, 137, 138 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "move_Shield_Left", "olaf", move_Shield_Left, 8, 10, true);
	int push_Wall_Right[] = { 58, 59, 60, 61 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "push_Wall_Right", "olaf", push_Wall_Right, 4, 5, true);
	int push_Wall_Left[] = { 62, 63, 64, 65 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "push_Wall_Left", "olaf", push_Wall_Left, 4, 5, true);
	int ladder_Up[] = { 66, 67, 68, 69 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "ladder_Up", "olaf", ladder_Up, 4, 10, true);
	int ladder_Down[] = { 69, 68, 67, 66 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "ladder_Down", "olaf", ladder_Down, 4, 10, true);
	int ladder_End[] = { 70, 71 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "ladder_End", "olaf", ladder_End, 2, 10, false);

	_olafMotion = KEYANIMANAGER->findAnimation("player_Olaf", "idle_Right");

}

void player_Olaf::startAniOlaf(string aniKey)
{
	_olafMotion = KEYANIMANAGER->findAnimation("player_Olaf", aniKey);
	KEYANIMANAGER->start("player_Olaf", aniKey);

}

void player_Olaf::shieldRender(HDC hdc)
{
	if (_isShieldUp)
		RectangleBrushPen(hdc, _shield, RGB(255, 0, 255), true);
}

void player_Olaf::initShield()
{
	_isShieldUp = false;																//방패들었니?
	_shield = RectMake(_playerRect.right - 10, _playerRect.top, 10, 70);				//방패렉트생성
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
			_shield = RectMake(_playerRect.right - 60, _playerRect.top + 5, 55, 10);			//오른쪽으로 방패렉트를 갱신한다.
		}
		//플레이어가 왼쪽을 보고 있다면
		if (_state == PLAYER_SHIELD_IDLE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left + 5, _playerRect.top + 5, 55, 10);				//왼쪽으로 방패렉트를 갱신한다.
		}
	}
}

void player_Olaf::pixelLeftWallCollision()
{
	for (int i = _proveLeft + 5; i > _proveLeft; --i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_speed = 0.f;								//스피드를 0으로 내려 이동하지 않도록 한다.
			_isLeftCollision = true;
		}
		else
		{
			_isLeftCollision = false;
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
			_speed = 0.f;									//스피드를 0으로 내려 이동하지 않도록 한다.
			_isRightCollision = true;
		}
		else
		{
			_isRightCollision = false;
		}
	}
}

void player_Olaf::pixelBottomCollision()
{
	if (_state == PLAYER_LADDER_UP) return;
	for (int i = _proveBottom - 5; i < _proveBottom + 5; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 255)
		{
			_y = i - 35;										   //플레이어 좌표 보정
			_isFloor = true;
			break;
		}
	}
}

void player_Olaf::playerCollisionLadder()
{
	RECT temp;
	int size = _ladderRc.size();
	for (int i = 0; i < size; i++)
	{
		if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
		{
			_isLadder = true;
			_isFloor = false;
		}
		else
		{
			_isLadder = false;
		}

	}
}

