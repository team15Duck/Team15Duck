#pragma once


#define PI 3.141592f
#define PI2 2 * PI

//������ �̹��� ȸ���� ���� ������
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

//float �� ����Ʈ ����
typedef struct tagPointFloatInfo
{
	float x;
	float y;
}POINTF, *PPOINTF;
//��
typedef struct tagELLIPSE
{
	POINTF p;
	float r;
} ELLIPSE, *LPELLIPSE;

namespace TEAM_15DUCK_UTILL
{
	POINT PointMake(int x, int y);

	POINTF PointFMake(float x, float y);

	void LineMake(HDC hdc, int startX, int startY, int endX, int endY, bool isAbsolut = true);

	void LineMake(HDC hdc, POINTF start, POINTF end, bool isAbsolut = true);


	//================= ��Ʈ ���� �Լ� ========================
	//    ��Ʈ�� �����(����Ʈ, ž, ����ũ��, ����ũ��)
	RECT RectMake(int x, int y, int width, int height);
	//    ��Ʈ�� �����(����X��ǥ, ����Y��ǥ, ����ũ��, ����ũ��)
	RECT RectMakeCenter(int x, int y, int width, int height);
	//================= �簢�� ���� �Լ� ======================
	//          �簢�� �����Լ�(�ѷ���DC, left, top, ����ũ��, ����ũ��, ������ǥ�� �׸��°�
	void RectangleMake(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);

	void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);

	void Rectangle(HDC hdc, RECT& rc, bool isAbsolut = true);

	//====================== �� �� �� �� ���� ===============================
	//        �� �����Լ� (hdc, left, top, ����ũ��, ����ũ��)
	ELLIPSE EllipseMake(float x, float y, float r);
	//        �� �����Լ� (hdc, ������ǥ X, ������ǥ Y, ����ũ��, ����ũ��) //Ÿ������
	void EllipseCenterRender(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);
	//        �� �׸�
	void EllipseRender(HDC hdc, ELLIPSE& e, bool isAbsolut = true);
	//���� ������ ��׸���
	float RadToDeg(float angle);

	//��׸� ������ ��������
	float DegToRad(float angle);

	//�Ÿ����ϱ�
	float getDistance(float x1, float y1, float x2, float y2);
	float getDistance(POINTF& p1, POINTF& p2);
	
	//���浹�ߴ���
	bool EllipseCollision(ELLIPSE& e1, ELLIPSE& e2);

	//�������ϱ�
	float getCenter(float a, float b);

	//��Ʈ ���� ��ȯ�Լ�
	POINT getRectCenter(RECT& rc);

	//��Ʈ x���� ��ȯ �Լ�
	float getRectXCenter(RECT& rc);
	
	//��Ʈ y���� ��ȯ �Լ�
	float getRectYCenter(RECT& rc);

	//��Ʈ width ��ȯ �Լ�
	float getRectWidth(RECT& rc);

	//��Ʈ height ��ȯ �Լ�
	float getRectHeight(RECT& rc);

	//�� �� �浹
	bool PtInEllipse(ELLIPSE& e, POINTF p);

	//�� �� �浹
	bool PtInEllipse(ELLIPSE& e, float x, float y);

	//��׸� �ڻ���
	float dCosf(float angle);

	//��׸� ����
	float dSinf(float angle);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ����
	float getAngle(POINTF p, POINTF target);

	float getAngle(float x, float y, float x2, float y2);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ����
	float getAngle2(POINTF p, POINTF target);

	float getAngle2(float x, float y, float x2, float y2);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ��׸�
	float dGetAngle(POINTF target, POINTF p);

	float dGetAngle(float x2, float y2, float x, float y);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ��׸�
	float dGetAngle2(POINTF target, POINTF p);

	float dGetAngle2(float x2, float y2, float x, float y);

	//�� �簢�� �浹
	bool RectEllipseCollition(RECT& rc, ELLIPSE& e);

	//��Ʈ ��ĥ
	void RectangleBrush(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	void RectangleBrushPen(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	void RectanglePen(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	//����ĥ
	void EllipseBrush(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

	void EllipseBrushPen(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

	void EllipsePen(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

}