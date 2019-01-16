#pragma once
#include "gameNode.h"

class player_Baleog;
class player_Olaf;
class player_Eric;


class testScene : public gameNode
{
private:

	image*			_pixelMap;			//����ٰ� ��� �ʵ����͸� �����Ұ��� ���⼭ �ȼ������� �����ͼ� �����Ұ�.
	player_Baleog*	_baleog;
	player_Olaf*	_olaf;
	player_Eric*	_eric;
public:
	testScene();
	~testScene();

	HRESULT init();
	void release();
	void update();
	void render();
};