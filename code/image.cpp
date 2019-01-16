#include "stdafx.h"
#include "image.h"

//�����Ϸ� ���ñ� (�� ���̺귯�� ������ msImg32 ���̺귯��)
#pragma comment(lib, "msimg32.lib")

image::image()
	: _imageInfo(NULL), _fileName(NULL),
	_trans(FALSE), _transColor(RGB(0, 0, 0))
{
}


image::~image()
{
}

HRESULT image::init(int width, int height, BOOL alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}



	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const DWORD resID, int width, int height, BOOL trans, COLORREF transColor, BOOL alpha)
{
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_RESOURCE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = 0;
	_imageInfo->y = 0;
	_imageInfo->width = width;
	_imageInfo->height = height;

	_fileName = NULL;

	_trans = FALSE;
	_transColor = RGB(0, 0, 0);

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}

	if (_imageInfo->hBit == 0)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, BOOL trans, COLORREF transColor, BOOL alpha)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, BOOL trans, COLORREF transColor, BOOL alpha)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;



	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}


	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, float x, float y, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL alpha)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x - (width / 2);
	_imageInfo->y = y - (height / 2);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char * fileName, int width, int height, int frameX, int frameY, BOOL trans, COLORREF transColor, BOOL alpha)
{
	//�����̸��� ������ ������  �����
	if (fileName == NULL) return E_FAIL;

	//�̹��� ������ �ʱ�ȭ �Ǿ����� ������ �����ض�
	if (_imageInfo != NULL) release();

	HDC hdc = GetDC(_hWnd);

	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->resID = 0;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);	//�� DC������ �ϳ� ��������
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->currentFrameX = 0;
	_imageInfo->currentFrameY = 0;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;

	int len = strlen(fileName);

	//���ϰ�� �� �̸��� �޾ƿ´�
	_fileName = new CHAR[len + 1];
	strcpy_s(_fileName, len + 1, fileName);

	//Ư��Į�� ���ܿ��θ� ����.
	_trans = trans;
	_transColor = transColor;

	//���ĺ��� ������.
	//���� + ġ���̴� �����ؼ� ����
	_alpha = alpha;
	if (_alpha)
	{
		_blendFunc.BlendFlags = 0;
		_blendFunc.AlphaFormat = 0;
		_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

		_blendImage = new IMAGE_INFO;
		_blendImage->loadType = LOAD_EMPTY;
		_blendImage->resID = 0;
		_blendImage->hMemDC = CreateCompatibleDC(hdc);
		_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
		_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
		_blendImage->width = width;
		_blendImage->height = height;
		if (_blendImage->hBit == NULL)
		{
			alphaRelease();

			return E_FAIL;
		}
	}

	if (_imageInfo->hBit == NULL)
	{
		release();

		return E_FAIL;
	}

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

void image::release()
{
	if (_imageInfo)
	{
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);

		//�� init�Լ��� ���ĺ��� ó���� �̹����� �Ҵ�ǰ� �ֱ� ������
		//���� ����������մϴ�!!!!!!!!!!!!!!!


		SAFE_DELETE(_imageInfo);
		SAFE_DELETE(_fileName);


		_trans = false;
		_transColor = FALSE;
	}
	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
		_alpha = FALSE;
	}
}

void image::alphaRelease()
{
	if (_blendImage)
	{
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);
		SAFE_DELETE(_blendImage);
		_alpha = FALSE;
	}
}

void image::setTransColor(BOOL trans, COLORREF transColor)
{
	_trans = trans;
	_transColor = transColor;
}

HRESULT image::setAlpha(BOOL alpha)
{
	_alpha = alpha;
	if (_alpha)
	{
		if (_blendImage) return S_OK;
		else
		{
			if (_alpha)
			{
				HDC hdc = GetDC(_hWnd);
				_blendFunc.BlendFlags = 0;
				_blendFunc.AlphaFormat = 0;
				_blendFunc.BlendOp = AC_SRC_OVER;	//<-- �̰� �� �� �����غ����� ������

				_blendImage = new IMAGE_INFO;
				_blendImage->loadType = LOAD_EMPTY;
				_blendImage->resID = 0;
				_blendImage->hMemDC = CreateCompatibleDC(hdc);
				_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width, _imageInfo->height);
				_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
				_blendImage->width = _imageInfo->width;
				_blendImage->height = _imageInfo->height;
				if (_blendImage->hBit == NULL)
				{
					alphaRelease();

					return E_FAIL;
				}
			}
		}
	}
	return S_OK;
}

