#include "stdafx.h"
#include "playerManager.h"
#include "mainUI.h"
#include "itemManager.h"
#include "objectManager.h"

playerManager::playerManager()
{
}


playerManager::~playerManager()
{
}

HRESULT playerManager::init()
{
	_vPlayer.push_back(new player_Eric);
	_vPlayer.push_back(new player_Baleog);
	_vPlayer.push_back(new player_Olaf);
	
	_vPlayer[PLAYER_NAME_ERIC]->init();
	_vPlayer[PLAYER_NAME_BALEOG]->init();
	_vPlayer[PLAYER_NAME_OLAF]->init();

	_currentSelectPlayer = PLAYER_NAME_ERIC;
	//_currentSelectPlayer = PLAYER_NAME_BALEOG;
	//_currentSelectPlayer = PLAYER_NAME_OLAF;
	CAMERA->setPlayerPosX(_vPlayer[_currentSelectPlayer]->getPosX());
	CAMERA->setPlayerPosY(_vPlayer[_currentSelectPlayer]->getPosY());
	return S_OK;
}

void playerManager::release()
{
}

void playerManager::update()
{
	for (int i = 0; i < PLAYER_NAME_COUNT; i++)
	{
		_vPlayer[i]->update();
		for (int j = 0; j < _im->getFieldItems().size(); j++)
		{
			RECT _temp;
			if (IntersectRect(&_temp, &_im->getFieldItems()[j]->getItemRect(), &_vPlayer[i]->getPlayerRect()))
			{
				for (int k = 0; k < 4; k++)
				{
					if (_vPlayer[i]->getInvenItem()[k] == nullptr)
					{
						_vPlayer[i]->getInvenItem()[k] = _im->getFieldItems()[j];
						_im->obtainItem(_im->getFieldItems()[j]);
						switch (i)
						{
							case PLAYER_NAME_ERIC:
								_mainUI->setEricItemInfo(_vPlayer[i]->getInvenItem());
							break;
							case PLAYER_NAME_BALEOG:
								_mainUI->setBaleogItemInfo(_vPlayer[i]->getInvenItem());
							break;
							case PLAYER_NAME_OLAF:
								_mainUI->setOlafItemInfo(_vPlayer[i]->getInvenItem());
							break;
						}
						break;
					}
				}
			}
		}
	}
}

void playerManager::render()
{
	for (int i = 0; i < PLAYER_NAME_COUNT; i++)
	{
		_vPlayer[i]->render();
	}
}

void playerManager::shieldPixelRender()
{
	//if (_vPlayer[PLAYER_NAME_OLAF]->방패들고있니?)
	{
		//들고있으면 IMAGEMANAGER->FindImage("stage1PixelMap")->getMemDC(); << 여기에 방패모양 올라프 좌표 맞춰서 그려주세요
	}
}

void playerManager::keyUpdate()
{
	if (!CAMERA->getMapMove())
		_vPlayer[_currentSelectPlayer]->keyUpdate();
}

void playerManager::keyPressCtrl()
{
	if(TIMEMANAGER->getWorldTime() < 0.5f) return;
	if (!CAMERA->getMapMove())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
		{

			_currentSelectPlayer = PLAYER_NAME(_currentSelectPlayer + 1);
			if (_currentSelectPlayer == PLAYER_NAME_NONE)
			{
				_currentSelectPlayer = PLAYER_NAME_ERIC;
			}
			CAMERA->setMapMove(true);
			POINTF playerPos;
			playerPos.x = *_vPlayer[_currentSelectPlayer]->getPosX();
			playerPos.y = *_vPlayer[_currentSelectPlayer]->getPosY();
			CAMERA->setAngle(dGetAngle(playerPos, CAMERA->getCenterPos()));
			_mainUI->setCurrentMainFrameIndex(_currentSelectPlayer);
			CAMERA->setPlayerPosX(_vPlayer[_currentSelectPlayer]->getPosX());
			CAMERA->setPlayerPosY(_vPlayer[_currentSelectPlayer]->getPosY());
		}
	}
}