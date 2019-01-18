#pragma once

#include "singletonBase.h"
#include "image.h"
#include <map> //사실 안해도 되는데 선언해봄 ㅋ _ㅋ

class imageManager : public singletonBase<imageManager>
{
private:
	//map<string, image*> <-- 얘를          mapImageList라 부르겠다.
	typedef map<string, image*>				mapImageList;
	typedef map<string, image*>::iterator	mapImageIter;

private:
	mapImageList _mImageList;


public:
	imageManager();
	~imageManager();

	HRESULT init();
	void release();

	image* addImage(string strKey, int width, int height);
	image* addImage(string strKey, const char* fileName, int width, int height, bool trans, COLORREF transColor, BOOL alpha = FALSE);
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool trans, COLORREF transColor, BOOL alpha = FALSE);

	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha = FALSE);
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool trans, COLORREF transColor, BOOL alpha = FALSE);

	//이미지를 찾는 함수
	image* findImage(string strKey);

	//싱글톤화 되어있는 이미지 지워주는 함쓔
	BOOL deleteImage(string strKey);

	//싸그리..
	BOOL deleteAll();

	void render(string strKey, HDC hdc);
	void render(string strKey, HDC hdc, int destX, int destY);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight);

	//오늘 과제 1. 프레임렌더 함수를 완성시켜보자 *^^* 3분컷가능

	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY);

	void alphaRender(string strKey, HDC hdc, BYTE alpha);

	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);

	void alphaRender(string strKey, HDC hdc, int destX, int destY,
		int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha);

	//이미지 프레임 렌더(뿌려줄 DC, 뿌려줄 X(Left), Y(Top))
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha);
	//이미지 프레임 렌더(뿌려줄 DC, 뿌려줄 Left, 뿌려줄 Top, 프레임X번호, 프레임Y번호)
	void alphaFrameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha);
	//이미지 한 장으로 루프렌더링하기(뿌려줄DC, 뿌려줄영역(렉트), 루프방향X, 루프방향Y)
	void alphaLoopRender(string strKey, HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha);

	void aniRender(string strKey, HDC hdc, int destX, int destY, animation* ani);
};

