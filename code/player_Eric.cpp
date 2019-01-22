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

	//�÷��̾� �⺻ ���� �ʱ�ȭ
	_size = { 64, 64 };		//�÷��̾� ������
	_x = 450;				//�÷��̾� x��ǥ
	_y = 1320;				//�÷��̾� y��ǥ

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

	//�ִϸ��̼� �ʱ�ȭ
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

		//�ִϸ��̼�
		EricAni();

		//�÷��̾� ��Ʈ ����
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
	//�ӵ� �׽�Ʈ�� ��� 
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
	//================================================================ ���� ����ó�� 
	if (!(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT ||
		_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT || _isFCollision ||
		_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN))
	{
		return;
	}
	//================================================================ ���� ����
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//���߿� �÷��̾ ������ ���ų� �������� �̵��ϰ� �ִٸ�
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_state = PLAYER_JUMP_LEFT;
			EricAniStart("jump_left");
		}
		//���࿡ �÷��̾ �������� ���ų� ���������� �̵��ϰ��ִٸ�
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
		}
		//���࿡ �÷��̾ ��ٸ��� �ö󰡰��ְų� ���������ִٸ�
		if (_state == PLAYER_LADDER_UP || _state == PLAYER_LADDER_DOWN)
		{
			_state = PLAYER_JUMP_RIGHT;
			EricAniStart("jump_right");
		}

		_isJump = true;												//���� �������� Ȯ��
		_jumpPower = START_JUMPP;									//���� �Ŀ��� ��ŸƮ �Ŀ� ����
		_gravity = GRAVITY * TIMEMANAGER->getElpasedTime();			//���ϸ� ���� �߷� ���� 

		//=========================================================== ����ó��?
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
	//Ư�� ��ų�� �ߵ��Ǵ� ���� >> ĳ������ �ӵ��� �ƽ� ���ǵ��϶�
	if (_speed == MAX_SPEED)
	{
		//���࿡ D Ű�� �����ٸ�
		if (KEYMANAGER->isOnceKeyDown('D'))
		{
			if (!(_state == PLAYER_MOVE_RIGHT || _state == PLAYER_MOVE_LEFT))
			{
				return;
			}
			// ���������� �̵��ϴ� ���¶��
			if (_state == PLAYER_MOVE_RIGHT)
			{
				//���¸� ������ ��ġ��� �ٲ��ְ� �ִϸ��̼� ���
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

void player_Eric::leftMove()
{
	//���࿡ ��ٸ� �ö󰡰��ִٸ� �����̵� �Ұ���
	if ((_isladderup && _isUpMove) || (_isladderdown && _isDownMove))
	{
		return;
	}
	if (!_isRightMove && !_isUpMove && !_isDownMove)
	{
		//================================================ �⺻�ӵ� �� �̵� ����
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			if (_isBCollision)						//ĳ���Ͱ� �ٴ� �ȼ��浹���̶�� 
			{
				_isLeftMove = true;					//�������� �̵��Ѵ�.
				_speed = MIN_SPEED;					//���ǵ�� �̴ϸ� ���ǵ�� ����
				_state = PLAYER_MOVE_LEFT;			//���´� �������� �̵������� ����
				EricAniStart("move_left");			//�ִϸ��̼��� �������� �̵��ϴ� �ִϸ��̼�

				//======================================= ����ó����
				_isFall = false;		//�������� ���� �����Ƿ�
				_isladderUse = false;	//��ٸ� ������� �ƴϹǷ�
			}
			//���࿡ ĳ���Ͱ� ��ٸ��� �Ŵ޷������� ����Ű�� ������ 
			if (_isladderUse)
			{
				_state = PLAYER_FALL_LEFT;
			}
		}
		//================================================ ���� ������ ����
		if (KEYMANAGER->isStayKeyDown(VK_LEFT))
		{
			//���࿡ �ٴ� �浹�߿� 
			if (_isBCollision)
			{
				//���ǵ尡 �ƽ� ���ǵ庸�� �۴ٸ�
				if (_speed < MAX_SPEED)
				{
					//�ӵ��� ���ӵ� * �ð����� ��� ���ؼ� ����Ѵ�.
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
				//�ӵ��� �ƽ� ���ǵ庸�� ū ���¶��
				else
				{
					//���ǵ带 �ƽ����ǵ�� �����Ѵ�.
					_speed = MAX_SPEED;

					if (_isladderUse || _isladderup)
					{
						_speed = MIN_SPEED;
					}
				}
				//���࿡ �������� ��ġ���ϴ� ���¶��
				if (_state == PLAYER_HEAD_BUTT_LEFT)
				{
					if (_EricMotion->isPlay() == false)
					{
						EricAniStart("move_left");
					}
				}
			}
			//============================================ �ʳ� �̵� ���� ó��
			//���࿡ ĳ���Ͱ� �� ũ���� ������ �Ѿ�� ���ϵ��� ó�� 
			if (_x - (_size.x / 2) < 0)
			{
				_x = 0 + (_size.x / 2);
			}
			//============================================ �� �ȼ��浹 ó��
			//���࿡ ��ٸ��� ��������ʰ� �ö����� �ʰ� �ִٸ� 
			//���࿡ ���� ���� �ȼ��浹�� ���� �ʰ� �ִٸ�
			if (!_isLCollision)
			{
				_x -= _speed * TIMEMANAGER->getElpasedTime();

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
						_isLCollision = false;						//�װԾƴ϶�� �浹���ߴ�
					}
				}
			}

		}
		//================================================ �⺻�ӵ� �� �̵� ����
		if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
		{
			_isLeftMove = false;						//�������� �̵�����.
			_speed = MIN_SPEED;							//���ǵ�� �̴ϸ� ���ǵ�� ����
			if (_state == PLAYER_HEAD_BUTT_LEFT)
			{
				_state = PLAYER_SIGN_LEFT;
				EricAniStart("sign_left");
				_aniCount += 1;
			}
			else
			{
				_state = PLAYER_IDLE_LEFT;				//���´� ���� �ٶ󺸴� �ִϸ��̼� ���
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
	//���࿡ ��ٸ�Ÿ�� ���� �ö󰡰��ִٸ�������̵� �Ұ��� 
	if ((_isladderup && _isUpMove) || (_isladderdown && _isDownMove))
	{
		return;
	}
	if (!_isLeftMove)
	{
		//================================================ �⺻�ӵ� �� �̵� ����
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			//ĳ���Ͱ� �ٴ��̶� �浹�߿� 
			if (_isBCollision)
			{
				_isRightMove = true;				//���������� �̵��Ѵ�.
				_speed = MIN_SPEED;					//���ǵ�� �̴ϸ� ���ǵ�� ����
				_state = PLAYER_MOVE_RIGHT;			//���´� ������ �̵��ϴ� �ִϸ��̼� ���
				EricAniStart("move_right");
			}
			//���࿡ ĳ���Ͱ� ��ٸ��� �Ŵ޷������� ������Ű�� ������ 
			if (_isladderUse)
			{
				_isFall = true;
			}
		}
		//================================================ ���� ������ ����
		if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			//�ٴ��̶� �浹�ϸ鼭 �̵��߿� 
			if (_isBCollision && _isRightMove)
			{
				//���࿡ �ӵ��� �ƽ� ���ǵ庸�� ������
				if (_speed < MAX_SPEED)
				{
					//�ӵ��� ���ӵ� * �ð����� ��� ���ؼ� ����Ѵ�.
					_speed += ACC_SPEED * TIMEMANAGER->getElpasedTime();
				}
				//�ӵ��� �ƽ� ���ǵ庸�� ū ���¶��
				else
				{
					//���ǵ带 �ƽ����ǵ�� �����Ѵ�.
					_speed = MAX_SPEED;
				}
				//���࿡ ���°� ��ġ���ϴ� ���¶�� 
				if (_state == PLAYER_HEAD_BUTT_RIGHT)
				{
					if (_EricMotion->isPlay() == false)
					{
						EricAniStart("move_right");
					}
				}
			}
			//�Ǵ� ��ٸ��� �ö󰡰� �ִ� ���̶��
			if (_isUpMove)
			{
				_speed = 5;
				_x += _speed;
				_isFall = true;
			}
			//============================================ �ʳ� �̵� ���� ó��
			//���࿡ ĳ���Ͱ� �� ũ���� �������� �Ѿ�� ���ϵ��� ó�� 
			if (_x + (_size.x / 2) > _pixelData->GetWidth())
			{
				_x = _pixelData->GetWidth() - (_size.x / 2);
			}
			//============================================ �� �ȼ��浹 ó��
			//���࿡ ������ ���� �ȼ��浹�� ���� �ʰ� �ִٸ�
			if (!_isRCollision)
			{
				_x += _speed * TIMEMANAGER->getElpasedTime();

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
							_EricMotion = KEYANIMANAGER->findAnimation("player_eric", "push_wall_right");

							if (!_EricMotion->isPlay())
							{
								KEYANIMANAGER->start("player_eric", "push_wall_right");
							}
						}
						//���࿡ ���� �浹�ϰ� �̵����̰� ������ ��ų�� ����ߴٸ� 
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
		//================================================ �⺻�ӵ� �� �̵� ����
		if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
		{
			_isRightMove = false;				//���������� �̵�����.
			_speed = MIN_SPEED;			//���ǵ�� �̴ϸ� ���ǵ�� ����

			//���࿡ ��ġ�� �޸������̶��
			if (_state == PLAYER_HEAD_BUTT_RIGHT)
			{
				//���¸� �Ѽ����°ɷ� �ٲ��ְ� �ִϸ��̼� ����� �ִ�ī��Ʈ+1
				_state = PLAYER_SIGN_RIGHT;
				EricAniStart("sign_right");
				_aniCount += 1;
			}
			//���࿡ ���Ͽ� �ɸ� �����϶�
			else if (_state == PLAYER_STUN_RIGHT)
			{
				//�ʴ� �� �Ǵ�?
			}
			else
			{
				_state = PLAYER_IDLE_RIGHT;	//���´� ������ �ٶ󺸴� �ִϸ��̼� ���
			}
		}
		//================================================ ����ó��
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
}


void player_Eric::downMove(object * ladder)
{
	_ladder = ladder;
	RECT temp;
	if (_isRightMove || _isLeftMove)
	{
		return;
	}
	//=================================================== ���� �� ��ǥ ����
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
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
					// �÷��̾ ��ٸ��� �������� ���� �ʴٸ� 
					if (!_isladderdown)
					{
						//���°�� ��ٸ����� üũ�ϱ����� �ε��� ����
						_ladderIndex = i;
						//ĳ������ x ��ǥ�� ��ٸ��� x��ǥ�� ���߾��ش�.
						float ladderX = _ladderRc[i]->left + (_ladderRc[i]->right - _ladderRc[i]->left) / 2;
						_x = ladderX;
						//ĳ������ ���¸� ��ٸ� Ÿ�������� �����ϸ鼭 ��ٸ��� �Ŵ޸��� �ִϸ��̼��� ���������
						_state = PLAYER_LADDER_DOWN;
						EricAniStart("ladder_down");
						//ĳ���ʹ� ��ٸ��� �Ŵ޷� �ְ�, �ö󰡰� �����Ƿ� üũ�� �Ұ��� ����
						_isladderUse = true;
						_isladderdown = true;
						_isDownMove = true;
						//��ٸ��� �Ŵ޷������� ������������ �ƴϹǷ�
						_isFall = false;
					}
				}
			}
		}
	}
	//=================================================== ���� ������ ����
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		//���࿡ ��ٸ��� ĳ���Ͱ� �Ŵ޷��ְ�, ���� �ö󰡴� ���̶��
		if (_isladderUse && _isladderdown)
		{
			_y += _speed;
			//���࿡ ��ٸ��� �ε����� 0���� ũ�ų� ����, �ִ� �������ٴ� ������
			if (0 <= _ladderIndex && _ladderIndex < _ladderRc.size())
			{
				//���࿡ ��ٸ��� ���� ������ ĳ������ �ϴܰ��� ���ų� ũ�ٸ�
				if (_ladderRc[_ladderIndex]->bottom <= _playerRect.bottom)
				{
					//ĳ������ ���´� ��ٸ� ���� �ǰ�, ��ٸ� �� üũ �Ұ��� true�� �ٲ��ش�.
					_state = PLAYER_IDLE_RIGHT;
					_isDeladder = true;
					EricAniStart("idleright");
				}
			}
		}
	}
	//=================================================== ����
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		//Ű�� ���� �ö󰡰����� �����Ƿ� ������ falseó���Ѵ�.
		_isladderdown = false;
		KEYANIMANAGER->pause("player_eric", "ladder_down");
	}
	//=================================================== ����ó��
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
	//�̹��� �߰�
	_player = IMAGEMANAGER->addFrameImage("player_eric", "image/eric.bmp", 704, 1024, 11, 16, true, RGB(255, 0, 255));
	//�ִϸ��̼� Ÿ���߰�
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

	//�⺻ �ִϸ��̼� ����
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
