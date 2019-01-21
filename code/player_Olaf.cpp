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
	//�ʱ�ȭ
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
	//�ִϸ��̼Ǿ�����Ʈ
	KEYANIMANAGER->update("player_Olaf");

	//�浹ó��
	stateOlaf();
	pixelBottomCollision();
	pixelFireCollision();
	playerCollisionLadder();

	//����
	_playerRect = RectMakeCenter(_x, _y, 70, 70);
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;


	//���а���
	stateShield();

}

void player_Olaf::render()
{
	_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _olafMotion);


	if (KEYMANAGER->isToggleKey(VK_TAB))
	{
		Rectangle(CAMERA->getMemDC(), _playerRect, false);
	}

}

void player_Olaf::keyPressMove()
{
	if (_isAlive)
	{//���и� ���� ��� ���� �ʴٸ�
		if (!_isShieldUp)
		{
			// ============================ �¿� ============================
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				_speed = 0.1f;
				_state = PLAYER_IDLE_RIGHT;
				startAniOlaf("idle_Right");
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_FALL_RIGHT;
					startAniOlaf("fall_Right");
				}
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_state = PLAYER_MOVE_RIGHT;
				pixelRightWallCollision();
				if (_isRightCollision || _pixelData->GetWidth() <= _playerRect.right)
				{
					if (!_isAniStart)
					{
						_speed = 0;
						_state = PLAYER_PUSH_WALL_RIGHT;
						startAniOlaf("push_Wall_Right");
						_isAniStart = true;
					}
				}
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_FALL_RIGHT;
					startAniOlaf("fall_Right");
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
				_speed = 0.1f;
				_state = PLAYER_IDLE_LEFT;
				startAniOlaf("idle_Left");
			}

			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_state = PLAYER_MOVE_LEFT;
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
					_state = PLAYER_MOVE_LEFT;
					startAniOlaf("move_Left");
				}
			}
			// ============================ ���� ============================
			if (_isLadder)
			{
				if (KEYMANAGER->isStayKeyDown(VK_UP))
					_state = PLAYER_LADDER_UP;

				if (KEYMANAGER->isOnceKeyDown(VK_UP))
				{
					_state = PLAYER_LADDER_UP;
					startAniOlaf("ladder_Up");
				}
				if (KEYMANAGER->isOnceKeyUp(VK_UP))
				{
					_speed = 0.1f;
					_state = PLAYER_IDLE_RIGHT;
					_olafMotion->pause();
				}
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
					_state = PLAYER_LADDER_DOWN;

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					_state = PLAYER_LADDER_DOWN;
					startAniOlaf("ladder_Down");
				}
				if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
				{
					_speed = 0.1f;
					_state = PLAYER_IDLE_RIGHT;
					_olafMotion->pause();
				}
			}
		}
		//���и� ���� ��� �ִٸ�
		else
		{
			// ============================ �¿� ============================
			if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
			{
				_speed = 0.1f;
				_state = PLAYER_SHIELD_IDLE_RIGHT;
				startAniOlaf("idle_Shield_Right");
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_SHIELD_FALL_RIGHT;
					startAniOlaf("fall_Shield_Right");
				}
			}
			if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
			{
				_state = PLAYER_MOVE_RIGHT;
				pixelRightWallCollision();
				if (_isRightCollision || _pixelData->GetWidth() <= _playerRect.right)
				{
					if (!_isAniStart)
					{
						_speed = 0;
						_state = PLAYER_PUSH_WALL_RIGHT;
						startAniOlaf("push_Wall_Right");
						_isAniStart = true;
					}
				}
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_SHIELD_FALL_RIGHT;
					startAniOlaf("fall_Shield_Right");
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
				_speed = 0.1f;
				_state = PLAYER_SHIELD_IDLE_LEFT;
				startAniOlaf("idle_Shield_Left");
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_SHIELD_FALL_LEFT;
					startAniOlaf("fall_Shield_Left");
				}
			}

			if (KEYMANAGER->isStayKeyDown(VK_LEFT))
			{
				_state = PLAYER_MOVE_LEFT;
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
				if (!_isFloor && !_isLadder)
				{
					_state = PLAYER_SHIELD_FALL_LEFT;
					startAniOlaf("fall_Shield_Left");
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
			// ============================ ���� ============================
			if (_isLadder)
			{
				if (KEYMANAGER->isStayKeyDown(VK_UP))
					_state = PLAYER_LADDER_UP;

				if (KEYMANAGER->isOnceKeyDown(VK_UP))
				{
					_state = PLAYER_LADDER_UP;
					startAniOlaf("ladder_Up");
				}
				if (KEYMANAGER->isOnceKeyUp(VK_UP))
				{
					_speed = 0.1f;
					_state = PLAYER_SHIELD_IDLE_RIGHT;
					_olafMotion->pause();
				}
				if (KEYMANAGER->isStayKeyDown(VK_DOWN))
					_state = PLAYER_LADDER_DOWN;

				if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
				{
					_state = PLAYER_LADDER_DOWN;
					startAniOlaf("ladder_Down");
				}
				if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
				{
					_speed = 0.1f;
					_state = PLAYER_SHIELD_IDLE_RIGHT;
					_olafMotion->pause();
				}
			}
		}
	}
}

