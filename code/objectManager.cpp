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
	IMAGEMANAGER->addFrameImage("bridge", "image/bridge.bmp", 805, 320, 5, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("door", "image/door.bmp", 192, 192, 3, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("lock", "image/lock.bmp", 162, 54, 3, 1, true, RGB(255, 0, 255));

	object* lockRed		= new object;
	object* lockYellow	= new object;
	object* lockBlue	= new object;
	
	// 오브젝트 생성 : 자물쇠
	{
		// lock blue
		POINTF pos = { 448, 1162 };
		lockBlue->init("lockBlue", "lock", pos, ITEM_TYPE_KEY_BLUE * 100, OBJECT_TYPE_LOCK_BLUE);
		_vFieldObjects.push_back(lockBlue);

		// lock red
		pos = { 1664, 1258 };
		lockRed->init("lockRed", "lock", pos, ITEM_TYPE_KEY_RED * 100, OBJECT_TYPE_LOCK_RED);
		_vFieldObjects.push_back(lockRed);

		// lock yellow
		pos = { 1728, 648 };
		lockYellow->init("lockYellow", "lock", pos, ITEM_TYPE_KEY_YELLOW * 100, OBJECT_TYPE_LOCK_YELLOW);
		_vFieldObjects.push_back(lockYellow);
	}

	// 오브젝트 생성 : 다리
	// bridge right - linked lock red
	{
		object* bridge = new object;
		POINTF pos = {1773.f, 1258.f};
		bridge->init("bridgeRight", "bridge", pos, -1, OBJECT_TYPE_BRIDGE_RIGHT);

		// 연결
		lockRed->setLinkObject(bridge);

		_vFieldObjects.push_back(bridge);
	}

	// 오브젝트 생성 : 문
	{
		// door right - linked lock yellow
		object* door1 = new object;
		POINTF pos = { 1664.f, 650.f };
		door1->init("doorRight", "door", pos, -1, OBJECT_TYPE_DOOR_RIGHT);

		// 연결
		lockYellow->setLinkObject(door1);
		_vFieldObjects.push_back(door1);


		// door left - linked lock blue
		object* obj = new object;
		pos = { 416.f, 1353.f };
		obj->init("doorLeft", "door", pos, -1, OBJECT_TYPE_DOOR_LEFT);

		// 연결
		lockBlue->setLinkObject(obj);
		_vFieldObjects.push_back(obj);
	}

	// 오브젝트 생성 : 사다리
	{
		object* ladder01 = new object;
		POINTF pos = {193.f, 841.f};
		POINT size = {2, 1124};
		ladder01->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder01->setCollisionSize(size);

		_vFieldLadders.push_back(ladder01);

		object* ladder02 = new object;
		pos = { 1121.f, 265.f };
		size = { 2, 162 };
		ladder02->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder02->setCollisionSize(size);

		_vFieldLadders.push_back(ladder02);

		object* ladder03 = new object;
		pos = { 1601.f, 585.f };
		size = { 2, 226 };
		ladder03->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder03->setCollisionSize(size);

		_vFieldLadders.push_back(ladder03);

		object* ladder04 = new object;
		pos = { 1985.f, 1001.f };
		size = { 2, 674 };
		ladder04->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder04->setCollisionSize(size);

		_vFieldLadders.push_back(ladder04);

		object* ladder05 = new object;
		pos = { 513.f, 1305.f };
		size = { 2, 194 };
		ladder05->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder05->setCollisionSize(size);

		_vFieldLadders.push_back(ladder05);

		object* ladder06 = new object;
		pos = { 1185.f, 1113.f };
		size = { 2, 194 };
		ladder06->init("ladder01", "", pos, -1, OBJECT_TYPE_LADDER);
		ladder06->setCollisionSize(size);

		_vFieldLadders.push_back(ladder06);
	}

	// 오브젝트 생성 : 부서지는 벽
	{
		object* brokenBlock = new object;
		POINTF pos = {1120.f, 1161.f};
		POINT size = {100, 300};
		brokenBlock->init("brokenBlock01", "", pos, -1, OBJECT_TYPE_BROKENBLOCK);
		brokenBlock->setCollisionSize(size);

		_vFieldObjects.push_back(brokenBlock);
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

	iter = _vFieldLadders.begin();
	for (iter; _vFieldLadders.end() != iter; )
	{
		object* value = (*iter);
		if (value)
		{
			iter = _vFieldLadders.erase(iter);

			SAFE_RELEASE(value);
			SAFE_DELETE(value);
		}
		else
			++iter;
	}

	_vFieldObjects.clear();
	_vFieldLadders.clear();
}

void objectManager::update()
{
	int size = (int)_vFieldObjects.size();
	for (int i = 0; i < size; ++i )
	{
		_vFieldObjects[i]->update();
	}

	size = (int)_vFieldLadders.size();
	for (int i = 0; i < size; ++i)
	{
		_vFieldLadders[i]->update();
	}
}

void objectManager::render()
{
	int size = (int)_vFieldObjects.size();
	for (int i = 0; i < size; ++i)
	{
		_vFieldObjects[i]->render();
	}

	size = (int)_vFieldLadders.size();
	for (int i = 0; i < size; ++i)
	{
		_vFieldLadders[i]->render();
	}
}

void objectManager::objectPixelRender(HDC hdc)
{
	int size = (int)_vFieldObjects.size();
	for (int i = 0; i < size; ++i)
	{
		_vFieldObjects[i]->pixelRender(hdc);
	}
}

bool objectManager::interactionObjectWithItem(item* useItem)
{
	if(!useItem)
		return false;

	int size = (int)_vFieldObjects.size();
	for (int i = 0; i < size; ++i)
	{
		// 값이 일치하면 사용
		if (_vFieldObjects[i]->getObjectValue() == useItem->getItemValue())
		{
			doActiveObject(_vFieldObjects[i]);
			return true;
		}
	}

	return false;
}

void objectManager::doActiveObject(object* obj)
{
	if (obj)
	{
		obj->active();
	}
}
