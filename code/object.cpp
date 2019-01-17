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

	_destX = _x - (_img->getFrameWidth() / 2);	// 이미지 렌더는 left, top 으로 그리기때문
	_destY = _y - (_img->getFrameHeight() / 2);	// 이미지 렌더는 left, top 으로 그리기때문

	_linkObj = nullptr;
	_value = itemValue;
	_type = type;

	// 190117 진형
	// 오브젝트 별로 크기를 따로 준다. : 원래 데이터에서 읽어와서 하는건데 일단 하드코딩으로 해놓겠움
	// 렉트크기(충돌체)를 오브젝트 크기별로 따로 주기 위함
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
	// 한번 작동된 오브젝트는 다시 작동하지 않는다
	if(_isActiveFinished)
		return;

	if(_linkObj)
		_linkObj->active();
}

void object::MakeRect()
{
	// 작동 완료되었으면 더이상 렉트 충돌 없음
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
