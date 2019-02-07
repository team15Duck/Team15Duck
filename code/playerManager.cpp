#include "stdafx.h"
#include "playerManager.h"
#include "mainUI.h"
#include "itemManager.h"
#include "objectManager.h"
#include "enemyManager.h"

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

	
	_itemSelectNum = -1;

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
	attackKey();		//활 키를 눌렀을 때 실행할 함수
	colArrowEnemy();	//활과 적의 충돌처리
	for (vector<bullet*>::iterator iter = _vArrow.begin(); iter != _vArrow.end(); )
	{
		bullet* arrow = (*iter);
		if (arrow->getIsAlive())
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
	if (!_vPlayer[_currentSelectPlayer]->getIsAlive())
	{
		_mainUI->setIsRender(_currentSelectPlayer, true);
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
			_mainUI->setIsRender(_currentSelectPlayer, true);
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


void playerManager::colArrowEnemy()
{
	//적과 충돌을 위한 반복문
	RECT	colEnemyArrow;
	int enemySize = _em->getVEnemy().size();
	for (int i = 0; i < enemySize; ++i)
	{
		for (int j = 0; j < _vArrow.size(); ++j)
		{
			if (!_em->getVEnemy()[i]->getIsAlive()) continue;
			//플레이어의 화살과 적이 충돌하면 적 죽임
			if (IntersectRect(&colEnemyArrow, &_em->getVEnemy()[i]->getEnemyRc(), &_vArrow[j]->getRect()))
			{
				_em->getVEnemy()[i]->setIsAlive(false);
				_vArrow[j]->setIsAlive(false);
			}

		}

	}
}

void playerManager::colEnemyPlayer()
{
	RECT colEnemyPlayer;
	int enemySize = _em->getVEnemy().size();
	for (int i = 0; i < PLAYER_NAME_COUNT; i++)
	{
	
		for (int j = 0; j < enemySize; ++j)
		{
			if (IntersectRect(&colEnemyPlayer, &_em->getVEnemy()[j]->getEnemyRc(), &_vPlayer[i]->getPlayerRect()))
			{
				(*_vPlayer[i]).takeDamage(1);
			}
		}
	}
}


void playerManager::uiKeyControl()
{
	if (_mainUI->getIsItemSelectOn())
	{
		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			if (_mainUI->getItemMoveIndex() == 3)
			{
				delete _vPlayer[_currentSelectPlayer]->getInvenItem()[_mainUI->getInvenPos(_currentSelectPlayer)];
				_vPlayer[_currentSelectPlayer]->setInvenItem(_mainUI->getInvenPos(_currentSelectPlayer), nullptr);
				_mainUI->setNameItemInfo(_currentSelectPlayer, _vPlayer[_currentSelectPlayer]->getInvenItem());
			}
			else
			{
				if (_currentSelectPlayer != _mainUI->getItemMoveIndex())
				{
					if (_itemSelectNum != -1)
					{
						//스왑
						item* temp = _vPlayer[_currentSelectPlayer]->getInvenItem()[_mainUI->getInvenPos(_currentSelectPlayer)];
						_vPlayer[_currentSelectPlayer]->setInvenItem(_mainUI->getInvenPos(_currentSelectPlayer), _vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem()[_itemSelectNum]);
						_vPlayer[_mainUI->getItemMoveIndex()]->setInvenItem(_itemSelectNum, temp);

						_mainUI->setNameItemInfo(_currentSelectPlayer, _vPlayer[_currentSelectPlayer]->getInvenItem());
						_mainUI->setNameItemInfo(_mainUI->getItemMoveIndex(), _vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem());
					}
				}
			}
			_mainUI->setIsItemSelectOn(false);
			_mainUI->setItemMoveIndex(_currentSelectPlayer);
			_mainUI->setIsItemMove(false);
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown(VK_TAB))
		{
			_mainUI->setItemMoveIndex(_currentSelectPlayer);
			_mainUI->setIsItemSelectOn(true);
			_mainUI->setIsItemMove(false);
		}
	}
	

	if (!_mainUI->getIsItemSelectOn()) return;

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_mainUI->getIsItemMove())
		{
			if (_mainUI->getItemMoveIndex() == 3)
			{
				delete _vPlayer[_currentSelectPlayer]->getInvenItem()[_mainUI->getInvenPos(_currentSelectPlayer)];
				_vPlayer[_currentSelectPlayer]->setInvenItem(_mainUI->getInvenPos(_currentSelectPlayer), nullptr);
				_mainUI->setNameItemInfo(_currentSelectPlayer, _vPlayer[_currentSelectPlayer]->getInvenItem());
			}
			else
			{
				if (_currentSelectPlayer != _mainUI->getItemMoveIndex())
				{
					if (_itemSelectNum != -1)
					{
						//스왑
						item* temp = _vPlayer[_currentSelectPlayer]->getInvenItem()[_mainUI->getInvenPos(_currentSelectPlayer)];
						_vPlayer[_currentSelectPlayer]->setInvenItem(_mainUI->getInvenPos(_currentSelectPlayer), _vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem()[_itemSelectNum]);
						_vPlayer[_mainUI->getItemMoveIndex()]->setInvenItem(_itemSelectNum, temp);

						_mainUI->setNameItemInfo(_currentSelectPlayer, _vPlayer[_currentSelectPlayer]->getInvenItem());
						_mainUI->setNameItemInfo(_mainUI->getItemMoveIndex(), _vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem());
					}
				}
			}
		


			_mainUI->setIsItemMove(false);
			_mainUI->setItemMoveIndex(_currentSelectPlayer);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				if (_vPlayer[_currentSelectPlayer]->getInvenItem()[i] != nullptr)
				{
					_mainUI->setIsItemMove(true);
					_mainUI->setItemMoveIndex(_currentSelectPlayer);
					_itemSelectNum = _mainUI->getInvenPos(_currentSelectPlayer);
					break;
				}
			}
		}
	
	}
	
	if (!_mainUI->getIsItemMove())
	{
		if (_mainUI->getInvenPos(_currentSelectPlayer) == 0 || _mainUI->getInvenPos(_currentSelectPlayer) == 1)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
			{
				_mainUI->setInvenPos(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer) + 2);
			}
		}
		if (_mainUI->getInvenPos(_currentSelectPlayer) == 2 || _mainUI->getInvenPos(_currentSelectPlayer) == 3)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_UP))
			{
				_mainUI->setInvenPos(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer) - 2);
			}
		}
		if (_mainUI->getInvenPos(_currentSelectPlayer) == 1 || _mainUI->getInvenPos(_currentSelectPlayer) == 3)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			{
				_mainUI->setInvenPos(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer) - 1);
			}
		}
		if (_mainUI->getInvenPos(_currentSelectPlayer) == 0 || _mainUI->getInvenPos(_currentSelectPlayer) == 2)
		{
			if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			{
				_mainUI->setInvenPos(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer) + 1);
			}
		}
	}
	else
	{
		//_playerItem[i][j]->setX((int)(CAMERA->getPosX()) + 158 + i * 144 + j % 2 * 32);
		//_playerItem[i][j]->setY((int)(CAMERA->getPosY()) + 388 + j / 2 * 32);
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
		{
			bool invenFind = false;
			while (!invenFind)
			{
			
				if (_mainUI->getItemMoveIndex() == 0)
				{
					_mainUI->setItemMoveIndex(3);
				}
				else
				{
					_mainUI->setItemMoveIndex(_mainUI->getItemMoveIndex() - 1);
				}
				if (_mainUI->getItemMoveIndex() == 3) break;
				if (_currentSelectPlayer == _mainUI->getItemMoveIndex())
				{
					_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setX((int)(CAMERA->getPosX()) + 158 + _mainUI->getItemMoveIndex() * 144 + _mainUI->getInvenPos(_currentSelectPlayer) % 2 * 32);
					_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setY((int)(CAMERA->getPosY()) + 388 + _mainUI->getInvenPos(_currentSelectPlayer) / 2 * 32);
					invenFind = true;
					break;
				}
				RECT temp;
				if (IntersectRect(&temp, &_vPlayer[_currentSelectPlayer]->getPlayerRect(), &_vPlayer[_mainUI->getItemMoveIndex()]->getPlayerRect()))
				{
					for (int i = 0; i < 4; i++)
					{
						if (_vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem()[i] == nullptr)
						{
							_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setX((int)(CAMERA->getPosX()) + 158 + _mainUI->getItemMoveIndex() * 144 + i % 2 * 32);
							_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setY((int)(CAMERA->getPosY()) + 388 + i / 2 * 32);
							_itemSelectNum = i;
							invenFind = true;
							break;
						}
					}
				}
			}
		}
		if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
		{
			bool invenFind = false;
			while (!invenFind)
			{
				if (_mainUI->getItemMoveIndex() == 3)
				{
					_mainUI->setItemMoveIndex(0);
				}
				else
				{
					_mainUI->setItemMoveIndex(_mainUI->getItemMoveIndex() + 1);
				}
				if (_mainUI->getItemMoveIndex() == 3) break;
				if (_currentSelectPlayer == _mainUI->getItemMoveIndex())
				{
					_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setX((int)(CAMERA->getPosX()) + 158 + _mainUI->getItemMoveIndex() * 144 + _mainUI->getInvenPos(_currentSelectPlayer) % 2 * 32);
					_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setY((int)(CAMERA->getPosY()) + 388 + _mainUI->getInvenPos(_currentSelectPlayer) / 2 * 32);
					invenFind = true;
					break;
				}
				RECT temp;
				if (IntersectRect(&temp, &_vPlayer[_currentSelectPlayer]->getPlayerRect(), &_vPlayer[_mainUI->getItemMoveIndex()]->getPlayerRect()))
				{
					for (int i = 0; i < 4; i++)
					{
						if (_vPlayer[_mainUI->getItemMoveIndex()]->getInvenItem()[i] == nullptr)
						{
							_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setX((int)(CAMERA->getPosX()) + 158 + _mainUI->getItemMoveIndex() * 144 + i % 2 * 32);
							_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setY((int)(CAMERA->getPosY()) + 388 + i / 2 * 32);
							_itemSelectNum = i;
							invenFind = true;
							break;
						}
					}
				}
			}
		}

		if (_mainUI->getItemMoveIndex() == 3)
		{
			_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setX((int)(CAMERA->getPosX()) + 158 + 2 * 144 + 2 * 32);
			_mainUI->getItemInfo(_currentSelectPlayer, _mainUI->getInvenPos(_currentSelectPlayer))->setY((int)(CAMERA->getPosY()) + 388);
		}
		



	}
}
