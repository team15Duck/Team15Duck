#include "stdafx.h"
#include "objectManager.h"


objectManager::objectManager()
{
}


objectManager::~objectManager()
{
}

HRESULT objectManager::init()
{
	_vFieldObjects.clear();

	// todo 나중에 이미지 한번에 로드하는 부분으로 이동 할 것
	IMAGEMANAGER->addFrameImage("bridge", "image/bridge.bmp", 645, 256, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door", "image/door.bmp", 192, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lock", "image/lock.bmp", 162, 54, 3, 1, true, RGB(255, 0, 255));

	object* lockRed = new object;
	object* lockYellow = new object;
	object* lockBlue = new object;
	
	// lock blue
	{
		POINTF pos = { 448, 1162 };
		lockBlue->init("lock", pos, ITEM_TYPE_KEY_BLUE * 100, OBJECT_TYPE_LOCK_BLUE);

		_vFieldObjects.push_back(lockBlue);
	}

	// lock red
	{
		POINTF pos = { 1664, 1258 };
		lockRed->init("lock", pos, ITEM_TYPE_KEY_RED * 100, OBJECT_TYPE_LOCK_RED);

		_vFieldObjects.push_back(lockRed);
	}

	// lock yellow
	{
		POINTF pos = { 1728, 648 };
		lockYellow->init("lock", pos, ITEM_TYPE_KEY_YELLOW * 100, OBJECT_TYPE_LOCK_YELLOW);

		_vFieldObjects.push_back(lockYellow);
	}

	// bridge right - linked lock red
	{
		object* obj = new object;
		POINTF pos = {1789.f, 1242.f};
		obj->init("bridge", pos, -1, OBJECT_TYPE_BRIDGE_RIGHT);

		// 연결
		lockRed->setLinkObject(obj);

		_vFieldObjects.push_back(obj);
	}

	// door right - linked lock yellow
	{
		object* obj = new object;
		POINTF pos = { 1664.f, 650.f };
		obj->init("door", pos, -1, OBJECT_TYPE_DOOR_RIGHT);

		// 연결
		lockYellow->setLinkObject(obj);

		_vFieldObjects.push_back(obj);
	}

	// door left - linked lock blue
	{
		object* obj = new object;
		POINTF pos = { 416.f, 1353.f };
		obj->init("door", pos, -1, OBJECT_TYPE_DOOR_LEFT);

		// 연결
		lockBlue->setLinkObject(obj);

		_vFieldObjects.push_back(obj);
	}


	return S_OK;
}

void objectManager::release()
{
	vector<object*>::iterator iter = _vFieldObjects.begin();
	for (iter; _vFieldObjects.end() != iter; )
	{
		object* value = (*iter);
		if (value)
		{
			iter = _vFieldObjects.erase(iter);

			SAFE_RELEASE(value);
			SAFE_DELETE(value);
		}
		else
			++iter;
	}

	_vFieldObjects.clear();
}

void objectManager::update()
{
	int size = _vFieldObjects.size();
	for (int i = 0 ; i < size; ++i )
	{
		_vFieldObjects[i]->update();
	}
}

void objectManager::render()
{
	int size = _vFieldObjects.size();
	for (int i = 0; i < size; ++i)
	{
		_vFieldObjects[i]->render();
	}
}

void objectManager::interactionObjectWithItem(item* useItem)
{
	if(!useItem)
		return;

	int size = _vFieldObjects.size();
	for (int i = 0; i < size; ++i)
	{
		if(_vFieldObjects[i]->getItemValue() == useItem->getItemValue())
			doActiveObject(_vFieldObjects[i]);
	}
}

void objectManager::doActiveObject(object* obj)
{
	if (obj)
	{
		obj->active();
	}
}
