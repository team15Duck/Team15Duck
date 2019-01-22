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
	//�ٽ� ������ ���� �; ���� Ű ���߿� �����!!
	if (KEYMANAGER->isOnceKeyDown('R'))
	{
		_isAlive = true;
		_deathMotion = false;
	}
	//==================== ���࿡ �׾��� �״� ����� �������� ���̻��� Ű �Է��� ����!!!!! ====================
	if (!_isAlive && !_deathMotion)
		return;
	//==================== ���࿡ �׾��µ� �״� ����� ���;� �ϸ� �Ʒ� ���๮��� Ű �ִ� �����ض�(���⼭ ����� false�� �ٲ��� ====================
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

	//==================== ����ִٸ� Ű �Է��� �޾ƺ���!! ====================
	collisionLadder(_ladderRc);
	//============== <<�� ��>> ================
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))			//���� �������� ó�� �����ϸ� _state�� _playerAni�� ���� �ٲ� �ֱ� ���ؼ� �־����ϴ�.
	{
		_isRight = false;
		//�ϴ� ���� �ӵ��� �����սô�
		_speed = _minSpeed;
		//���ʺ� �ε������� üũ����
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
			_fallStartY = _y;				//�������� �����Ҷ��� ���̸� ������ ����
			_isLadder = false;
		}

		pixelBottomCollision();
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//�������� ������(����)
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
		//�����̸鼭 �ٴ� üũ�ϰ�
		pixelBottomCollision();
		//����Ű�� ������ ���߿� ������ ������
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
		//�������� �����̴ٰ� image ������ �������� �ϸ� speed ���� 0���� ��
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
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))			//���� �����ӿ��� ���� ����
	{
		if ((_state == PLAYER_ATTACK_LEFT || _state == PLAYER_ARROW_LEFT )&& _playerAni->isPlay())
		{
			return;
		}
		_speed = 0.f;								//���ǵ� ���� �ٽ� ��(���� �ε��� ��� speed���� 0���� �ξ��� ������ �ǵ����ִ� �ڵ���)
		_state = PLAYER_IDLE_LEFT;					//���°��� idle
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
	//============== <�� �� ��> ================
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))		//������ �������� ó�� �����ϸ� _state�� _playerAni�� ���� �ٲ��ֱ� ���ؼ� �־����ϴ�.
	{
		_isRight = true;
		//���Ǵ� �����ӵ��� �����մϴ�
		_speed = _minSpeed;
		//������ �� �浹 üũ
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
			_fallStartY = _y;				//�������� �����Ҷ��� ���̸� ������ ����
			_isLadder = false;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//���������� ������ ����
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
		//�ӵ��� ���ӵ��� �־�ھƾ�
		_speed += _acceleration * TIMEMANAGER->getElpasedTime();
		if (_speed >= _maxSpeed)
		{
			_speed = _maxSpeed;
		}
		//�����̸鼭 �ٴ� üũ�ϰ�
		pixelBottomCollision();
		//�����̴ٰ� ������ ������
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
		//���������� �����̴ٰ� image ������ �������� �ϸ� speed ���� 0���� ��
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
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))			//������ �����ӿ��� ���� ����
	{
		if ((_state == PLAYER_ATTACK_RIGHT || _state == PLAYER_ARROW_RIGHT) && _playerAni->isPlay())
		{
			return;
		}
		_speed = 0.f;								//���ǵ尪�� �ٽ� ��(���� �ε��� ��� speed ���� 0���� �ٲپ��� ������ �ǵ��� �����)
		_state = PLAYER_IDLE_RIGHT;					//���°��� idle
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
	
	//����Ű �Լ�
	attackKey();

	if (_state == PLAYER_FALL_LEFT  || _state == PLAYER_FALL_RIGHT)
	{
		_y += _gravity * TIMEMANAGER->getElpasedTime();
		_curFallingY = _y;				//���� ������������ �� ���� ����
		if (_curFallingY - _fallStartY >= _damageHeight)
		{
			//�������� �κ� ������ �ִϸ��̼� ������ �ϱ�
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
	//�Ϲ� ����
	//0 Ȥ�� 1 �߿��� ���� Ȯ���� 0�� ���� ���� �߱�, 1�� ���� ���� �߱�
}

void player_Baleog::keyPressD()
{
	//Ȱ���
}

void player_Baleog::initBaleog()
{
	//_x = 1500;
	_x = WINSIZEX / 2 + 100;
	_y = 1370;
	_speed = 0.f;
	
	_acceleration = 3.5f;		//���ӵ�
	_minSpeed = 1.f;			//�����ӵ�
	_maxSpeed = 4.5f;			//�ְ�ӵ�

	_damageHeight = 315.f;
	_gravity = GRAVITY;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//pixel �浹 Ž���� ����
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	_isGround = false;			//�ٴڿ� �پ��ּ�?
	_isLadder = false;			//��ٸ� ����?
	_isLadderTop = false;		//��ٸ��� ������?
	_isChangeAni = false;		//�ִϸ��̼� �ٲ�ߴ�??
	_isPushWall = false;		//�� �а� �־�?
	_deathMotion = false;		//�״� ����� ���;ߴ�?
	_isRight = true;


	_ladderIndex = 0;
	keyAniSetting();

	
}


void player_Baleog::pixelLeftWallCollision()
{
	//���� �� �浹(�ȼ��浹)
	for (int i = _proveLeft + 5; i > _proveLeft; --i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_LEFT;			//���°��� ���� �̴� ����(����)�� ��
			_speed = 0.f;							//������ ���̻� ��������
			
			_isPushWall = true;
			break;
		}
	}
}

void player_Baleog::pixelRightWallCollision()
{
	//������ �� �浹(�ȼ��浹)
	for (int i = _playerRect.right - 5; i < _playerRect.right; ++i)
	{
		COLORREF color = GetPixel(_pixelData->getMemDC(), i, _y);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 0 && g == 255 && b == 255)
		{
			_state = PLAYER_PUSH_WALL_RIGHT;		//���°��� ���� �̴� ����(������)�� ��
			_speed = 0.f;

			_isPushWall = true;
			break;
		}
	}
}


