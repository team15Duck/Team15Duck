#include "stdafx.h"
#include "playerManager.h"


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
		_vPlayer[i]->render(CAMERA->getMemDC());
	}
}

void playerManager::keyUpdate()
{
	if (CAMERA->getMapMove()) return;
	_vPlayer[_currentSelectPlayer]->keyUpdate();
}

void playerManager::keyPressCtrl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
	{
		_currentSelectPlayer = PLAYER_NAME(_currentSelectPlayer + 1);
		if (_currentSelectPlayer == PLAYER_NAME_NONE)
		{
			_currentSelectPlayer = PLAYER_NAME_ERIC;
		}
		CAMERA->setMapMove(true);
	
		CAMERA->setPlayerPosX(_vPlayer[_currentSelectPlayer]->getPosX());
		CAMERA->setPlayerPosY(_vPlayer[_currentSelectPlayer]->getPosY());
	}
}