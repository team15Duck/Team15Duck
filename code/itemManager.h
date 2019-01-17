#pragma once
#include "item.h"
#include <vector>

class itemManager
{
private:
	vector<item*> _vFieldItems;		// �ʵ忡 �ִ� �����۵�

public:
	itemManager();
	~itemManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// �÷��̾ ������ ȹ�� : �ʵ忡�� �ش� ������ ����
	void obtainItem(item* targetItem);

	// �ʵ� ������ ����Ʈ(����) GET
	vector<item*> getFieldItems() { return _vFieldItems; }
};