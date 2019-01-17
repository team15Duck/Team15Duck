#include "stdafx.h"
#include "itemManager.h"


itemManager::itemManager()
{
}


itemManager::~itemManager()
{
}

HRESULT itemManager::init()
{
	_vFieldItems.clear();

	// todo 나중에 이미지 한번에 로드하는 부분으로 이동 할 것
	IMAGEMANAGER->addFrameImage("fieldItem", "image/fieldItem.bmp", 540, 54, 10, 1, true, RGB(255, 0, 255));

	// create field items
	{
		// fruit small
		{
			item* value = new item;
			POINTF pos = { 64, 507};
			value->init("fieldItem", pos, 1, ITEM_TYPE_FRUIT_SMALL);

			_vFieldItems.push_back(value);
		}

		// fruit big 1
		{
			item* value = new item;
			POINTF pos = { 62, 956};
			value->init("fieldItem", pos, 1, ITEM_TYPE_FRUIT_BIG);

			_vFieldItems.push_back(value);
		}

		// fruit big 2
		{
			item* value = new item;
			POINTF pos = { 894, 700};
			value->init("fieldItem", pos, 1, ITEM_TYPE_FRUIT_BIG);

			_vFieldItems.push_back(value);
		}

		// meat
		{
			item* value = new item;
			POINTF pos = { 880, 284};
			value->init("fieldItem", pos, 2, ITEM_TYPE_MEAT);

			_vFieldItems.push_back(value);
		}

		// key blue
		{
			item* value = new item;
			POINTF pos = { 700, 1116};
			value->init("fieldItem", pos, ITEM_TYPE_KEY_BLUE * 100, ITEM_TYPE_KEY_BLUE);

			_vFieldItems.push_back(value);
		}

		// key red
		{
			item* value = new item;
			POINTF pos = { 1662, 442 };
			value->init("fieldItem", pos, ITEM_TYPE_KEY_RED * 100, ITEM_TYPE_KEY_RED);

			_vFieldItems.push_back(value);
		}

		// key yellow
		{
			item* value = new item;
			POINTF pos = { 1340, 986 };
			value->init("fieldItem", pos, ITEM_TYPE_KEY_YELLOW * 100, ITEM_TYPE_KEY_YELLOW);

			_vFieldItems.push_back(value);
		}

		// shield
		{
			item* value = new item;
			POINTF pos = { 1022, 600};
			value->init("fieldItem", pos, 1, ITEM_TYPE_SHIELD);

			_vFieldItems.push_back(value);
		}
	}

	return S_OK;
}

void itemManager::release()
{
	vector<item*>::iterator iter = _vFieldItems.begin();
	for ( iter; _vFieldItems.end() != iter; )
	{
		item* value = (*iter);
		if (value)
		{
			iter = _vFieldItems.erase(iter);
			
			SAFE_RELEASE(value);
			SAFE_DELETE(value);
		}
		else
			++iter;
	}

	_vFieldItems.clear();
}

void itemManager::update()
{
}

void itemManager::render()
{
	int size = _vFieldItems.size();
	for (int ii = 0 ; ii < size; ++ii)
	{
		_vFieldItems[ii]->render();
	}
}

void itemManager::obtainItem(item* targetItem)
{
	// 빈 값이 들어오면 리턴
	if(!targetItem)
		return;

	vector<item*>::iterator iter  = _vFieldItems.begin();
	vector<item*>::iterator end  = _vFieldItems.end();
	for (iter; end != iter; ++iter)
	{
		item* value = (*iter);
		if (value != targetItem)
			continue;

		_vFieldItems.erase(iter);

		SAFE_RELEASE(value);
		SAFE_DELETE(value);

		break;
	}
}
