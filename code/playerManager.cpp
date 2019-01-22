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
	attackKey();
	for (vector<bullet*>::iterator iter = _vArrow.begin(); iter != _vArrow.end(); )
	{
		bullet* arrow = (*iter);
		if (arrow->isAlive())
		{
			arrow->update();
			++iter;
		}
		else
		{
			iter = _vArrow.erase(iter);
			
			SAFE_RELEASE(arrow);
			SAFE_DELETE(arrow);
		}
	}
}

void playerManager::render()
{
	for (int i = 0; i < PLAYER_NAME_COUNT; i++)
	{
		_vPlayer[i]->render();
	}
	for (int i = 0; i < _vArrow.size(); ++i)
	{
		_vArrow[i]->render();
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
	//셋중 하나라도 살아 있다면
	if (_vPlayer[PLAYER_NAME_ERIC]->getIsAlive() || _vPlayer[PLAYER_NAME_BALEOG]->getIsAlive() || _vPlayer[PLAYER_NAME_OLAF]->getIsAlive())
	{
		//컨트롤키를 누른다면
		if (KEYMANAGER->isOnceKeyDown(VK_CONTROL))
		{
			//다음놈이 살아있는놈일때까지 바꿈
			while (true)
			{
				_currentSelectPlayer = PLAYER_NAME(_currentSelectPlayer + 1);
				if (_currentSelectPlayer == PLAYER_NAME_NONE)
				{
					_currentSelectPlayer = PLAYER_NAME_ERIC;
				}
				if (_vPlayer[_currentSelectPlayer]->getIsAlive()) break;
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

void playerManager::attackKey()
{
	if (_vPlayer[PLAYER_NAME_BALEOG]->getIsFire())
	{
		POINTF baleogPos;
		baleogPos.x = *_vPlayer[PLAYER_NAME_BALEOG]->getPosX();
		baleogPos.y = *_vPlayer[PLAYER_NAME_BALEOG]->getPosY();
		
		image* arrowImg = IMAGEMANAGER->addFrameImage("arrow", "image/arrow.bmp", 136, 40, 4, 2, true, RGB(255, 0, 255));
		_arrow = new bullet;
		_arrow->init(arrowImg, _pixelData, _vPlayer[PLAYER_NAME_BALEOG]->getIsAttackRight(), baleogPos);			//todo 일단 한방향으로만 발사해보자
		
		_vPlayer[PLAYER_NAME_BALEOG]->setIsFire(false);
		_vArrow.push_back(_arrow);
	}
}
