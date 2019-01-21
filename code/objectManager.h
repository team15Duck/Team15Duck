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

	// 오브젝트 사용
	// 만약 아이템을 사용해야 하는 오브젝트라면 플레이어에서 아이템과 오브젝트의 value값을 확인하고 값이 일치한다면 이 함수를 호출해주세요
	// 아이템 없이 사용하는 경우에는 그냥 호출해주세요
	void interactionObject(object* obj);

	// 필드에 있는 오브젝트들
	vector<object*> getFieldObjects() { return _vFieldObjects; }
	
	// 필드에 있는 사다리들
	vector<object*> getFieldLadders() { return _vFieldLadders; }

private:
	// 오브젝트 작동 : 외부에서 사용할 함수가 아니므로 private
	void doActiveObject(object* obj);	
};

