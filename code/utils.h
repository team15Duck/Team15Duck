#pragma once


#define PI 3.141592f
#define PI2 2 * PI

//프레임 이미지 회전을 위한 각도값
#define PI8		float(PI / 8.0f)
#define PI16	float(PI / 16.0f)
#define PI32	float(PI / 32.0f)
#define PI64	float(PI / 64.0f)
#define PI128	float(PI / 128.0f)

//float 형 포인트 변수
typedef struct tagPointFloatInfo
{
	float x;
	float y;
}POINTF, *PPOINTF;
//원
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


	//================= 렉트 관련 함수 ========================
	//    렉트를 만든다(레프트, 탑, 가로크기, 세로크기)
	RECT RectMake(int x, int y, int width, int height);
	//    렉트를 만든다(중점X좌표, 중점Y좌표, 가로크기, 세로크기)
	RECT RectMakeCenter(int x, int y, int width, int height);
	//================= 사각형 관련 함수 ======================
	//          사각형 생성함수(뿌려줄DC, left, top, 가로크기, 세로크기, 절대좌표에 그리는가
	void RectangleMake(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);

	void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);

	void Rectangle(HDC hdc, RECT& rc, bool isAbsolut = true);

	//====================== 동 그 라 미 관련 ===============================
	//        원 생성함수 (hdc, left, top, 가로크기, 세로크기)
	ELLIPSE EllipseMake(float x, float y, float r);
	//        원 생성함수 (hdc, 센터좌표 X, 센터좌표 Y, 가로크기, 세로크기) //타원가능
	void EllipseCenterRender(HDC hdc, int x, int y, int width, int height, bool isAbsolut = true);
	//        원 그림
	void EllipseRender(HDC hdc, ELLIPSE& e, bool isAbsolut = true);
	//라디안 각도를 디그리로
	float RadToDeg(float angle);

	//디그리 각도를 라디안으로
	float DegToRad(float angle);

	//거리구하기
	float getDistance(float x1, float y1, float x2, float y2);
	float getDistance(POINTF& p1, POINTF& p2);
	
	//원충돌했는지
	bool EllipseCollision(ELLIPSE& e1, ELLIPSE& e2);

	//중점구하기
	float getCenter(float a, float b);

	//렉트 중점 반환함수
	POINT getRectCenter(RECT& rc);

	//렉트 x중점 반환 함수
	float getRectXCenter(RECT& rc);
	
	//렉트 y중점 반환 함수
	float getRectYCenter(RECT& rc);

	//렉트 width 반환 함수
	float getRectWidth(RECT& rc);

	//렉트 height 반환 함수
	float getRectHeight(RECT& rc);

	//원 점 충돌
	bool PtInEllipse(ELLIPSE& e, POINTF p);

	//원 점 충돌
	bool PtInEllipse(ELLIPSE& e, float x, float y);

	//디그리 코사인
	float dCosf(float angle);

	//디그리 사인
	float dSinf(float angle);

	//원두개 박아서 각도받아오기 아크탄젠트 반환형 라디안
	float getAngle(POINTF p, POINTF target);

	float getAngle(float x, float y, float x2, float y2);

	//원 두개 박아서 각도받아오기 아크코사인 반환형 라디안
	float getAngle2(POINTF p, POINTF target);

	float getAngle2(float x, float y, float x2, float y2);

	//원두개 박아서 각도받아오기 아크탄젠트 반환형 디그리
	float dGetAngle(POINTF target, POINTF p);

	float dGetAngle(float x2, float y2, float x, float y);

	//원 두개 박아서 각도받아오기 아크코사인 반환형 디그리
	float dGetAngle2(POINTF target, POINTF p);

	float dGetAngle2(float x2, float y2, float x, float y);

	//원 사각형 충돌
	bool RectEllipseCollition(RECT& rc, ELLIPSE& e);

	//렉트 색칠
	void RectangleBrush(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	void RectangleBrushPen(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	void RectanglePen(HDC hdc, RECT& rc, COLORREF color, bool isAbsolut = true);

	//원색칠
	void EllipseBrush(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

	void EllipseBrushPen(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

	void EllipsePen(HDC hdc, ELLIPSE& e, COLORREF color, bool isAbsolut = true);

}