void player_Olaf::keyPressSpace()
{

	//��Ÿ���� ź ���¿����� SPACE ������ ���°� �ٲ��� �ʴ´�.
	//���и� ���� ��� ���� �ʴٸ�
	if (!_isShieldUp)
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//���°� ����ȴ�.
			_isShieldUp = true;

			//�÷��̾� ���°� �������� ���� �ִٸ�
			if (_state == PLAYER_IDLE_RIGHT)
			{
				_state = PLAYER_SHIELD_IDLE_RIGHT;					//���и� ���� ��� �������� ����.
				startAniOlaf("idle_Shield_Right");
			}
			//������ ���� �ִٸ�
			if (_state == PLAYER_IDLE_LEFT)
			{
				_state = PLAYER_SHIELD_IDLE_LEFT;					//���и� ���� ��� ������ ����.
				startAniOlaf("idle_Shield_Left");
			}
			//���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_RIGHT)
			{
				_state = PLAYER_SHIELD_MOVE_RIGHT;					//���и� ���� ��� ���������� �̵��Ѵ�.
				startAniOlaf("move_Shield_Right");
			}
			//�������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_MOVE_LEFT)
			{
				_state = PLAYER_SHIELD_MOVE_LEFT;					//���и� ���� ��� �������� �̵��Ѵ�.
				startAniOlaf("move_Shield_Left");
			}
			//���������� �������� �ִٸ�
			if (_state == PLAYER_FALL_RIGHT)
			{
				_state = PLAYER_SHIELD_FALL_RIGHT;					//���и� ���� ��� ���������� õõ�� ��������.
				startAniOlaf("fall_Shield_Right");
			}
			//�������� �������� �ִٸ�
			if (_state == PLAYER_FALL_LEFT)
			{
				_state = PLAYER_SHIELD_FALL_LEFT;					//���и� ���� ��� �������� õõ�� ��������.
				startAniOlaf("fall_Shield_Left");
			}
		}
	}
	else
	{
		//�����̽��ٸ� �������� ������ ��ġ�� ����ȴ�.
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			//���°� ����ȴ�.
			_isShieldUp = false;

			//�÷��̾� ���°� ���и� ���� ��� �������� ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_RIGHT)
			{
				_state = PLAYER_IDLE_RIGHT;							//�������� ����.
				startAniOlaf("idle_Right");
			}
			//���и� ���� ��� ������ ���� �ִٸ�
			if (_state == PLAYER_SHIELD_IDLE_LEFT)
			{
				_state = PLAYER_IDLE_LEFT;							//������ ����.
				startAniOlaf("idle_Left");
			}
			//���и� ���� ��� ���������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_RIGHT)
			{
				_state = PLAYER_MOVE_RIGHT;							//���������� �̵��Ѵ�.
				startAniOlaf("move_Right");
			}
			//���и� ���� ��� �������� �̵��ϰ� �ִٸ�
			if (_state == PLAYER_SHIELD_MOVE_LEFT)
			{
				_state = PLAYER_MOVE_LEFT;							//�������� �̵��Ѵ�.
				startAniOlaf("move_Left");
			}
			//���и� ���� ��� ���������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_RIGHT;							//���������� ��������.
				startAniOlaf("fall_Right");
			}
			//���и� ���� ��� �������� �������� �ִٸ�
			if (_state == PLAYER_SHIELD_FALL_LEFT)
			{
				//���⼭ �������� �ӵ��� ����
				_state = PLAYER_FALL_LEFT;							//�������� ��������.
				startAniOlaf("fall_Left");
			}
		}
	}
}

