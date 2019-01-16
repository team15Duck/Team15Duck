#pragma once
#include "item.h"
#include <vector>

class itemManager
{
private:
	vector<item*> _vFieldItems;

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	vector<item*> getFieldItems() { return _vFieldItems; }
};