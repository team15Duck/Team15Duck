#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(const char* imgName, POINTF position, int itemValue, ITEM_TYPE type)
{
	
	_img = IMAGEMANAGER->findImage(imgName);
	
	if(!_img)
		return E_FAIL;
	_isRender = true;
	_type = type;

	_x = position.x;
	_y = position.y;

	_destX = _x - _img->getFrameWidth() / 2;	// �̹��� ������ left, top ���� �׸��⶧��
	_destY = _y - _img->getFrameWidth() / 2;	// �̹��� ������ left, top ���� �׸��⶧��

	_value = itemValue;

	// 190116 ����
	// ������ ���� ũ�⸦ ���� �ش�. : ���� �����Ϳ��� �о�ͼ� �ϴ°ǵ� �ϴ� �ϵ��ڵ����� �س��ڿ�
	// ��Ʈũ��(�浹ü)�� ������ ũ�⺰�� ���� �ֱ� ����
	switch (type)
	{
		case ITEM_TYPE_FRUIT_SMALL: 
		{
			_size = {32, 28};
			break;
		}
		case ITEM_TYPE_FRUIT_BIG:
		{
			_size = { 26, 32 };
			break;
		}
		case ITEM_TYPE_MEAT:
		{
			_size = { 50, 54 };
			break;
		}
		case ITEM_TYPE_SHIELD:
		{
			_size = { 30, 30 };
			break;
		}
		case ITEM_TYPE_KEY_RED:
		case ITEM_TYPE_KEY_YELLOW:
		case ITEM_TYPE_KEY_BLUE:
		{
			_size = { 18, 32 };
			break;
		}
		default:
		{
			_size = {};
			break;
		}
	}

	_rc = RectMakeCenter(_x, _y, _size.x, _size.y);

	return S_OK;
}

void item::release()
{
	_img = nullptr;
}

void item::update()
{
}

void item::render()
{
	_img->frameRender(CAMERA->getMemDC(), _destX, _destY, _type, 0);
}