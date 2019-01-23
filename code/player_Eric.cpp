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
	//ĳ���� ���� ���� �ʱ�ȭ
	ericInit();
	//ĳ���� �ִϸ��̼� ���� �ʱ�ȭ
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

		//�ִϸ��̼�
		EricAni();

	}
	*/

	KEYANIMANAGER->update("player_eric");

	//�̵����� ó��
	if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_HEAD_BUTT_RIGHT)
	{
		if (_isRightMove)
		{
			//���ǵ尡 �ƽ� ���ǵ庸�� ������ �ӵ� ���ó��
			if (_speed < MAX_SPEED)
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
			}
			//�ӵ� ���� ó��
			else
			{
				_speed = MAX_SPEED;
			}
			//�� �ȼ��浹 ó��
			if (!_isRCollision)
			{
				for (int i = _proveRight; i > _proveRight - 32; --i)
				{
					COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//========================================================== �������� �浹ó�� �κ�
					if ((r == 0 && g == 255 && b == 255))
					{
						_isRCollision = true;						//�浹������ Ȯ��

						_x = i - (_size.x / 2);						//�÷��̾� x �� ����

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
			//�������� �̵�
			_x += _speed * TIMEMANAGER->getElpasedTime();
		}
		//================================================================= �� �̵� ����ó�� 
		if (_x + (_size.x / 2) > _pixelData->GetWidth())
		{
			_x = _pixelData->GetWidth() - (_size.x / 2);
		}
	}
	else if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_HEAD_BUTT_LEFT)
	{
		if (_isLeftMove)
		{
			//���ǵ尡 �ƽ� ���ǵ庸�� ������ �ӵ� ���ó��
			if (_speed < MAX_SPEED)
			{
				_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
			}
			//�ӵ� ���� ó��
			else
			{
				_speed = MAX_SPEED;
			}
			//�� �ȼ��浹 ó��
			if (!_isLCollision)
			{
				for (int i = _proveLeft; i < _proveLeft + 32; ++i)
				{
					COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);

					int r = GetRValue(color);
					int g = GetGValue(color);
					int b = GetBValue(color);

					//========================================================== �������� �浹ó�� �κ�
					if ((r == 0 && g == 255 && b == 255))
					{
						_isLCollision = true;						//�浹������ Ȯ��
						_x = i + (_size.x / 2);						//�÷��̾� x��ǥ ����

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
						_isLCollision = false;						//�װԾƴ϶�� �浹���ߴ�
					}
				}
			}
			//�������� �̵�
			_x -= _speed * TIMEMANAGER->getElpasedTime();
			//================================================================= �� �̵� ����ó�� 
			if (_x - (_size.x / 2) < 0)
			{
				_x = 0 + (_size.x / 2);
			}
		}
	}
	//��ٸ����� ó��
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
	//�������� ó��
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
	//��ų���� ó��
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
	//���б� ó��
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
	//���� ó��
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
	//�Ѽ�ó��
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

	//�浹 ó��
	collisioninit();
	pixelBottomCollision();
	//�÷��̾� ��Ʈ ����
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
	//������ �̵� 
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
	//���� �̵�
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

	//���� �̵�
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
			_isJump = true;												//���� �������� Ȯ��
			_jumpPower = START_JUMPP;									//���� �Ŀ��� ��ŸƮ �Ŀ� ����
			_gravity = GRAVITY;											//���ϸ� ���� �߷� ���� 
			EricAniStart("jump_right");
		}
		else if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_MOVE_LEFT)
		{
			_state = PLAYER_JUMP_LEFT;
			_isJump = true;												//���� �������� Ȯ��
			_jumpPower = START_JUMPP;									//���� �Ŀ��� ��ŸƮ �Ŀ� ����
			_gravity = GRAVITY;											//���ϸ� ���� �߷� ���� 
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
				//�ִϸ��̼� ó��
				EricAniStart("head_butt_right");
			}
		}
		if (_isLeftMove)
		{
			if (_speed == MAX_SPEED)
			{
				_isLSkill = true;
				_state = PLAYER_HEAD_BUTT_LEFT;
				//�ִϸ��̼� ó��
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

		// ���࿡ ���� ����Ÿ��� �浹�Ͻÿ� 
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
	//================================================================= ����ó��
	if (_state == PLAYER_JUMP_RIGHT || _state == PLAYER_JUMP_LEFT ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
	{
		return;
	}
	//================================================================= �ȼ��浹
	_isBCollision = false;
	for (int i = _proveBottom - 15; i < _proveBottom + 10; ++i)
	{
		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//========================================================= �������� �浹�κ�
			if (r == 255 && g == 0 && b == 255)
			{
				_y = i - (_size.y / 2);					//�÷��̾��� y���� �������ְ�
				_isBCollision = true;					//�ٴڰ� �浹�ϰ������� Ȯ����
				_isJump = false;						//������ �����ϵ��� ���������� false�� ����
				_isFall = false;						//�ٴڿ� ������ �������� �ִ� ���� �ƴϴ�.
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

				break;									//���̻� x���� �˻縦 ���Ѵ�.
			}
		}
		//�浹�߿� �ִٸ�
		if (_isBCollision)
		{
			break;										//���̻� y���� �˻縦 ���ϰ� �ε巴�� �̵��� ** ���⼭ �극��ũ�Ȱɸ� ������
		}
	}
	//================================================================= �ٴڰ� �ȼ��浹���� �ƴҶ��� ó��
	if (!_isBCollision)
	{
		_gravity = GRAVITY;											//�߷°� ����
		_y += _gravity * TIMEMANAGER->getElpasedTime();				//�߷°� ��ŭ ��������.
	}
	*/
	//================================================================= ����ó��
	if (_state == PLAYER_JUMP_RIGHT || _state == PLAYER_JUMP_LEFT ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
	{
		return;
	}
	//================================================================= �ȼ��浹
	_isBCollision = false;
	for (int i = _proveBottom - 5; i < _proveBottom + 10; ++i)
	{
		for (int j = _x - 1; j < _x + 2; ++j)
		{
			COLORREF color = GetPixel(_pixelData->getMemDC(), j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);
			//========================================================= �������� �浹�κ�
			if (r == 255 && g == 0 && b == 255)
			{
				_y = i - (_size.y / 2);					//�÷��̾��� y���� �������ְ�
				_isBCollision = true;					//�ٴڰ� �浹�ϰ������� Ȯ����
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
				break;									//���̻� x���� �˻縦 ���Ѵ�.
			}
		}
		//�浹�߿� �ִٸ�
		if (_isBCollision)
		{
			break;										//���̻� y���� �˻縦 ���ϰ� �ε巴�� �̵��� ** ���⼭ �극��ũ�Ȱɸ� ������
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

		//========================================================== �������� �浹ó�� �κ�
		if ((r == 0 && g == 255 && b == 255))
		{

			_x = i - (_size.x / 2);						//�÷��̾� x �� ����
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

		//========================================================== �������� �浹ó�� �κ�
		if ((r == 0 && g == 255 && b == 255))
		{
			_x = i + (_size.x / 2);						//�÷��̾� x �� ����
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
			//========================================================= �������� �浹�κ�
			if (r == 255 && g == 0 && b == 0)
			{
				_y = i - (_size.y / 2);					//�÷��̾��� y���� �������ְ�
				_isFCollision = true;					//�ҹٴ��̶� �浹�ϰ������� Ȯ���ϱ� 
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

				break;									//���̻� x���� �˻縦 ���Ѵ�.
			}
		}
	}

}

void player_Eric::ericInit()
{
	playerBase::init();

	//�÷��̾� �⺻ ���� �ʱ�ȭ
	_size = { 64, 64 };		//�÷��̾� ������
	_x = 150;				//�÷��̾� x��ǥ
	_y = 1375;				//�÷��̾� y��ǥ

	_speed = MIN_SPEED;		//�÷��̾� �⺻ ���ǵ�
	_jumpPower = 0;				//�÷��̾� �����Ŀ�
	_gravity = 0;				//�÷��̾� �߷�
	_isAlive = true;				//�÷��̾� ����ִ��� üũ�� �Ұ� 
	_lifeCount = 3;				//�÷��̾� ������ �ִ� 3
	_playerRect = RectMakeCenter(_x, _y, _size.x, _size.y);

	//�浹ó���� �ʱ�ȭ 
	_proveBottom = _playerRect.bottom;
	_proveRight = _playerRect.right;
	_proveLeft = _playerRect.left;
	_proveTop = _playerRect.top;

	//�ȼ��浹üũ �Ұ� �ʱ�ȭ
	_isRCollision = false;		//������ ��
	_isLCollision = false;		//���� ��
	_isBCollision = false;		//�ٴ�
	_isFCollision = false;		//�״¹ٴ�

	//�̵����� �Ұ� �ʱ�ȭ

	_isJump = false;
	_isFall = false;
	_isRightMove = false;
	_isLeftMove = false;
	_isUpMove = false;
	_isDownMove = false;

	//��ٸ�Ÿ��� �Ұ�

	_isladderup = false;
	_isladderdown = false;
	_isUsladder = false;
	_isUeladder = false;
	_isDsladder = false;
	_isDeladder = false;
	_isladderUse = false;

	//��ų��� �Ұ�

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
	//=================================================== ���� �� ��ǥ ����
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		//���࿡ ĳ������ ���°� �Ʒ��� ������
		if (_state == PLAYER_IDLE_LEFT || _state == PLAYER_IDLE_RIGHT ||
			_state == PLAYER_MOVE_LEFT || _state == PLAYER_MOVE_RIGHT ||
			_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT ||
			_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
		{
			for (int i = 0; i < _ladderRc.size(); ++i)
			{
				//���࿡ ��ٸ���Ʈ�� ĳ���� ��Ʈ�� �ε�������
				if (IntersectRect(&temp, _ladderRc[i], &_playerRect))
				{
					// �÷��̾ ��ٸ��� �ö󰡰� ���� �ʴٸ�
					if (!_isladderup)
					{
						//���� �̵��ϹǷ� ���� �̵��ϴ� �Ұ� true ����
						_isUpMove = true;
						//���°�� ��ٸ����� üũ�ϱ����� �ε��� ����
						_ladderIndex = i;
						//ĳ������ x ��ǥ�� ��ٸ��� x��ǥ�� ���߾��ش�.
						float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;
						_x = ladderX;
						//ĳ������ ���¸� ��ٸ� Ÿ�������� �����ϸ鼭 ��ٸ��� �Ŵ޸��� �ִϸ��̼��� ���������
						_state = PLAYER_LADDER_UP;
						EricAniStart("ladder_up");
						//ĳ���ʹ� ��ٸ��� �Ŵ޷� �ְ�, �ö󰡰� �����Ƿ� üũ�� �Ұ��� ����
						_isladderUse = true;
						_isladderup = true;
						//��ٸ��� �Ŵ޸��� ���������ִ����� �ƴϹǷ�
						_isFall = false;
					}
				}
			}
		}
	}
	//=================================================== ���� ������ ����
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//���࿡ ��ٸ��� ĳ���Ͱ� �Ŵ޷��ְ�, ���� �ö󰡴� ���̶��
		if (_isladderUse && _isladderup)
		{
			_y -= _speed;
			//���࿡ ��ٸ��� �ε����� 0���� ũ�ų� ����, �ִ� �������ٴ� ������
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//���࿡ ��ٸ��� ���� ������ ĳ������ �ϴܰ��� ���ų� �۴ٸ�
				if (_ladderRc[_ladderIndex]->top >= _playerRect.bottom)
				{
					//ĳ������ ���´� ��ٸ� ���� �ǰ�, ��ٸ� �� üũ �Ұ��� true�� �ٲ��ش�.
					_state = PLAYER_LADDER_END;
					_isUeladder = true;
					EricAniStart("ladder_end");
				}
			}
		}
	}
	//=================================================== ����
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		//Ű�� ���� �ö󰡰����� �����Ƿ� ������ falseó���Ѵ�.
		_isUpMove = false;
		_isladderup = false;
		_state = PLAYER_LADDER_UP;
		KEYANIMANAGER->pause("player_eric", "ladder_up");
	}
	//=================================================== ����ó��
	if (_state == PLAYER_LADDER_END)
	{
		if (_EricMotion->isPlay() == false)
		{
			_state = PLAYER_IDLE_RIGHT;
			EricAniStart("idleright");
		}
		//ĳ������ ���°� ��ٸ����� ���������� ��ٸ��� �Ŵ޷� �ִ°͵� �ƴϰ�, �ö����� �ʰ� ������ üũ������ false�� ����
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

		//========================================================== ����ó��
		if (_isladderUse && _isladderup)
		{
			//���࿡ ��ٸ��� �ε����� 0���� ũ�ų� ����, �ִ� �������ٴ� ������
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//���࿡ ��ٸ��� ���� ������ ĳ������ �ϴܰ��� ���ų� �۴ٸ�
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

		//========================================================== ����ó��
		if (_isladderUse && _isladderdown)
		{
			//���࿡ ��ٸ��� �ε����� 0���� ũ�ų� ����, �ִ� �������ٴ� ������
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//���࿡ ��ٸ��� ���� ������ ĳ������ �ϴܰ��� ���ų� �۴ٸ�
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
	//�̹��� �߰�
	_player = IMAGEMANAGER->addFrameImage("player_eric", "image/eric.bmp", 704, 1024, 11, 16, true, RGB(255, 0, 255));
	//�ִϸ��̼� Ÿ���߰�
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

	//�⺻ �ִϸ��̼� ����
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
