#include "stdafx.h"
#include "playerManager.h"
#include "mainUI.h"

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
	}
}

void playerManager::render()
{
	for (int i = 0; i < PLAYER_NAME_COUNT; i++)
	{
		_vPlayer[i]->render();
	}
}

void playerManager::keyUpdate()
{
	if (!CAMERA->getMapMove())
		_vPlayer[_currentSelectPlayer]->keyUpdate();
}

void playerManager::keyPressCtrl()
{
	if (TIMEMANAGER->getWorldTime() < 0.5f) return;
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