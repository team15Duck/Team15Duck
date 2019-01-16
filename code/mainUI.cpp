#include "stdafx.h"
#include "mainUI.h"


mainUI::mainUI()
{
}


mainUI::~mainUI()
{
}

HRESULT mainUI::init()
{
	_main = IMAGEMANAGER->addFrameImage("uiBaseImage", "image/profileUIBase.bmp", 1920, 128, 3, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("itemSelect", "image/itemSelect.bmp", 32, 32, true, RGB(255, 0, 255));
	_currentMainFrameIndex = 0;

	for (int i = 0; i < 3; i++)
	{
		_itemSelect[i].pos = i;
		_itemSelect[i].invenPos = 0;
		_itemSelect[i].isRender = true;
	}



	_isItemSelectOn = true;
	_isItemMove = false;
	_blinkedCount = 0;
	
	item* it[4];
	POINTF p = PointFMake(10, 10);
	it[0]->init("itemSelect", p, 1);

	setEricItemInfo(it);



	return S_OK;
}

void mainUI::release()
{

}

void mainUI::update()
{
	//아이템을 선택중이라면? 
	if (_isItemSelectOn)
	{
		_blinkedCount += TIMEMANAGER->getElpasedTime();
		if (_isItemMove) //선택중으로 들어와서 옮기기 키를 누르면 깜박이면 안된다!? 아니져 아이템만 깜박여야죠
		{
			for (int i = 0; i < 3; i++)
			{
				_itemSelect[i].isRender = true;
			}

		}
		else //선택중으로 들어와서 옮기고 있지 않다면? 깜박여
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == _currentMainFrameIndex)
				{
					_itemSelect[i].pos = i;
					_itemSelect[i].invenPos = 0;
					if (_blinkedCount > 0.5f)
					{
						_itemSelect[i].isRender = !_itemSelect[i].isRender;
						_blinkedCount = 0;
					}
				}
			}
		}
	}
}

void mainUI::render()
{
	_main->frameRender(CAMERA->getMemDC(), CAMERA->getPosX(), CAMERA->getPosY() + WINSIZEY - 128, _currentMainFrameIndex, 0);
	for (int i = 0; i < 3; i++)
	{
		if (_itemSelect[i].isRender)
		{
			IMAGEMANAGER->findImage("itemSelect")->render(CAMERA->getMemDC(), CAMERA->getPosX() + 158 + _itemSelect[i].pos * 144 + _itemSelect[i].invenPos % 2 * 32,
																			  CAMERA->getPosY() + 388 + _itemSelect[i].invenPos / 2 * 32);
		}
	}
}

void mainUI::setEricItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[0][i] = it[i];
	}
}

void mainUI::setBaleogItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[1][i] = it[i];
	}
}

void mainUI::setOlafItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[2][i] = it[i];
	}
}



void mainUI::setIsItemSelectOn(bool isItemSelectOn)
{
	_isItemSelectOn = isItemSelectOn;
	if (!_isItemSelectOn)
	{
		for (int i = 0; i < 3; i++)
		{
			_itemSelect[i].isRender = true;
		}
	}
}
