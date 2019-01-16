#pragma once

enum ITEM_TYPE
{
	ITEM_TYPE_FRUIT_SMALL,	// ����
	ITEM_TYPE_FRUIT_BIG,	// ����
	ITEM_TYPE_MEAT,			// ���
	ITEM_TYPE_SHIELD,		// �ǵ�
	ITEM_TYPE_KEY_RED,		// ����
	ITEM_TYPE_KEY_YELLOW,	// ����
	ITEM_TYPE_KEY_BLUE,		// ����
	ITEM_TYPE_LOCK_RED,		// �ڹ���
	ITEM_TYPE_LOCK_YELLOW,	// �ڹ���
	ITEM_TYPE_LOCK_BLUE,	// �ڹ���

	ITEM_TYPE_NONE,
	ITEM_TYPE_COUNT = ITEM_TYPE_NONE,
};

class item
{
private:

	float _x;				// ������ǥ
	float _y;

	float _destX, _destY;	// �̹��� �׸� left, top��ǥ

	ITEM_TYPE	_type;		// ������ Ÿ��
	int			_value;		// �ɷ�ġ(ex.  FRUIT _value = 1 : hp�� 1 ä����
							//			   MEAT  _value = 2 : hp�� 2 ä����
							//			    KEY _value == LOCK _value >> ���� ������		

	image*	_img;			// �̹���
	POINT	_size;			// ũ��
	RECT	_rc;			// �浹 ��Ʈ

public:
	item();
	~item();

	HRESULT init(const char* imgName, POINTF position, int itemValue, ITEM_TYPE type);
	void release();
	void update();
	void render();

	ITEM_TYPE getItemType() { return _type;	 }
	int getItemValue()		{ return _value; }
	RECT getItemRect()		{ return _rc;	 }

private:
	// ��Ʈ ����
	void MakeRect();
};

