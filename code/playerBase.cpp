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
	
	return S_OK;
}

void playerBase::release()
{
}

void playerBase::update()
{
}

void playerBase::render(HDC cameraDC)
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

void playerBase::keyPressCtrl()
{
}

void playerBase::keyPressTab()
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
