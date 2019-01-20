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
	//============== �� �� ================
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))			//���� �������� ó�� �����ϸ� _state�� _playerAni�� ���� �ٲ� �ֱ� ���ؼ� �־����ϴ�.
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
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))			//�������� ������(����)
	{
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
			if (!_isChangeAni && _speed == 0)
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
		_speed = 2.0f;								//���ǵ� ���� �ٽ� ��(���� �ε��� ��� speed���� 0���� �ξ��� ������ �ǵ����ִ� �ڵ���)
		_state = PLAYER_IDLE_LEFT;					//���°��� idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleLeft");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
	}
	//============== �� �� �� ================
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))		//������ �������� ó�� �����ϸ� _state�� _playerAni�� ���� �ٲ��ֱ� ���ؼ� �־����ϴ�.
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
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))		//���������� ������ ����
	{
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
		_speed = 2.0f;								//���ǵ尪�� �ٽ� ��(���� �ε��� ��� speed ���� 0���� �ٲپ��� ������ �ǵ��� �����)
		_state = PLAYER_IDLE_RIGHT;					//���°��� idle
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "normalIdleRight");
		_playerAni->start();
		_isChangeAni = false;
		_isPushWall = false;
	}

	//playerCollisionLadder();
	//============== �� �� ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = PLAYER_LADDER_UP;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//��ٸ��� �浹 �ƴ��� ���θ� üũ�� �ӽ� RECT
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

	//============== �� �� �� ===============
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
	//�Ϲ� ����
	//0 Ȥ�� 1 �߿��� ���� Ȯ���� 0�� ���� ���� �߱�, 1�� ���� ���� �߱�
}

void player_Baleog::keyPressD()
{
	//Ȱ���
}

void player_Baleog::initBaleog()
{
	_x = 1950;
	//_x = WINSIZEX / 2 - 200;
	_y = 1350;
	_speed = 2.f;
	_gravity = 0;

	_playerRect = RectMakeCenter(_x, _y, 50, 70);

	//pixel �浹 Ž���� ����
	_proveBottom = _playerRect.bottom;
	_proveLeft = _playerRect.left;
	_proveRight = _playerRect.right;

	//�ӽ� �浹 üũ�� Rect
	//_tempWall = RectMakeCenter(300, 1325, 50, 100);
	//_tempLadder = RectMakeCenter(192, 840, 50, 1130);

	_isLadder = false;			//��ٸ� ����?
	_isLadderTop = false;		//��ٸ��� ������?
	_isChangeAni = false;		//�ִϸ��̼� �ٲ�ߴ�??
	_isPushWall = false;		//�� �а� �־�?

	
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

void player_Baleog::rectBrokenWallCollision()
{
	//�μ����� ���� rect�ε� �� ���̶� �ε��� ���
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
	//�ٴ��浹ó��(�ȼ��浹)
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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleRight", _imageKey, specialIdleRight, 9, 6, true);
	//
	int specialIdleLeft[]{ 18, 19, 20, 21, 22, 23, 24, 25, 26 };			//enume : PLAYER_PLAYER_IDLE_SPECIAL_LEFT 3
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "specialIdleLeft", _imageKey, specialIdleLeft, 9, 6, true);

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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "highFallEndRight", _imageKey, highFallEndRight, 5, 6, true);

	int highFallEndLeft[] = { 75, 76, 77, 78, 79 };					//���� ������ �������鼭 rect�� bottom�� �ٴڿ� ���� ��쿡 �� �ִϸ��̼� �߰�(����)
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
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "ladderEnd", _imageKey, ladderEnd, 2, 7, true);				//���� �� �κ� ������ �Ȱɾ �� �������� Ȯ�� ���ؿ� (��ٸ� �� ó���ϰ� ���� Ȯ���ҰԿ�)

	int hitRight[] = { 123 };												//���Ϳ��� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitRight", _imageKey, hitRight, 1, 3, true);

	int hitLeft[] = { 132 };												//���Ϳ��� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitLeft", _imageKey, hitLeft, 1, 3, true);

	int hitDeathRight[] = { 117, 118, 119, 120, 121, 122 };					//���Ϳ��� �°� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathRight", _imageKey, hitDeathRight, 6, 3, true);

	int hitDeathLeft[] = { 126, 127, 128, 129, 130, 131 };					//���Ϳ��� �°� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "hitDeathLeft", _imageKey, hitDeathLeft, 6, 3, true);

	int fallDeathRight[] = { 135, 136, 137, 138, 139 };						//�������ٰ� ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathRight", _imageKey, fallDeathRight, 5, 3, true);

	int fallDeathLeft[] = { 140, 141, 142, 143, 144 };						//�������ٰ� ������(����)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fallDeathLeft", _imageKey, fallDeathLeft, 5, 3, true);

	int fireDeathRight[] = { 145, 146, 147, 148, 149, 150, 151, 152 };		//��Ÿ������(������)
	KEYANIMANAGER->addArrayFrameAnimation(_aniImageKey, "fireDeathRight", _imageKey, fireDeathRight, 8, 6, true);

	int fireDeathLeft[] = { 153, 154, 155, 156, 157, 158, 159, 160 };		//��Ÿ������(����)
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
	//============== �� �� ===============
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		_state = PLAYER_LADDER_UP;
		_playerAni = KEYANIMANAGER->findAnimation(_aniImageKey, "ladderUp");
		_playerAni->start();
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		//��ٸ��� �浹 �ƴ��� ���θ� üũ�� �ӽ� RECT
		RECT collisionTempRect;
		//int tempIndex = _object->getFieldLadders().size();
		
		_y -= _speed;

		
		
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_playerAni->pause();
	}

	//============== �� �� �� ===============
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