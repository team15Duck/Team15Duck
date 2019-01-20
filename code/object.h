#pragma once
//#include "animation.h"

// ������Ʈ Ÿ��
enum OBJECT_TYPE
{
	OBJECT_TYPE_LOCK_RED,		// �ڹ��� R
	OBJECT_TYPE_LOCK_YELLOW,	// �ڹ��� Y
	OBJECT_TYPE_LOCK_BLUE,		// �ڹ��� B
	OBJECT_TYPE_DOOR_RIGHT,		// �� �����ʿ� �ִ�
	OBJECT_TYPE_DOOR_LEFT,		// �� ���ʿ� �ִ�
	OBJECT_TYPE_BRIDGE_RIGHT,	// �ٸ�	�����ʿ� �ִ�
	OBJECT_TYPE_BRIDGE_LEFT,	// �ٸ� ���ʿ� �ִ�
	OBJECT_TYPE_LADDER,			// ��ٸ�
	OBJECT_TYPE_BROKENBLOCK,	// �μ����� ��

	OBJECT_TYPE_NONE,
	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE,
};

// ������Ʈ Ŭ����
class object
{
private:

	float _x;				// ������ǥ x
	float _y;				// ������ǥ y

	float _destX, _destY;	// �̹��� �׸� left, top��ǥ

	string _objName;		// ������Ʈ �̸�
	OBJECT_TYPE	_type;		// ������Ʈ Ÿ��
	int			_value;		// �������̶� ������ Ű��(ex.  KEY _value == LOCK _value >> ���� ������		
	object*		_linkObj;	// ����� ������Ʈ (ex. �ڹ���� �� or �ٸ� �� ����Ǿ�����)

	image*	_img;			// �̹���
	POINT	_size;			// ũ��
	RECT	_rc;			// �浹 ��Ʈ

	bool _isActiveFinished;	// �۵� �Ϸ��ߴ��� (ex. ���� �����ִٸ� false, �����ִٸ� true)

	animation* _ani;		// ���� �������� �ִϸ��̼�

public:
	object();
	~object();

	// ������Ʈ �̸�(Ű�ִϸ��̼ǿ��� ���), �̹��� �̸�, ������ǥ, ������ ������ ��, ������Ʈ Ÿ��
	HRESULT init(const char* objName, const char* imgName, POINTF position, int itemValue, OBJECT_TYPE type);
	void release();
	void update();
	void render();

	// �ȼ� �浹�� ���� ���� �Լ�
	void pixelRender(HDC hdc);

	// �۵�
	void active();

	// ����Ǵ� ������Ʈ�� ����
	void setLinkObject(object* obj) { _linkObj = obj; }

	// �浹ü(rect) ũ�� ����
	void setCollisionSize(POINT size);


	float getX() { return _x; }
	float getY() { return _y; }

	OBJECT_TYPE geObjectType() { return _type; }
	int			getObjectValue() { return _value; }
	RECT*		getObjectRect()
	{
		return &_rc;
	}

private:
	// ��Ʈ ����
	void MakeRect();
};

