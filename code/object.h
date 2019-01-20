#pragma once
//#include "animation.h"

// 오브젝트 타입
enum OBJECT_TYPE
{
	OBJECT_TYPE_LOCK_RED,		// 자물쇠 R
	OBJECT_TYPE_LOCK_YELLOW,	// 자물쇠 Y
	OBJECT_TYPE_LOCK_BLUE,		// 자물쇠 B
	OBJECT_TYPE_DOOR_RIGHT,		// 문 오른쪽에 있는
	OBJECT_TYPE_DOOR_LEFT,		// 문 왼쪽에 있는
	OBJECT_TYPE_BRIDGE_RIGHT,	// 다리	오른쪽에 있는
	OBJECT_TYPE_BRIDGE_LEFT,	// 다리 왼쪽에 있는
	OBJECT_TYPE_LADDER,			// 사다리
	OBJECT_TYPE_BROKENBLOCK,	// 부서지는 벽

	OBJECT_TYPE_NONE,
	OBJECT_TYPE_COUNT = OBJECT_TYPE_NONE,
};

// 오브젝트 클래스
class object
{
private:

	float _x;				// 중점좌표 x
	float _y;				// 중점좌표 y

	float _destX, _destY;	// 이미지 그릴 left, top좌표

	string _objName;		// 오브젝트 이름
	OBJECT_TYPE	_type;		// 오브젝트 타입
	int			_value;		// 아이템이랑 연동될 키값(ex.  KEY _value == LOCK _value >> 문이 열린다		
	object*		_linkObj;	// 연결된 오브젝트 (ex. 자물쇠랑 문 or 다리 는 연결되어있음)

	image*	_img;			// 이미지
	POINT	_size;			// 크기
	RECT	_rc;			// 충돌 렉트

	bool _isActiveFinished;	// 작동 완료했는지 (ex. 문이 닫혀있다면 false, 열려있다면 true)

	animation* _ani;		// 현재 실행중인 애니메이션

public:
	object();
	~object();

	// 오브젝트 이름(키애니메이션에서 사용), 이미지 이름, 중점좌표, 연동될 아이템 값, 오브젝트 타입
	HRESULT init(const char* objName, const char* imgName, POINTF position, int itemValue, OBJECT_TYPE type);
	void release();
	void update();
	void render();

	// 픽셀 충돌을 위한 렌더 함수
	void pixelRender(HDC hdc);

	// 작동
	void active();

	// 연결되는 오브젝트를 연결
	void setLinkObject(object* obj) { _linkObj = obj; }

	// 충돌체(rect) 크기 세팅
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
	// 렉트 생성
	void MakeRect();
};

