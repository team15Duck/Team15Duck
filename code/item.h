#pragma once

enum ITEM_TYPE
{
	ITEM_TYPE_FRUIT_SMALL,	// 과일
	ITEM_TYPE_FRUIT_BIG,	// 과일
	ITEM_TYPE_MEAT,			// 고기
	ITEM_TYPE_SHIELD,		// 실드
	ITEM_TYPE_KEY_RED,		// 열쇠
	ITEM_TYPE_KEY_YELLOW,	// 열쇠
	ITEM_TYPE_KEY_BLUE,		// 열쇠
	ITEM_TYPE_LOCK_RED,		// 자물쇠
	ITEM_TYPE_LOCK_YELLOW,	// 자물쇠
	ITEM_TYPE_LOCK_BLUE,	// 자물쇠

	ITEM_TYPE_NONE,
	ITEM_TYPE_COUNT = ITEM_TYPE_NONE,
};

class item
{
private:

	float _x;				// 중점좌표
	float _y;

	float _destX, _destY;	// 이미지 그릴 left, top좌표

	ITEM_TYPE	_type;		// 아이템 타입
	int			_value;		// 능력치(ex.  FRUIT _value = 1 : hp를 1 채워줌
							//			   MEAT  _value = 2 : hp를 2 채워줌
							//			    KEY _value == LOCK _value >> 문이 열린다		

	image*	_img;			// 이미지
	POINT	_size;			// 크기
	RECT	_rc;			// 충돌 렉트

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
	// 렉트 생성
	void MakeRect();
};

