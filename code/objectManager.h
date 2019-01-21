#pragma once
#include "object.h"
#include "item.h"
#include <vector>

// �ʵ忡 �ѷ����ִ� ������Ʈ���� �����ϴ� Ŭ����
class objectManager
{
private:
	vector<object*> _vFieldObjects;		// �ʵ忡 �ִ� ������Ʈ��
	vector<object*> _vFieldLadders;		// �ʵ忡 �ִ� ��ٸ���

public:
	objectManager();
	~objectManager();

	HRESULT init();
	void release();
	void update();
	void render();

	// �ȼ� �浹�� ���� ���� �Լ�
	void objectPixelRender(HDC hdc);				

	// ������Ʈ ���
	// ���� �������� ����ؾ� �ϴ� ������Ʈ��� �÷��̾�� �����۰� ������Ʈ�� value���� Ȯ���ϰ� ���� ��ġ�Ѵٸ� �� �Լ��� ȣ�����ּ���
	// ������ ���� ����ϴ� ��쿡�� �׳� ȣ�����ּ���
	void interactionObject(object* obj);

	// �ʵ忡 �ִ� ������Ʈ��
	vector<object*> getFieldObjects() { return _vFieldObjects; }
	
	// �ʵ忡 �ִ� ��ٸ���
	vector<object*> getFieldLadders() { return _vFieldLadders; }

private:
	// ������Ʈ �۵� : �ܺο��� ����� �Լ��� �ƴϹǷ� private
	void doActiveObject(object* obj);	
};

