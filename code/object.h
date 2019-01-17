#pragma once
//#include "animation.h"

enum OBJECT_TYPE
{
	OBJECT_TYPE_LOCK_RED,		// �ڹ��� R
	OBJECT_TYPE_LOCK_YELLOW,	// �ڹ��� Y
	OBJECT_TYPE_LOCK_BLUE,		// �ڹ��� B
	OBJECT_TYPE_DOOR_RIGHT,		// �� �����ʿ� �ִ�
	OBJECT_TYPE_DOOR_LEFT,		// �� ���ʿ� �ִ�
	OBJECT_TYPE_BRIDGE_RIGHT,	// �ٸ�	�����ʿ� �ִ�
	OBJECT_TYPE_BRIDGE_LEFT,	// �ٸ� ���ʿ� �ִ�

	OBJECT_TYPE_NONE,
	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE,
};

class object
{
private:

	float _x;				// ������ǥ
	float _y;

	float _destX, _destY;	// �̹��� �׸� left, top��ǥ

	OBJECT_TYPE	_type;		// ������Ʈ Ÿ��
	int			_value;		// �������̶� ������ Ű��(ex.  KEY _value == LOCK _value >> ���� ������		
	object*		_linkObj;	// ����� ������Ʈ (ex. �ڹ���� �� or �ٸ� �� ����Ǿ�����)

	image*	_img;			// �̹���
	POINT	_size;			// ũ��
	RECT	_rc;			// �浹 ��Ʈ

	bool _isActiveFinished;	// �۵� �Ϸ��ߴ��� (ex. ���� �����ִٸ� false, �����ִٸ� true)

	int _frameX;
	int _frameY;

	string _objName;		// ������Ʈ �̸�

	animation* _ani;

public:
	object();
	~object();

	HRESULT init(const char* objName, const char* imgName, POINTF position, int itemValue, OBJECT_TYPE type);
	void release();
	void update();
	void render();


	// �۵�
	void active();
	//void endActive();

	// ����Ǵ� ������Ʈ ����
	void setLinkObject(object* obj) { _linkObj = obj; }

	OBJECT_TYPE getItemType() { return _type;	}
	int			getItemValue(){ return _value;	}
	RECT		getItemRect() { return _rc;		}

private:
	// ��Ʈ ����
	void MakeRect();
};