void player_Baleog::pixelBottomCollision()
{
	//�ٴ��浹ó��(�ȼ��浹)
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
		else if (r != 255 && g != 0 && b != 255)				//ĳ���Ͱ� �ٴ� �κп� ������
		{
			_isGround = false;
		}
	}

	//��������
	if (_state == PLAYER_FALL_LEFT || _state == PLAYER_FALL_RIGHT)
	{
		
		if (_curFallingY - _fallStartY >= _damageHeight)		//�������� �������� ���� ���̸�
		{
			_lifeCount -= 1;			//������ ����
			if (_lifeCount == 0)
			{
				_isAlive = false;		//����� ������
				//�ִ� : 
			}

			//�ִ� :
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
		//else if (_curFallingY - _fallStartY < _damageHeight)	//�������� ������ ���� ���̸�
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
		//�ٴڿ� �� �浹�� �׾��� ǥ�ñ��� �߰� ���߰� �Ұ�
		COLORREF color = GetPixel(_pixelData->getMemDC(), _x, i);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);
		if(r == 255 && g==0 && b == 0)
		{
			//�ҿ� �������� ���⿡ ���� �״� ����� ������ �޶� ���ǹ� �޾���
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
	//�μ����� ���� rect�ε� �� ���̶� �ε��� ���
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
	//�̹��� �߰�
	_imageKey = "baleog";
	_aniImageKey = "player_Baleog";
	_player = IMAGEMANAGER->addFrameImage(_imageKey, "image/baleog.bmp", 630, 1260, 9, 18, true, RGB(255, 0, 255));

	//Ű �̸��� ĳ���͸� ������(��)
	KEYANIMANAGER->addAnimationType(_aniImageKey);
	/*
	//����
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

	int fallRight[] = { 63, 64 };		//���� ������ �������� ��
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallRight", _imageKey, fallRight, 2, 8, true);

	int fallLeft[] = { 72, 73 };		//���� ������ �������� ��
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallLeft", _imageKey, fallLeft, 2, 8, true);

	int highFallRight[] = { 65 };		//���� ������ �������� ��
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallRight", _imageKey, highFallRight, 1, 6, true);

	int highFallLeft[] = { 74 };		//���� ������ �������� ��
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallLeft", _imageKey, highFallLeft, 1, 6, true);

	int highFallEndRight[] = { 66, 67, 68, 69, 70 };				//���� ������ �������鼭 rect�� bottom�� �ٴڿ� ���� ��쿡 �� �ִϸ��̼� �߰�(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndRight", _imageKey, highFallEndRight, 5, 6, false);

	int highFallEndLeft[] = { 75, 76, 77, 78, 79 };					//���� ������ �������鼭 rect�� bottom�� �ٴڿ� ���� ��쿡 �� �ִϸ��̼� �߰�(����)
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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderEnd", _imageKey, ladderEnd, 2, 7, false);				//���� �� �κ� ������ �Ȱɾ �� �������� Ȯ�� ���ؿ� (��ٸ� �� ó���ϰ� ���� Ȯ���ҰԿ�)

	int hitRight[] = { 123 };												//���Ϳ��� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitRight", _imageKey, hitRight, 1, 3, false);

	int hitLeft[] = { 132 };												//���Ϳ��� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitLeft", _imageKey, hitLeft, 1, 3, false);

	int hitDeathRight[] = { 117, 118, 119, 120, 121, 122 };					//���Ϳ��� �°� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathRight", _imageKey, hitDeathRight, 6, 3, false);

	int hitDeathLeft[] = { 126, 127, 128, 129, 130, 131 };					//���Ϳ��� �°� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathLeft", _imageKey, hitDeathLeft, 6, 3, false);

	int fallDeathRight[] = { 135, 136, 137, 138, 139 };						//�������ٰ� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathRight", _imageKey, fallDeathRight, 5, 3, false);

	int fallDeathLeft[] = { 140, 141, 142, 143, 144 };						//�������ٰ� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathLeft", _imageKey, fallDeathLeft, 5, 3, false);

	int fireDeathRight[] = { 145, 146, 147, 148, 149, 150, 151, 152 };		//��Ÿ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathRight", _imageKey, fireDeathRight, 8, 6, false);

	int fireDeathLeft[] = { 153, 154, 155, 156, 157, 158, 159, 160 };		//��Ÿ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathLeft", _imageKey, fireDeathLeft, 8, 6, false);

	int lookFrontRight[] = { 2 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontRight", _imageKey, lookFrontRight, 1, 6, true);

	int lookFrontLeft[] = { 5 };
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "lookFrontLeft", _imageKey, lookFrontLeft, 1, 6, true);

	int attackLengthRight[] = { 81, 82, 83, 84 };							//���� ����(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthRight", _imageKey, attackLengthRight, 4, 6, false);

	int attackLengthLeft[] = { 85, 86, 87, 88 };							//���� ����(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackLengthLeft", _imageKey, attackLengthLeft, 4, 6, false);

	int attackWidthRight[] = { 90, 91, 92, 93 };							//���� ����(������)	
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthRight", _imageKey, attackWidthRight, 4, 6, false);

	int attackWidthLeft[] = { 94, 95, 96, 97 };								//���� ����(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "attackWidthLeft", _imageKey, attackWidthLeft, 4, 6, false);

	int arrowRight[] = { 99, 100, 101, 102, 103, 104, 105, 106 };			//Ȱ ����(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowRight", _imageKey, arrowRight, 8, 10, false);

	int arrowLeft[] = { 108, 109, 110, 111, 112, 113, 114, 115 };			//Ȱ ����(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "arrowLeft", _imageKey, arrowLeft, 8, 10, false);

	//_state = PLAYER_IDLE_RIGHT;
	_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
	_playerAni->start();
}


void player_Baleog::collisionLadder(vector<RECT*> ladder)
{
	RECT tempColLadder;
	int ladderVSize = ladder.size();
	//============== �� �� ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		for (int i = 0; i < ladderVSize; ++i)
		{
			if (IntersectRect(&tempColLadder, ladder[i], &_playerRect))		//�÷��̾�� ��ٸ��� ��Ʈ�� �浹���� �� 
			{
				_isLadder = true;			//��ٸ��� Ÿ�� �־
				_ladderIndex = i;

				_speed = 2.0f;				//_y �� ���ǵ尡 ����

				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");		
				_playerAni->start();		//�ö󰡴� ����� ����غ��ƿ�
			}
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))	//Ű�� ��� �������ְ�
	{
		if (_isLadder)						//��ٸ��� Ÿ���ִٸ�
		{
			if (_playerRect.bottom <= (*ladder[_ladderIndex]).top)		//�÷��̾��� ���� ��ٸ��� ���κп� ������
			{
				_speed = 0;									//���̻� y�� �̵��� ���� ������
				if (!_isLadderTop)							//������ bool _isLadderTop�� false�� �� ���ǿ� ���Ϳ�
				{	
					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderEnd");		//��ٸ� ���κп����� ����� 
					_playerAni->start();					//����ϼ���
					_isLadderTop = true;
					_isLadder = false;						//�׶� ���̻� ��ٸ� ���� �ִ°� �ƴϴϱ�  _isLadder = false �� �ٲ��ּ���
				}
				pixelBottomCollision();

			}
			_y -= _speed;					//y�� �̵��� ��� �ϼ���
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

	//============== �� �� �� ===============
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		for (int i = 0; i < ladderVSize; ++i)
		{
			if (IntersectRect(&tempColLadder, ladder[i], &_playerRect))		//�÷��̾�� ��ٸ��� ��Ʈ�� �浹���� �� 
			{
				_ladderIndex = i;
				if (!_isLadderTop && !_isLadder)
				{
					_speed = 2.0f;				//_y �� ���ǵ尡 ����
					_isLadder = true;			//��ٸ��� Ÿ�� �־

					_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderDown");
					_playerAni->start();		//�������� ����� ����غ��ƿ�
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
		if (_isLadder)						//��ٸ��� Ÿ���ִٸ�
		{
			_speed = 2.0f;
			
			if (_playerRect.bottom >= (*ladder[_ladderIndex]).bottom)		//�÷��̾��� ���� ��ٸ��� �Ʒ��κп� ������
			{
				_speed = 0;									//���̻� y�� �̵��� ���� ������
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
		
			_y += _speed;					//y�� �̵��� ��� �ϼ���
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
	//========================== <�� �� Ű> ===========================
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		//============ ���������� �����ϸ� ==============
		if (_state == PLAYER_MOVE_RIGHT || _state == PLAYER_IDLE_RIGHT)
		{
			_state = PLAYER_ATTACK_RIGHT;
			if (RND->getInt(2) == 0)				//������ ���� ����
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
		//============= �������� �����ϸ� ===============
		if (_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_state = PLAYER_ATTACK_LEFT;
			if (RND->getInt(2) == 0)				//���� ���� ����
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackLengthLeft");
				_playerAni->start(); 
				_isChangeAni = false;
			}
			else if (RND->getInt(2) == 1)			//���� ���� ����
			{
				_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "attackWidthLeft");
				_playerAni->start();
				_isChangeAni = false;
			}
		}
	}
	
	//====================<Ȱ �� ��>=======================
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
			//�ҷ��� �������� rect.right
		}
		if(_state == PLAYER_MOVE_LEFT || _state == PLAYER_IDLE_LEFT)
		{
			_isAttackRight = false;
			_isFire = true;
			_state = PLAYER_ARROW_LEFT;
			_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "arrowLeft");
			_playerAni->start();
			_isChangeAni = false;
			//�ҷ��� �������� rect.left
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
