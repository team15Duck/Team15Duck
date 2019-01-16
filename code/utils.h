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
	inline POINT PointMake(int x, int y);

	inline POINTF PointFMake(float x, float y);

	inline void LineMake(HDC hdc, int startX, int startY, int endX, int endY);

	inline void LineMake(HDC hdc, POINTF start, POINTF end);


	//================= ��Ʈ ���� �Լ� ========================
	//    ��Ʈ�� �����(����Ʈ, ž, ����ũ��, ����ũ��)
	inline RECT RectMake(int x, int y, int width, int height);
	//    ��Ʈ�� �����(����X��ǥ, ����Y��ǥ, ����ũ��, ����ũ��)
	inline RECT RectMakeCenter(int x, int y, int width, int height);
	//================= �簢�� ���� �Լ� ======================
	//          �簢�� �����Լ�(�ѷ���DC, left, top, ����ũ��, ����ũ��
	inline void RectangleMake(HDC hdc, int x, int y, int width, int height);

	inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height);

	inline void Rectangle(HDC hdc, RECT& rc);

	//====================== �� �� �� �� ���� ===============================
	//        �� �����Լ� (hdc, left, top, ����ũ��, ����ũ��)
	inline ELLIPSE EllipseMake(float x, float y, float r);
	//        �� �����Լ� (hdc, ������ǥ X, ������ǥ Y, ����ũ��, ����ũ��) //Ÿ������
	inline void EllipseCenterRender(HDC hdc, int x, int y, int width, int height);
	//        �� �׸�
	inline void EllipseRender(HDC hdc, ELLIPSE& e);
	//���� ������ ��׸���
	inline float RadToDeg(float angle);

	//��׸� ������ ��������
	inline float DegToRad(float angle);

	//�Ÿ����ϱ�
	float getDistance(float x1, float y1, float x2, float y2);
	inline float getDistance(POINTF& p1, POINTF& p2);
	
	//���浹�ߴ���
	inline bool EllipseCollision(ELLIPSE& e1, ELLIPSE& e2);

	//�������ϱ�
	inline float getCenter(float a, float b);

	//��Ʈ ���� ��ȯ�Լ�
	inline POINT getRectCenter(RECT& rc);

	//��Ʈ x���� ��ȯ �Լ�
	inline float getRectXCenter(RECT& rc);
	
	//��Ʈ y���� ��ȯ �Լ�
	inline float getRectYCenter(RECT& rc);

	//��Ʈ width ��ȯ �Լ�
	inline float getRectWidth(RECT& rc);

	//��Ʈ height ��ȯ �Լ�
	inline float getRectHeight(RECT& rc);

	//�� �� �浹
	inline bool PtInEllipse(ELLIPSE& e, POINTF p);

	//�� �� �浹
	inline bool PtInEllipse(ELLIPSE& e, float x, float y);

	//��׸� �ڻ���
	inline float dCosf(float angle);

	//��׸� ����
	inline float dSinf(float angle);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ����
	inline float getAngle(POINTF p, POINTF target);

	inline float getAngle(float x, float y, float x2, float y2);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ����
	inline float getAngle2(POINTF p, POINTF target);

	inline float getAngle2(float x, float y, float x2, float y2);

	//���ΰ� �ھƼ� �����޾ƿ��� ��ũź��Ʈ ��ȯ�� ��׸�
	inline float dGetAngle(POINTF target, POINTF p);

	inline float dGetAngle(float x2, float y2, float x, float y);

	//�� �ΰ� �ھƼ� �����޾ƿ��� ��ũ�ڻ��� ��ȯ�� ��׸�
	inline float dGetAngle2(POINTF target, POINTF p);

	inline float dGetAngle2(float x2, float y2, float x, float y);

	//�� �簢�� �浹
	inline bool RectEllipseCollition(RECT& rc, ELLIPSE& e);

	//��Ʈ ��ĥ
	inline void RectangleBrush(HDC hdc, RECT& rc, COLORREF color);

	inline void RectangleBrushPen(HDC hdc, RECT& rc, COLORREF color);

	inline void RectanglePen(HDC hdc, RECT& rc, COLORREF color);

	//����ĥ
	inline void EllipseBrush(HDC hdc, ELLIPSE& e, COLORREF color);

	inline void EllipseBrushPen(HDC hdc, ELLIPSE& e, COLORREF color);

	inline void EllipsePen(HDC hdc, ELLIPSE& e, COLORREF color);

}