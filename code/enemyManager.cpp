#include "stdafx.h"
#include "enemyManager.h"
#include "playerManager.h"	

enemyManager::enemyManager()
{
}

enemyManager::~enemyManager()
{
}

HRESULT enemyManager::init()
{
	enemy* test = new enemy;
	test->init(0, 1025 + 51, 346 - 31, 1025 + 31, 1185 - 31);
	_vEnemy.push_back(test);


	for (int i = 0; i < 10; i++)
	{

		enemy* test = new enemy;
		test->init(i + 1, RND->getFromIntTo(460, 640), 1372, 450, 650);
		_vEnemy.push_back(test);
	}


	return S_OK;
}

void enemyManager::release()
{
}

void enemyManager::update()
{
	int vSize = _vEnemy.size();
	for (int i = 0; i < vSize; i++)
	{
		_vEnemy[i]->update();
		for (int j = 0; j < 3; j++)
		{
			if (_vEnemy[i]->isFire(*_pm->getVPlayer()[j]->getPosX(), *_pm->getVPlayer()[j]->getPosY()))
			{
				//ÃÑ¾Ë¹ß»ç
			}
		}
		
	}
}

void enemyManager::render()
{
	int vSize = _vEnemy.size();
	for (int i = 0; i < vSize; i++)
	{
		if (!_vEnemy[i]->getIsAlive()) continue;
		_vEnemy[i]->render();
	}
}

void enemyManager::bulletFire()
{
}
