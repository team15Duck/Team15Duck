#pragma once
#include "object.h"
#include "item.h"
#include <vector>

// 필드에 뿌려져있는 오브젝트들을 관리하는 클래스
class objectManager
{
private:
	vector<object*> _vFieldObjects;		// 필드에 있는 오브젝트들
	vector<object*> _vFieldLadders;		// 필드에 있는 사다리들

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 픽셀 충돌을 위한 렌더 함수
	void objectPixelRender(HDC hdc);				

	// 아이템을 가지고 오브젝트와 상호작용 ex: 아이템 사용(자물쇠는 열쇠 아이템이 있어야 사용)
	// 사용이 되면 return true, 그렇지 않다면 false
	bool interactionObjectWithItem(item* useItem);	

	// 필드에 있는 오브젝트들
	vector<object*> getFieldObjects() { return _vFieldObjects; }
	
	// 필드에 있는 사다리들
	vector<object*> getFieldLadders() { return _vFieldLadders; }

private:
	// 오브젝트 작동 : 외부에서 사용할 함수가 아니므로 private
	void doActiveObject(object* obj);	
};

