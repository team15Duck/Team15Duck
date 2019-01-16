#include "stdafx.h"
#include "item.h"


item::item()
{
}


item::~item()
{
}

HRESULT item::init(const char* imgName, POINTF position, int itemValue)
{
	_img = IMAGEMANAGER->findImage(imgName);


	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
}
