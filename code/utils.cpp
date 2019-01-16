#include "stdafx.h"
#include "utils.h"


namespace TEAM_15DUCK_UTILL
{
	POINT PointMake(int x, int y)
	{
		POINT pt = { x, y };

		return pt;
	}
	POINTF PointFMake(float x, float y)
	{
		POINTF pt = { x, y };

		return pt;
	}
	void LineMake(HDC hdc, int startX, int startY, int endX, int endY)
	{
		MoveToEx(hdc, startX, startY, NULL);
		LineTo(hdc, endX, endY);
	}
	void LineMake(HDC hdc, POINTF start, POINTF end)
	{
		MoveToEx(hdc, start.x, start.y, NULL);
		LineTo(hdc, end.x, end.y);
	}
	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x, y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
		return rc;
	}
	void RectangleMake(HDC hdc, int x, int y, int width, int height)
	{
		Rectangle(hdc, x, y, x + width, y + height);
	}
	void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
	{
		Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
	}
	void Rectangle(HDC hdc, RECT & rc)
	{
		Rectangle(hdc, rc.left, rc.top, rc.right, rc.bottom);
	}
	ELLIPSE EllipseMake(float x, float y, float r)
	{
		ELLIPSE rt;
		rt.p.x = x;
		rt.p.y = y;
		rt.r = r;
		return rt;
	}
	void EllipseCenterRender(HDC hdc, int x, int y, int width, int height)
	{
		Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
	}
	void EllipseRender(HDC hdc, ELLIPSE & e)
	{
		Ellipse(hdc, e.p.x - e.r, e.p.y - e.r, e.p.x + e.r, e.p.y + e.r);
	}
	float RadToDeg(float angle)
	{
		return angle * (180.0f / PI);
	}
	float DegToRad(float angle)
	{
		return angle * (PI / 180.0f);
	}
	//거리 구하는 함수
	float getDistance(float x1, float y1, float x2, float y2)
	{
		float x = x2 - x1;
		float y = y2 - y1;

		return sqrtf(x * x + y * y);
	}

	float getDistance(POINTF & p1, POINTF & p2)
	{
		return sqrtf((p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y));
	}

	bool EllipseCollision(ELLIPSE & e1, ELLIPSE & e2)
	{
		return (e1.r + e2.r >= getDistance(e1.p, e2.p));
	}

	float getCenter(float a, float b)
	{
		return a + (b - a) / 2;
	}

	POINT getRectCenter(RECT & rc)
	{
		POINT p;
		p.x = getCenter(rc.left, rc.right);
		p.y = getCenter(rc.top, rc.bottom);
		return p;
	}

	float getRectXCenter(RECT & rc)
	{
		return getCenter(rc.left, rc.right);
	}

	float getRectYCenter(RECT & rc)
	{
		return getCenter(rc.top, rc.bottom);
	}

	float getRectWidth(RECT & rc)
	{
		return rc.right - rc.left;
	}

	float getRectHeight(RECT & rc)
	{
		return rc.bottom - rc.top;
	}

	bool PtInEllipse(ELLIPSE & e, POINTF p)
	{
		return (e.r >= getDistance(e.p, p));
	}

	bool PtInEllipse(ELLIPSE & e, float x, float y)
	{
		return (e.r >= getDistance(e.p.x, e.p.y, x, y));
	}

	float dCosf(float angle)
	{
		return cosf(DegToRad(angle));
	}

	float dSinf(float angle)
	{
		return sinf(DegToRad(angle));
	}

	float getAngle(POINTF p, POINTF target)
	{
		return -atan2f(target.y - p.y, target.x - p.x);
	}

	float getAngle(float x, float y, float x2, float y2)
	{
		return -atan2f(y2 - y, x2 - x);
	}

	float getAngle2(POINTF p, POINTF target)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float getAngle2(float x, float y, float x2, float y2)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
			if (angle > 2 * PI) angle -= 2 * PI;
		}
		return angle;
	}

	float dGetAngle(POINTF target, POINTF p)
	{
		return RadToDeg(-atan2f(target.y - p.y, target.x - p.x));
	}

	float dGetAngle(float x2, float y2, float x, float y)
	{
		return RadToDeg(-atan2f(y2 - y, x2 - x));
	}

	float dGetAngle2(POINTF target, POINTF p)
	{
		float angle;
		float deltaX = target.x - p.x;
		float deltaY = target.y - p.y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	float dGetAngle2(float x2, float y2, float x, float y)
	{
		float angle;
		float deltaX = x2 - x;
		float deltaY = y2 - y;
		float distance = sqrtf(deltaX* deltaX + deltaY * deltaY);
		angle = acosf(deltaX / distance);
		if (deltaY < 0)
		{
			angle = 2 * PI - angle;
		}
		return RadToDeg(angle);
	}

	bool RectEllipseCollition(RECT & rc, ELLIPSE & e)
	{
		if ((rc.left <= e.p.x && e.p.x <= rc.right) || (rc.top <= e.p.y && e.p.y <= rc.bottom))
		{
			POINT p;
			p.x = e.p.x;
			p.y = e.p.y;
			RECT rc2 = { rc.left - e.r, rc.top - e.r, rc.right + e.r, rc.bottom + e.r };
			if (PtInRect(&rc2, p))return true;
		}
		else
		{
			POINTF p;
			p.x = rc.left;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.left;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.top;
			if (PtInEllipse(e, p)) return true;
			p.x = rc.right;
			p.y = rc.bottom;
			if (PtInEllipse(e, p)) return true;
		}
		return false;
	}

	void RectangleBrush(HDC hdc, RECT & rc, COLORREF color)
	{
		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
		Rectangle(hdc, rc);
		SelectObject(hdc, oBrush);
		DeleteObject(brush);
	}

	void RectangleBrushPen(HDC hdc, RECT & rc, COLORREF color)
	{
		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, color);
		HPEN oPen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, rc);
		SelectObject(hdc, oBrush);
		DeleteObject(brush);
		SelectObject(hdc, oPen);
		DeleteObject(pen);
	}

	void RectanglePen(HDC hdc, RECT & rc, COLORREF color)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, color);
		HPEN oPen = (HPEN)SelectObject(hdc, pen);
		Rectangle(hdc, rc);
		SelectObject(hdc, oPen);
		DeleteObject(pen);
	}

	void EllipseBrush(HDC hdc, ELLIPSE & e, COLORREF color)
	{
		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
		EllipseRender(hdc, e);
		SelectObject(hdc, oBrush);
		DeleteObject(brush);
	}

	void EllipseBrushPen(HDC hdc, ELLIPSE & e, COLORREF color)
	{
		HBRUSH brush = CreateSolidBrush(color);
		HBRUSH oBrush = (HBRUSH)SelectObject(hdc, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, color);
		HPEN oPen = (HPEN)SelectObject(hdc, pen);
		EllipseRender(hdc, e);
		SelectObject(hdc, oBrush);
		DeleteObject(brush);
		SelectObject(hdc, oPen);
		DeleteObject(pen);
	}

	void EllipsePen(HDC hdc, ELLIPSE & e, COLORREF color)
	{
		HPEN pen = CreatePen(PS_SOLID, 1, color);
		HPEN oPen = (HPEN)SelectObject(hdc, pen);
		EllipseRender(hdc, e);
		SelectObject(hdc, oPen);
		DeleteObject(pen);
	}

}