#pragma once
#include "item.h"
#include <vector>

class itemManager
{
private:
	vector<item*> _vFieldItems;		// 필드에 있는 아이템들

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// 플레이어가 아이템 획득 : 필드에서 해당 아이템 삭제
	void obtainItem(item* targetItem);

	// 필드 아이템 리스트(벡터) GET
	vector<item*> getFieldItems() { return _vFieldItems; }
};