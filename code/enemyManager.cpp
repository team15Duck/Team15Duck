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
	IMAGEMANAGER->addImage("bullet", "image/enemyBullet.bmp", 32, 6, true, RGB(255, 0, 255));
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
			int bulletFire = _vEnemy[i]->isFire(*_pm->getVPlayer()[j]->getPosX(), *_pm->getVPlayer()[j]->getPosY());
			if (bulletFire == 0)
			{
				continue;
			}
			else if (bulletFire == 1)
			{
				bullet* newBullet = new bullet;
				newBullet->init2(IMAGEMANAGER->findImage("bullet"), _pixelData, false, _vEnemy[i]->getPos());
				_vBullet.push_back(newBullet);
			}
			else if (bulletFire == 2)
			{
				bullet* newBullet = new bullet;
				newBullet->init2(IMAGEMANAGER->findImage("bullet"), _pixelData, true, _vEnemy[i]->getPos());
				_vBullet.push_back(newBullet);
			}
		}
	}

	vSize = _vBullet.size();
	RECT temp;
	for (int i = 0; i < vSize; i++)
	{
		////////////////////////// �ȼ� �浹
		if (!_vBullet[i]->isAlive())
		{
			_vBullet.erase(_vBullet.begin() + i);
			i--;
			vSize--;

			continue;
		}

		////////////////////////// ��Ʈ �浹
		{
			bool isCollision = false;					// �浹�Ǿ����� Ȯ��
			RECT bulletRc = _vBullet[i]->getRect();		// �Ѿ� ��Ʈ

			//todo ������� ����ִٸ� ����� ���� �浹 ó�� ����
			if (_pm->getVPlayer()[PLAYER_NAME_OLAF]->getIsAlive())
			{
				//if(IntersectRect(&temp, &_pm->getVPlayer()[PLAYER_NAME_OLAF]->getShieldRect(), &bulletRc))
				{
					//isCollision = true;
				}
			}

			if (!isCollision)
			{
				//�÷��̾�� ��Ʈ �浹
				for (int j = 0; j < PLAYER_NAME_COUNT; ++j)
				{
					// �׾��ִٸ� continue;
					if (!_pm->getVPlayer()[j]->getIsAlive())
						continue;

					if (IntersectRect(&temp, &_pm->getVPlayer()[j]->getPlayerRect(), &bulletRc))
					{
						// todo �÷��̾� ������ �Դ� �Լ� ȣ��

						// �浹��
						isCollision = true;

						break;
					}
				}
			}

			if (isCollision)
			{
				bullet* blt = _vBullet[i];

				_vBullet.erase(_vBullet.begin() + i);
				i--;
				vSize--;

				SAFE_RELEASE(blt);
				SAFE_DELETE(blt);

				break;
			}
		}

		_vBullet[i]->update2();

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
	vSize = _vBullet.size();
	for (int i = 0; i < vSize; i++)
	{
		_vBullet[i]->render2();
	}
}