void player_Olaf::keyPressD()
{
	//��� �����̽���ɰ� �����ϴ� �����̽� �� �ϸ� ��������.. �ڵ尡 �� �� �򰥸���...
}

void player_Olaf::initOlaf()
{
	_x = 300;								   //X��ǥ
	_y = 1250;								   //Y��ǥ
	_speed = 0.f;							   //���ǵ�
	_lifeCount = 3;							   //ü��

	_isAlive = true;
	_isFloor = true;
	_isLadder = false;
	_isLadderTop = false;

	_proveBottom = _playerRect.bottom + 5;		//�浹ó��
	_proveRight = _playerRect.right;			//�浹ó��
	_proveLeft = _playerRect.left;				//�浹ó��


	_playerRect = RectMakeCenter(_x, _y, 70, 70); //�ö�����Ʈ����
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
			if (!_isRightCollision)
			{
				if (_speed < 2.0f)
				{
					_speed += 3 * TIMEMANAGER->getElpasedTime();
				}
				else
				{
					_speed = 2.0f;
				}
			}
			_x += _speed;
			break;
		}
		case PLAYER_MOVE_LEFT:
		case PLAYER_SHIELD_MOVE_LEFT:
		{
			if (!_isLeftCollision)
			{
				if (_speed < 2.0f)
				{
					_speed += 3 * TIMEMANAGER->getElpasedTime();
				}
				else
				{
					_speed = 2.0f;
				}
			}
			_x -= _speed;
			break;
		}
		case PLAYER_LADDER_UP:
		{
			_speed = 2.5f;
			_y -= _speed;
			break;
		}
		case PLAYER_LADDER_DOWN:
		{
			_speed = 2.5f;
			_y += _speed;
			break;
		}
		case PLAYER_FALL_RIGHT:
		case PLAYER_FALL_LEFT:
		{
			_gravity = GRAVITY;
			_y += _gravity * TIMEMANAGER->getElpasedTime();
			break;
		}
		case PLAYER_SHIELD_FALL_LEFT:
		case PLAYER_SHIELD_FALL_RIGHT:
		{
			if (!_isFloor && !_isLadder)
			{
				_gravity = 50.0f;
				_y += _gravity * TIMEMANAGER->getElpasedTime();
			}
			if (_isFloor)
			{
				if (_state == PLAYER_SHIELD_FALL_RIGHT)
				{
					_state = PLAYER_SHIELD_IDLE_RIGHT;
					startAniOlaf("idle_Shield_Right");
				}
				else if (_state == PLAYER_SHIELD_FALL_LEFT)
				{
					_state = PLAYER_SHIELD_IDLE_LEFT;
					startAniOlaf("idle_Shield_Left");
				}
			}
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
	int fall_Right[] = { 21, 22 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fall_Right", "olaf", fall_Right, 2, 10, false);
	int fall_Left[] = { 49, 50 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fall_Left", "olaf", fall_Left, 2, 10, false);
	int fire_Death_Right[] = { 91, 92, 93, 94, 95, 96, 97, 98 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fire_Death_Right", "olaf", fire_Death_Right, 8, 10, false);
	int fire_Death_Left[] = { 119, 120, 121, 122, 123, 124, 125, 126 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fire_Death_Left", "olaf", fire_Death_Left, 8, 10, false);
	int fall_Shield_Right[] = { 141, 142 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fall_Shield_Right", "olaf", fall_Shield_Right, 2, 5, true);
	int fall_Shield_Left[] = { 145, 146 };
	KEYANIMANAGER->addArrayFrameAnimation("player_Olaf", "fall_Shield_Left", "olaf", fall_Shield_Left, 2, 5, true);

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
	_isShieldUp = false;																//���е����?
	_shield = RectMake(_playerRect.right - 10, _playerRect.top, 10, 70);				//���з�Ʈ����
}

void player_Olaf::stateShield()
{
	//���и� ���� �ȵ���ٸ�
	if (!_isShieldUp)
	{
		//�÷��̾ �������� ���� �ִٸ�
		if (_state == PLAYER_IDLE_RIGHT || _state == PLAYER_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right - 10, _playerRect.top, 10, 70);			//���������� ���з�Ʈ�� �����Ѵ�.
		}
		//�÷��̾ ������ ���� �ִٸ�
		if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left, _playerRect.top, 10, 70);				//�������� ���з�Ʈ�� �����Ѵ�.
		}
	}
	//���и� ���� ����ٸ�
	else
	{
		//�÷��̾ �������� ���� �ִٸ�
		if (_state == PLAYER_SHIELD_IDLE_RIGHT || _state == PLAYER_SHIELD_MOVE_RIGHT)
		{
			_shield = RectMake(_playerRect.right - 60, _playerRect.top + 5, 55, 10);			//���������� ���з�Ʈ�� �����Ѵ�.
		}
		//�÷��̾ ������ ���� �ִٸ�
		if (_state == PLAYER_SHIELD_IDLE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT)
		{
			_shield = RectMake(_playerRect.left + 5, _playerRect.top + 5, 55, 10);				//�������� ���з�Ʈ�� �����Ѵ�.
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
			_speed = 0.f;								//���ǵ带 0���� ���� �̵����� �ʵ��� �Ѵ�.
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
			_speed = 0.f;									//���ǵ带 0���� ���� �̵����� �ʵ��� �Ѵ�.
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
			_y = i - 35;										   //�÷��̾� ��ǥ ����
			_isFloor = true;
			_isLadder = false;
			break;
		}
		else if (!(r == 255 && g == 0 && b == 255))
		{
			_isFloor = false;
			_isLadder = false;
		}
	}
}

void player_Olaf::pixelFireCollision()
{
	for (int i = _playerRect.bottom - 10; i < _playerRect.bottom + 10; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			if (_state == PLAYER_IDLE_RIGHT || _state == PLAYER_MOVE_RIGHT ||
				_state == PLAYER_FALL_RIGHT || _state == PLAYER_HIGH_FALL_RIGHT ||
				_state == PLAYER_SHIELD_IDLE_RIGHT || _state == PLAYER_SHIELD_MOVE_RIGHT ||
				_state == PLAYER_SHIELD_FALL_RIGHT)
			{
				_state = PLAYER_FIRE_DEATH_RIGHT;
				startAniOlaf("fire_Death_Right");
			}
			if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT ||
				_state == PLAYER_FALL_LEFT || _state == PLAYER_HIGH_FALL_LEFT ||
				_state == PLAYER_SHIELD_IDLE_LEFT || _state == PLAYER_SHIELD_MOVE_LEFT ||
				_state == PLAYER_SHIELD_FALL_LEFT)
			{
				_state = PLAYER_FIRE_DEATH_LEFT;
				startAniOlaf("fire_Death_Left");
			}
			_y = i - 35;

			_isFloor = false;
			_isLadder = false;
			_lifeCount = 0;
			_speed = 0;
			_isAlive = false;
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
			if (_ladderRc[i]->top <= _playerRect.bottom)
			{
				_isLadder = false;
				_isFloor = false;
				_isLadderTop = true;
			}
			_isLadder = true;
			_isFloor = false;
			_isLadderTop = false;
		}

	}
}
