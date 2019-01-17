#include "stdafx.h"
#include "object.h"


object::object()
{
}


object::~object()
{
}

HRESULT object::init(const char* objName, const char * imgName, POINTF position, int itemValue, OBJECT_TYPE type)
{
	_objName.clear();
	_objName.append(objName);

	_img = IMAGEMANAGER->findImage(imgName);

	if(!_img)
		return E_FAIL;

	_x = position.x;
	_y = position.y;

	_destX = _x - (_img->getFrameWidth() / 2);	// �̹��� ������ left, top ���� �׸��⶧��
	_destY = _y - (_img->getFrameHeight() / 2);	// �̹��� ������ left, top ���� �׸��⶧��

	_linkObj = nullptr;
	_value = itemValue;
	_type = type;

	_ani = nullptr;

	KEYANIMANAGER->addAnimationType(_objName);
	// 190117 ����
	// ������Ʈ ���� ũ�⸦ ���� �ش�. : ���� �����Ϳ��� �о�ͼ� �ϴ°ǵ� �ϴ� �ϵ��ڵ����� �س��ڿ�
	// ��Ʈũ��(�浹ü)�� ������Ʈ ũ�⺰�� ���� �ֱ� ����
	switch (_type)
	{
		case OBJECT_TYPE_LOCK_RED:
		case OBJECT_TYPE_LOCK_YELLOW:
		case OBJECT_TYPE_LOCK_BLUE:
		{
			_frameX = _type;
			_frameY = 0;
			_size = {32, 32};

			int lockIdle[] = { _type };
			char key[128];
			sprintf_s(key, "lock%d", _type);
			
			KEYANIMANAGER->addArrayFrameAnimation(_objName, key, imgName, lockIdle, 1, 6, false);

			_ani = KEYANIMANAGER->findAnimation(_objName, key);

			break;
		}
		case OBJECT_TYPE_DOOR_RIGHT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_DOOR_RIGHT;
			_size = { 32, 96 };

			int doorIdle[] = { 0 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "doorRightIdle", imgName, doorIdle, 1, 6, false);
			
			int doorActive[] = { 1, 2 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "doorRightActive", imgName, doorActive, 2, 6, false);
			
			_ani = KEYANIMANAGER->findAnimation(_objName, "doorRightIdle");

			break;
		}
		case OBJECT_TYPE_DOOR_LEFT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_DOOR_RIGHT;
			_size = {32, 96};

			int doorIdle[] = { 3 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "doorLeftIdle", imgName, doorIdle, 1, 6, false);

			int doorActive[] = { 4, 5 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "doorLeftActive", imgName, doorActive, 2, 6, false);
			_ani = KEYANIMANAGER->findAnimation(_objName, "doorLeftIdle");
			break;
		}

		case OBJECT_TYPE_BRIDGE_RIGHT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_BRIDGE_RIGHT;
			_size = { 32, 160 };

			int bridgeIdle[] = { 0 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "bridgeRightIdle", imgName, bridgeIdle, 1, 6, false);

			int bridgeActive[] = { 1, 2, 3, 4 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "bridgeRightActive", imgName, bridgeActive, 4, 6, false);
			
			_ani = KEYANIMANAGER->findAnimation(_objName, "bridgeRightIdle");
			break;
		}

		case OBJECT_TYPE_BRIDGE_LEFT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_BRIDGE_RIGHT;
			_size = {32, 160};

			int bridgeIdle[] = { 5 };
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "bridgeLeftIdle", imgName, bridgeIdle, 1, 6, false);

			int bridgeActive[] = { 6, 7, 8 , 9};
			KEYANIMANAGER->addArrayFrameAnimation(_objName, "bridgeLeftActive", imgName, bridgeActive, 4, 6, false);
			
			_ani = KEYANIMANAGER->findAnimation(_objName, "bridgeLeftIdle");
			break;
		}
		default:
		{
			_frameX = 0;
			_frameY = 0;
			_size = {0, 0};
			break;
		}
	}
	
	MakeRect();
	if(_ani)
		_ani->start();
	_isActiveFinished = false;

	return S_OK;
}

void object::release()
{
	_img = nullptr;
	_linkObj = nullptr;
}

void object::update()
{
	KEYANIMANAGER->update(_objName);
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		if(KEYMANAGER->isStayKeyDown(VK_SPACE))
				active();

	}

	MakeRect();
}

void object::render()
{
	if(_ani)
		_img->aniRender(CAMERA->getMemDC(), _destX, _destY, _ani);
	if (KEYMANAGER->isToggleKey(VK_F6))
	{
		Rectangle(CAMERA->getMemDC(), _rc);
	}
	
	if (_isActiveFinished)
	{
		
	}
	else
	{

	}
}

void object::active()
{
	// �ѹ� �۵��� ������Ʈ�� �ٽ� �۵����� �ʴ´�
	if(_isActiveFinished)
		return;

	switch (_type)
	{
		case OBJECT_TYPE_LOCK_RED:
		case OBJECT_TYPE_LOCK_YELLOW:
		case OBJECT_TYPE_LOCK_BLUE:
		{
			break;
		}
		case OBJECT_TYPE_DOOR_RIGHT:
		{
			_ani = KEYANIMANAGER->findAnimation(_objName, "doorRightActive");
			break;
		}
		case OBJECT_TYPE_DOOR_LEFT:
		{
			_ani = KEYANIMANAGER->findAnimation(_objName, "doorLeftActive");
			break;
		}

		case OBJECT_TYPE_BRIDGE_RIGHT:
		{
			_ani = KEYANIMANAGER->findAnimation(_objName, "bridgeRightActive");
			break;
		}

		case OBJECT_TYPE_BRIDGE_LEFT:
		{
			_ani = KEYANIMANAGER->findAnimation(_objName, "bridgeLeftActive");
			break;
		}
	}

	if(_ani)
		_ani->start();

	_isActiveFinished = true;

	if (_linkObj)
		_linkObj->active();
}

void object::MakeRect()
{
	// �۵� �Ϸ�Ǿ����� ���̻� ��Ʈ �浹 ����
	if (_isActiveFinished)
	{
		_rc = {};
		return;
	}

	switch (_type)
	{
		case OBJECT_TYPE_LOCK_RED:
		case OBJECT_TYPE_LOCK_YELLOW:
		case OBJECT_TYPE_LOCK_BLUE:
		{
			_rc = RectMakeCenter(_x, _y, _size.x, _size.y);
			break;
		}
		case OBJECT_TYPE_DOOR_RIGHT:
		{
			_rc = RectMake(_x, _y - _size.y / 2, _size.x, _size.y);
			break;
		}
		case OBJECT_TYPE_DOOR_LEFT:
		{
			_rc = RectMake(_x - _size.x, _y - _size.y / 2, _size.x, _size.y);
			break;
		}
		case OBJECT_TYPE_BRIDGE_RIGHT:
		{
			_rc = RectMakeCenter(_x + _size.x * 2, _y, _size.x, _size.y);
			break;
		}
		case OBJECT_TYPE_BRIDGE_LEFT:
		{
			_rc = RectMakeCenter(_x - _size.x * 2, _y, _size.x, _size.y);
			break;
		}
		default:
		{
			_rc = {};
		}
			break;
	}
}
