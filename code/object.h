#pragma once
//#include "animation.h"

enum OBJECT_TYPE
{
	OBJECT_TYPE_LOCK_RED,		// 자물쇠 R
	OBJECT_TYPE_LOCK_YELLOW,	// 자물쇠 Y
	OBJECT_TYPE_LOCK_BLUE,		// 자물쇠 B
	OBJECT_TYPE_DOOR_RIGHT,		// 문 오른쪽에 있는
	OBJECT_TYPE_DOOR_LEFT,		// 문 왼쪽에 있는
	OBJECT_TYPE_BRIDGE_RIGHT,	// 다리	오른쪽에 있는
	OBJECT_TYPE_BRIDGE_LEFT,	// 다리 왼쪽에 있는

	OBJECT_TYPE_NONE,
	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE,
};

class object
{
private:

	float _x;				// 중점좌표
	float _y;

	float _destX, _destY;	// 이미지 그릴 left, top좌표

	OBJECT_TYPE	_type;		// 오브젝트 타입
	int			_value;		// 아이템이랑 연동될 키값(ex.  KEY _value == LOCK _value >> 문이 열린다		
	object*		_linkObj;	// 연결된 오브젝트 (ex. 자물쇠랑 문 or 다리 는 연결되어있음)

	image*	_img;			// 이미지
	POINT	_size;			// 크기
	RECT	_rc;			// 충돌 렉트

	bool _isActiveFinished;	// 작동 완료했는지 (ex. 문이 닫혀있다면 false, 열려있다면 true)

	int _frameX;
	int _frameY;

	string _objName;		// 오브젝트 이름

	animation* _ani;

public:
	object();
	~object();

	HRESULT init(const char* objName, const char* imgName, POINTF position, int itemValue, OBJECT_TYPE type);
	void release();
	void update();
	void render();


	// 작동
	void active();
	//void endActive();

	// 연결되는 오브젝트 연결
	void setLinkObject(object* obj) { _linkObj = obj; }

	OBJECT_TYPE getItemType() { return _type;	}
	int			getItemValue(){ return _value;	}
	RECT		getItemRect() { return _rc;		}

private:
	// 렉트 생성
	void MakeRect();
};