void image::render(HDC hdc)
{
	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			0,					//�̹��� �׷��� ����X��ǥ(left)
			0,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, 0, 0,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			posX,					//�̹��� �׷��� ����X��ǥ(left)
			posY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, posX, posY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render2(HDC hdc, int destX, int destY)
{

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			destX,					//�̹��� �׷��� ����X��ǥ(left)
			destY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, destX, destY,
			_imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + sourWidth < 0) return;
		if (posY + sourHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			posX,					//�̹��� �׷��� ����X��ǥ(left)
			posY,					//�̹��� �׷��� ����Y��ǥ(top)
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			sourX, sourY,			//��������� XY��ǥ
			sourWidth,				//������ ����/����ũ��
			sourHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, posX, posY,
			sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			posX,					//�̹��� �׷��� ����X��ǥ(left)
			posY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,				//����� ����ũ��
			_imageInfo->frameHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//��������� XY��ǥ
			_imageInfo->frameWidth,				//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, posX, posY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			hdc,					//����� DC
			posX,					//�̹��� �׷��� ����X��ǥ(left)
			posY,					//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,				//����� ����ũ��
			_imageInfo->frameHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight,			//��������� XY��ǥ
			_imageInfo->frameWidth,				//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
	}
	else
	{
		BitBlt(hdc, posX, posY,
			_imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::loopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY)
{
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ������ �����غ���
	int drawAreaX = drawArea->left;				//�׷��� ������ Left
	int drawAreaY = drawArea->top;				//�׷��� ������ top
	int drawAreaW = drawArea->right - drawAreaX; //�׷��� ������ ����ũ��
	int drawAreaH = drawArea->bottom - drawAreaY;//�׷��� ������ ����ũ��

	//���κ��� �غ��ô�
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//������ ������ ���ؼ� ��Ȯ�� ��ġ�� �˾ƿ´�
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ���� ���
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �̹����� �����ٸ�
		if (y + sourHeight > drawAreaH)
		{
			//�׸�ŭ ��������� - ���궧���� ������ -���� ���� �ƴ϶� �����ΰ���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�ø���(�ٽ� �׷��ش�)
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//�Ͽ��̰� ���ϴ� X��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//������ ������ ���� ���� ����
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			render(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top);
		}
	}

}

//
void image::alphaRender(HDC hdc, BYTE alpha)
{
	//������ �����սô�
	//BYTE�� ���ĺ��� ��ġ���̴�. 0 ~ 255�� ������ ������
	//���� �������� ������ ����

	if (!_alpha)
	{
		render(hdc);
		return;
	}

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		//����ؾߵ� DC�� �׷����ִ� ������ blend�� �׸���
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, (int)_imageInfo->x, (int)_imageInfo->y, SRCCOPY);

		//����ؾߵ� �̹����� Blend�� �ű��
		GdiTransparentBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _transColor);

		//BlendDC�� ����ؾߵ� ��� �׸���
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else
	{
		//BlendDC�� ����ؾߵ� ��� �׸���
		AlphaBlend(hdc, (int)_imageInfo->x, (int)_imageInfo->y, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->width < 0) return;
		if (posY + _imageInfo->height < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	//������ �����սô�
	//BYTE�� ���ĺ��� ��ġ���̴�. 0 ~ 255�� ������ ������
	//���� �������� ������ ����
	if (!_alpha)
	{
		render(hdc, destX, destY);
		return;
	}

	//�̰��� �ؾ� ���İ��� �����!!!
	_blendFunc.SourceConstantAlpha = alpha;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, posX, posY, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,						//�̹��� �׷��� ����X��ǥ(left)
			0,						//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->width,		//����� ����ũ��
			_imageInfo->height,		//����� ����ũ��
			_imageInfo->hMemDC,
			0, 0,					//��������� XY��ǥ
			_imageInfo->width,		//������ ����/����ũ��
			_imageInfo->height,
			_transColor				//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc, posX, posY, _imageInfo->width,
			_imageInfo->height, _blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, posX, posY, _imageInfo->width,
			_imageInfo->height, _imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + sourWidth < 0) return;
		if (posY + sourHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (!_alpha)
	{
		render(hdc, destX, destY, sourX, sourY, sourWidth, sourHeight);
		return;
	}
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, posX, posY, SRCCOPY);
		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,					//�̹��� �׷��� ����X��ǥ(left)
			0,					//�̹��� �׷��� ����Y��ǥ(top)
			sourWidth,				//����� ����ũ��
			sourHeight,				//����� ����ũ��
			_imageInfo->hMemDC,
			sourX, sourY,			//��������� XY��ǥ
			sourWidth,				//������ ����/����ũ��
			sourHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
		AlphaBlend(hdc, posX, posY, sourWidth,
			sourHeight, _blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, posX, posY, sourWidth,
			sourHeight, _blendImage->hMemDC, sourX, sourY, sourWidth, sourHeight,
			_blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, BYTE alpha)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (!_alpha)
	{
		frameRender(hdc, destX, destY);
		return;
	}
	_blendFunc.SourceConstantAlpha = alpha;
	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, posX, posY, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,						//�̹��� �׷��� ����X��ǥ(left)
			0,						//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,		//����� ����ũ��
			_imageInfo->frameHeight,		//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,					//��������� XY��ǥ
			_imageInfo->frameWidth,		//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);

		AlphaBlend(hdc, posX, posY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, posX, posY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendFunc);
	}
}

