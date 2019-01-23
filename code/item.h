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

	ITEM_TYPE_NONE,
	ITEM_TYPE_COUNT = ITEM_TYPE_NONE,
};

class item
{
private:

	float _x;				// ������ǥ x
	float _y;				// ������ǥ y

	float _destX, _destY;	// �̹��� �׸� left, top��ǥ

	ITEM_TYPE	_type;		// ������ Ÿ��
	int			_value;		// �ɷ�ġ(ex.  FRUIT _value = 1 : hp�� 1 ä����
							//			   MEAT  _value = 2 : hp�� 2 ä����
							//			    KEY _value == LOCK _value >> ���� ������		

	image*	_img;			// �̹���
	POINT	_size;			// ũ��
	RECT	_rc;			// �浹 ��Ʈ

	bool _isRender;			// ���� ���ΰ�

public:
	item();
	~item();

	// �̹��� �̸�, ������ǥ, ������ ��, ������ Ÿ��
	HRESULT init(const char* imgName, POINTF position, int itemValue, ITEM_TYPE type);
	void release();
	void update();
	void render();

	ITEM_TYPE getItemType() { return _type;		}
	int		  getItemValue(){ return _value;	}
	RECT	  getItemRect()	{ return _rc;		}
	bool	  getIsRender() { return _isRender; }
	
	// ���� ���� ����
	void	  setIsRender(bool render) { _isRender = render; }

	float getX() { return _x; }
	void setX(float x) { _x = x; }
	float getY() { return _y; }
	void setY(float y) { _y = y; }
};

