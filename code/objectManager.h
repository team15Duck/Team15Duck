#pragma once
#include "object.h"
#include "item.h"
#include <vector>

class objectManager
{
private:
	vector<object*> _vFieldObjects;		// �ʵ忡 �ִ� ������Ʈ��

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	void interactionObjectWithItem(item* useItem);	//�������� ������ ������Ʈ�� ��ȣ�ۿ� ex: ������ ���(�ڹ���� ���� �������� �־�� ���)

	vector<object*> getFieldObjects() { return _vFieldObjects; }

private:
	void doActiveObject(object* obj);	// ������Ʈ �۵�
};