void image::alphaFrameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha)
{
	float posX = destX - CAMERA->getPosX();
	float posY = destY - CAMERA->getPosY();

	if (_imageInfo->hMemDC != NULL)
	{
		if (posX + _imageInfo->frameWidth < 0) return;
		if (posY + _imageInfo->frameHeight < 0) return;
		if (posX > WINSIZEX) return;
		if (posY > WINSIZEY) return;
	}

	if (!_alpha)
	{
		frameRender(hdc, destX, destY, currentFrameX, currentFrameY);
		return;
	}
	_blendFunc.SourceConstantAlpha = alpha;
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;

	if (_trans)
	{
		BitBlt(_blendImage->hMemDC, 0, 0,
			_imageInfo->width, _imageInfo->height,
			hdc, posX, posY, SRCCOPY);

		//Ư��Į�� �����ϰ� DC -> DC ���̷� ��Ӻ��� ���ִ� �Լ�
		GdiTransparentBlt(
			_blendImage->hMemDC,	//����� DC
			0,						//�̹��� �׷��� ����X��ǥ(left)
			0,						//�̹��� �׷��� ����Y��ǥ(top)
			_imageInfo->frameWidth,		//����� ����ũ��
			_imageInfo->frameHeight,		//����� ����ũ��
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,					//��������� XY��ǥ
			_imageInfo->frameWidth,		//������ ����/����ũ��
			_imageInfo->frameHeight,
			_transColor				//���綧 ������ Į��(�� Į��)
		);
		AlphaBlend(hdc, posX, posY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendFunc);
	}
	else
	{
		AlphaBlend(hdc, posX, posY, _imageInfo->frameWidth,
			_imageInfo->frameHeight, _blendImage->hMemDC, 0, 0, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendFunc);
	}
}

void image::alphaLoopRender(HDC hdc, const LPRECT drawArea, int offSetX, int offSetY, BYTE alpha)
{
	if (!_alpha)
	{
		loopRender(hdc, drawArea, offSetX, offSetY);
		return;
	}
	_blendFunc.SourceConstantAlpha = alpha;
	if (offSetX < 0) offSetX = _imageInfo->width + (offSetX % _imageInfo->width);
	if (offSetY < 0) offSetY = _imageInfo->height + (offSetY % _imageInfo->height);

	int sourWidth;
	int sourHeight;

	RECT rcDest;
	RECT rcSour;

	//ȭ�鿡 �����̹��� �׷��� ������ �����غ���
	int drawAreaX = drawArea->left;				//�׷��� ������ Left
	int drawAreaY = drawArea->top;				//�׷��� ������ top
	int drawAreaW = drawArea->right - drawAreaX; //�׷��� ������ ����ũ��
	int drawAreaH = drawArea->bottom - drawAreaY;//�׷��� ������ ����ũ��

	//���κ��� �غ��ô�
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//������ ������ ���ؼ� ��Ȯ�� ��ġ�� �˾ƿ´�
		rcSour.top = (y + offSetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;

		//�з��ö� ���� ���
		sourHeight = rcSour.bottom - rcSour.top;

		//ȭ������� �̹����� �����ٸ�
		if (y + sourHeight > drawAreaH)
		{
			//�׸�ŭ ��������� - ���궧���� ������ -���� ���� �ƴ϶� �����ΰ���
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//ȭ������� ���������� �ٽ� �о�ø���(�ٽ� �׷��ش�)
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//�Ͽ��̰� ���ϴ� X��
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//������ ������ ���� ���� ����
			rcSour.left = (x + offSetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;

			sourWidth = rcSour.right - rcSour.left;

			if (x + sourWidth > drawAreaW)
			{
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			alphaRender(hdc, rcDest.left, rcDest.top,
				rcSour.left, rcSour.top,
				rcSour.right - rcSour.left,
				rcSour.bottom - rcSour.top, alpha);
		}
	}
}


void image::aniRender(HDC hdc, int destX, int destY, animation* ani)
{
	render(hdc, destX, destY, ani->getFramePos().x, ani->getFramePos().y, ani->getFrameWidth(), ani->getFrameHeight());
}