#include "stdafx.h"
#include "object.h"


object::object()
{
}


object::~object()
{
}

HRESULT object::init(const char * imgName, POINTF position, int itemValue, OBJECT_TYPE type)
{
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
			break;
		}
		case OBJECT_TYPE_DOOR_RIGHT:
		case OBJECT_TYPE_DOOR_LEFT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_DOOR_RIGHT;
			_size = {32, 96};
			break;
		}
		case OBJECT_TYPE_BRIDGE_RIGHT:
		case OBJECT_TYPE_BRIDGE_LEFT:
		{
			_frameX = 0;
			_frameY = _type - OBJECT_TYPE_BRIDGE_RIGHT;
			_size = {32, 128};
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
	MakeRect();
}

void object::render()
{
	_img->frameRender(CAMERA->getMemDC(), _destX, _destY, _frameX, _frameY);
	//Rectangle(CAMERA->getMemDC(), _rc);
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

	if(_linkObj)
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
			_rc = RectMake(_x + _size.x, _y - _size.y / 2, _size.x, _size.y);
			break;
		}
		case OBJECT_TYPE_BRIDGE_LEFT:
		{
			_rc = RectMake(_x - _size.x * 2, _y - _size.y / 2, _size.x, _size.y);
			break;
		}
		default:
		{
			_rc = {};
		}
			break;
	}
}
