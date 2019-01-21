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

	for (int i = 0; i < PLAYER_NAME_COUNT; ++i)
	{
		RECT temp;
		vector<object*> ladders = _om->getFieldLadders();

		for (int j = 0; j < ladders.size(); ++j)
		{
			if (IntersectRect(&temp, ladders[j]->getObjectRect(), &_vPlayer[i]->getPlayerRect()))
			{
				_vPlayer[i]->playerCollisionLadder(ladders[j]);
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

void playerManager::shieldPixelRender(HDC hdc)
{
	_vPlayer[PLAYER_NAME_OLAF]->shieldRender(hdc);
}

void playerManager::keyUpdate()
{
	if (!CAMERA->getMapMove())
		_vPlayer[_currentSelectPlayer]->keyUpdate();
}

void playerManager::keyPressCtrl()
{
	if (TIMEMANAGER->getWorldTime() < 0.5f) return;
	//if (!CAMERA->getMapMove())
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


			if (CAMERA->getCenterPos().x == playerPos.x && CAMERA->getCenterPos().y == playerPos.y)
			{
				CAMERA->setMapMove(false);
			}
			else if (CAMERA->getCenterPos().x == playerPos.x && CAMERA->getCenterPos().y > playerPos.y)
			{
				CAMERA->setAngle(90);
			}
			else if (CAMERA->getCenterPos().x == playerPos.x && CAMERA->getCenterPos().y < playerPos.y)
			{
				CAMERA->setAngle(270);
			}
			else if (CAMERA->getCenterPos().x > playerPos.x && CAMERA->getCenterPos().y == playerPos.y)
			{
				CAMERA->setAngle(180);
			}
			else if (CAMERA->getCenterPos().x < playerPos.x && CAMERA->getCenterPos().y == playerPos.y)
			{
				CAMERA->setAngle(0);
			}
			else if (CAMERA->getCenterPos().x < playerPos.x && CAMERA->getCenterPos().y > playerPos.y)	//플레이어가 오른쪽위에 있을때
			{
				CAMERA->setAngle(45);
			}
			else if (CAMERA->getCenterPos().x < playerPos.x && CAMERA->getCenterPos().y < playerPos.y)	//플레이어가 오른쪽아래에 있을때
			{
				CAMERA->setAngle(315);
			}
			else if (CAMERA->getCenterPos().x > playerPos.x && CAMERA->getCenterPos().y > playerPos.y)	//플레이어가 왼쪽위에 있을때
			{
				CAMERA->setAngle(135);
			}
			else if (CAMERA->getCenterPos().x > playerPos.x && CAMERA->getCenterPos().y < playerPos.y)	//플레이어가 왼쪽아래에 있을때
			{
				CAMERA->setAngle(225);
			}

			_mainUI->setCurrentMainFrameIndex(_currentSelectPlayer);
			CAMERA->setPlayerPosX(_vPlayer[_currentSelectPlayer]->getPosX());
			CAMERA->setPlayerPosY(_vPlayer[_currentSelectPlayer]->getPosY());
		}
	}
}