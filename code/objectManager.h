#pragma once
#include "object.h"
#include "item.h"
#include <vector>

class objectManager
{
private:
	vector<object*> _vFieldObjects;		// 필드에 있는 오브젝트들

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void interactionObjectWithItem(item* useItem);	//아이템을 가지고 오브젝트와 상호작용 ex: 아이템 사용(자물쇠는 열쇠 아이템이 있어야 사용)

	vector<object*> getFieldObjects() { return _vFieldObjects; }

private:
	void doActiveObject(object* obj);	// 오브젝트 작동
};

