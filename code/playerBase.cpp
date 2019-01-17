#include "stdafx.h"
#include "playerBase.h"


playerBase::playerBase()
{
}


playerBase::~playerBase()
{
}

HRESULT playerBase::init()
{
	_proveBottom = (float)_playerRect.bottom;
	for (int i = 0; i < 4; i++)
	{
		_invenItem[i] = nullptr;
	}
	return S_OK;
}

void playerBase::release()
{
}

void playerBase::update()
{
}

void playerBase::render()
{
	

}

void playerBase::keyUpdate()
{
	keyPressMove();
	keyPressSpace();
	keyPressD();
	keyPressE();
}

void playerBase::keyPressMove()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_x -= _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_x += _speed;
	}
	
}

void playerBase::keyPressSpace()
{
}

void playerBase::keyPressD()
{
}

void playerBase::keyPressE()
{
}

void playerBase::keyPressS()
{
}





void playerBase::pixelHorizenWallCollision()
{
}

void playerBase::rectBrokenWallCollision()
{
}

void playerBase::pixelTopWallCollision()
{
}

void playerBase::pixelBottomCollision()
{

}
