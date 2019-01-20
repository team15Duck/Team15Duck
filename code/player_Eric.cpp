#include "stdafx.h"
#include "player_Eric.h"
#include "objectManager.h"


player_Eric::player_Eric()
{
}


player_Eric::~player_Eric()
{
}


HRESULT player_Eric::init()
{
	//�÷��̾� �⺻ ���� �ʱ�ȭ
	_size = { 64, 64 };		//�÷��̾� ������
	_x = 450;				//�÷��̾� x��ǥ
	_y = 1350;				//�÷��̾� y��ǥ

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
	_isRightMove = false;
	_isLeftMove = false;

	//��ٸ�Ÿ��� �Ұ�

	_isLadder = false;		//��ٸ� Ÿ���ִ��� Ȯ�ο� �Ұ�
	_isladderchk = false;		//��ٸ� ������Ʈ Ȯ�ο� �Ұ�
	_isladderup = false;		//��ٸ� Ÿ�� �ö󰡴��� Ȯ�ο� �Ұ�
	_isladderdown = false;		//��ٸ� Ÿ�� ���������� Ȯ�ο� �Ұ� 
	_isLadderTop = false;		//��ٸ� ������ �ִ��� Ȯ�ο� �Ұ�

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

		//��ٸ�����
		/*if (_ladder != nullptr)
		{
			RECT temp;
			if (IntersectRect(&temp, &_ladder->getObjectRect(), &_playerRect))
			{

			}
			else
			{
				_isladderchk = false;
			}
		}*/

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
		Rectangle(CAMERA->getMemDC(), _playerRect, false);
		_player->aniRender(CAMERA->getMemDC(), _playerRect.left, _playerRect.top, _EricMotion);
	}
	//�ӵ� �׽�Ʈ�� ��� 
	//char str[256];
	//SetTextColor(CAMERA->getMemDC(), RGB(255, 255, 255));
	//sprintf_s(str, "speed : %.1f", _speed);
	//TextOut(CAMERA->getMemDC(), 0, 200, str, strlen(str));
	//sprintf_s(str, "state : %d", _state);
	//TextOut(CAMERA->getMemDC(), 0, 250, str, strlen(str));
}

void player_Eric::keyPressMove()
{
	rightMove();
	leftMove();
}

void player_Eric::keyPressSpace()
{
	//================================================================ ���� ����ó�� 
	if (!(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT ||
		_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT || _isFCollision))
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

		_isJump = true;												//���� �������� Ȯ��
		_jumpPower = START_JUMPP;										//���� �Ŀ��� ��ŸƮ �Ŀ� ����
		_gravity = GRAVITY * TIMEMANAGER->getElpasedTime();			//���ϸ� ���� �߷� ���� 
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
	if (_state == PLAYER_JUMP_RIGHT || _state == PLAYER_JUMP_LEFT)
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
				_y = i - (_size.y / 2);	//�÷��̾��� y���� �������ְ�
				_isBCollision = true;					//�ٴڰ� �浹�ϰ������� Ȯ����
				_isJump = false;				//������ �����ϵ��� ���������� false�� ����

				if (_state == PLAYER_FALL_RIGHT)
				{
					_state = PLAYER_IDLE_RIGHT;
				}
				else if (_state == PLAYER_FALL_LEFT)
				{
					_state = PLAYER_IDLE_LEFT;
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

void player_Eric::playerCollisionLadder(object* ladder)
{
	if (!ladder)
	{
		return;
	}
	_ladder = ladder;
	_isladderchk = true;
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
				_isFCollision = true;					//�ٴڰ� �浹�ϰ������� Ȯ����
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
	//================================================ �⺻�ӵ� �� �̵� ����
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_isLeftMove = true;					//�������� �̵��Ѵ�.
		_speed = MIN_SPEED;					//���ǵ�� �̴ϸ� ���ǵ�� ����
		_state = PLAYER_MOVE_LEFT;			//���´� ���� �̵��ϴ� �ִϸ��̼� ���
		EricAniStart("move_left");
	}
	//================================================ ���� ������ ����
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		//============================================	�ӵ� �� ���ӵ� ó��
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
		//============================================ �ʳ� �̵� ���� ó��
		//���࿡ ĳ���Ͱ� �� ũ���� ������ �Ѿ�� ���ϵ��� ó�� 
		if (_x - (_size.x / 2) < 0)
		{
			_x = 0 + (_size.x / 2);
		}
		//============================================ �� �ȼ��浹 ó��
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
		_isLeftMove = false;				//�������� �̵�����.
		_speed = MIN_SPEED;			//���ǵ�� �̴ϸ� ���ǵ�� ����
		_state = PLAYER_IDLE_LEFT;		//���´� ������ �ٶ󺸴� �ִϸ��̼� ���
	}
}

void player_Eric::rightMove()
{
	//================================================ �⺻�ӵ� �� �̵� ����
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_isRightMove = true;					//���������� �̵��Ѵ�.
		_speed = MIN_SPEED;			//���ǵ�� �̴ϸ� ���ǵ�� ����
		_state = PLAYER_MOVE_RIGHT;	//���´� ������ �̵��ϴ� �ִϸ��̼� ���
		EricAniStart("move_right");
	}
	//================================================ ���� ������ ����
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		//============================================	�ӵ� �� ���ӵ� ó��
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
		_state = PLAYER_IDLE_RIGHT;	//���´� ������ �ٶ󺸴� �ִϸ��̼� ���
	}
}

void player_Eric::upMove(object * ladder)
{
	/*
	if (_isladderchk)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_UP))
		{
			_x = ladder->getX();
		}
		if (KEYMANAGER->isStayKeyDown(VK_UP))
		{
			_speed = MIN_SPEED;

			_y -= _speed;
		}
	}
	else
	{

	}
	*/
	//���࿡ ����Ű�� ������ ���� �̵��ض�
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_y -= _speed;
	}
}

void player_Eric::downMove(object * ladder)
{
	/*
	if (_isladderchk)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
		{
			_x = ladder->getX();
		}
		if (KEYMANAGER->isStayKeyDown(VK_DOWN))
		{
			_speed = MIN_SPEED;
			_y += _speed;
		}
	}
	*/
	//���࿡ �Ʒ���Ű�� ������ �Ʒ��� �̵���
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_y += _speed;
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
