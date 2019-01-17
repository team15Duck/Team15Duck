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
	IMAGEMANAGER->addImage("playerHP", "image/hpImage.bmp", 12, 12, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("dieProfile", "image/dieProfile.bmp", 204, 52, 3, 1, false, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("invenItem", "image/invenItemImage.bmp", 224, 32, 7, 1, false, RGB(255, 0, 255));
	_currentMainFrameIndex = 0;

	for (int i = 0; i < 3; i++)
	{
		_itemSelect[i].name = (PLAYER_NAME)i;
		_itemSelect[i].invenPos = 0;
		_itemSelect[i].isRender = true;
		_playerHP[i] = 3;
		_isPlayerAlive[i] = true;
		for (int j = 0; j < 4; j++)
		{
			_playerItem[i][j] = nullptr;
		}
	}
	//_isPlayerAlive[1] = false;
	_isItemSelectOn = false;
	_isItemMove = false;
	_blinkedCount = 0;
	_playerItem[0][0] = new item;
	POINTF p = { 3,4 };
	_playerItem[0][0]->init("fieldItem", p, 1, ITEM_TYPE_FRUIT_SMALL);
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
				for (int j = 0; j < 4; j++)
				{
					if (_playerItem[i][j] != nullptr)
					{
						if (i == _currentMainFrameIndex)
						{
							if (_blinkedCount > 0.5f)
							{
								_playerItem[i][j]->setIsRender(!_playerItem[i][j]->getIsRender());
								_blinkedCount = 0;
							}
						}
					}
				}
				_itemSelect[i].renderPos.x = ceil(CAMERA->getPosX()) + 158 + _itemSelect[i].name * 144 + _itemSelect[i].invenPos % 2 * 32;
				_itemSelect[i].renderPos.y = ceil(CAMERA->getPosY()) + 388 + _itemSelect[i].invenPos / 2 * 32;
			}
		}
		else //선택중으로 들어와서 옮기고 있지 않다면? 깜박여
		{
			for (int i = 0; i < 3; i++)
			{
				if (i == _currentMainFrameIndex)
				{
					if (_blinkedCount > 0.5f)
					{
						_itemSelect[i].isRender = !_itemSelect[i].isRender;
						_blinkedCount = 0;
					}
				}

				for (int j = 0; j < 4; j++)
				{
					if (_playerItem[i][j] != nullptr)
					{
						_playerItem[i][j]->setIsRender(true);
					}
				}
				_itemSelect[i].renderPos.x = ceil(CAMERA->getPosX()) + 158 + _itemSelect[i].name * 144 + _itemSelect[i].invenPos % 2 * 32;
				_itemSelect[i].renderPos.y = ceil(CAMERA->getPosY()) + 388 + _itemSelect[i].invenPos / 2 * 32;
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
		for (int j = 0; j < 4; j++)
		{
			if (_playerItem[i][j] != nullptr)
			{
				if (_playerItem[i][j]->getIsRender())
				{
					IMAGEMANAGER->findImage("invenItem")->frameRender(CAMERA->getMemDC(), ceil(CAMERA->getPosX()) + 158 + i * 144 + j % 2 * 32,
																						  ceil(CAMERA->getPosY()) + 388 + j / 2 * 32,
																						  _playerItem[i][j]->getItemType(), 0);
				}
			}
		}
		//그리는명령이 있다면?
		if (_itemSelect[i].isRender)
		{
			IMAGEMANAGER->findImage("itemSelect")->render(CAMERA->getMemDC(), _itemSelect[i].renderPos.x,
																			  _itemSelect[i].renderPos.y);
		}
		//살아있지 않다면?
		if (!_isPlayerAlive[i])
		{
			IMAGEMANAGER->findImage("dieProfile")->frameRender(CAMERA->getMemDC(), ceil(CAMERA->getPosX()) + 90 + i * 144, ceil(CAMERA->getPosY()) + 388, i, 0);
		}
		//HP그리기
		for (int j = 0; j < _playerHP[i]; j++)
		{
			IMAGEMANAGER->findImage("playerHP")->render(CAMERA->getMemDC(), ceil(CAMERA->getPosX()) + 92 + i * 144 + j * 17, ceil(CAMERA->getPosY()) + 440);
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
