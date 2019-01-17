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
		_itemSelect[i].name = (PLAYER_NAME)i;
		_itemSelect[i].invenPos = 0;
		_itemSelect[i].isRender = true;
	}

	_isItemSelectOn = false;
	_isItemMove = false;
	_blinkedCount = 0;
	
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
					_itemSelect[i].name = (PLAYER_NAME)i;
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
	else
	{
		for (int i = 0; i < 3; i++)
		{
			_itemSelect[i].renderPos.x = ceil(CAMERA->getPosX()) + 158 + _itemSelect[i].name * 144 + _itemSelect[i].invenPos % 2 * 32;
			_itemSelect[i].renderPos.y = ceil(CAMERA->getPosY()) + 388 + _itemSelect[i].invenPos / 2 * 32;
		}
	}
}

void mainUI::render()
{
	_main->frameRender(CAMERA->getMemDC(), ceil(CAMERA->getPosX()), ceil(CAMERA->getPosY()) + WINSIZEY - 128, _currentMainFrameIndex, 0);
	for (int i = 0; i < 3; i++)
	{
		if (_itemSelect[i].isRender)
		{
			IMAGEMANAGER->findImage("itemSelect")->render(CAMERA->getMemDC(), _itemSelect[i].renderPos.x,
																			  _itemSelect[i].renderPos.y);
		}
	}
}

void mainUI::setEricItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[PLAYER_NAME_ERIC][i] = it[i];
	}
}

void mainUI::setBaleogItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[PLAYER_NAME_BALEOG][i] = it[i];
	}
}

void mainUI::setOlafItemInfo(item ** it)
{
	for (int i = 0; i < 4; i++)
	{
		_playerItem[PLAYER_NAME_OLAF][i] = it[i];
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
