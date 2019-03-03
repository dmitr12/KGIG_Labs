#include "stdafx.h"
#include "CMainWin.h"
#include<string.h>
#include <string>
int ShowBitMap(HWND hWnd, HBITMAP hBit, int x, int y)
{
	BITMAP BitMap;
	GetObject(hBit, sizeof(BITMAP), &BitMap);
	int Height = BitMap.bmHeight;
	int Width = BitMap.bmWidth;
	HDC ImageDC = GetDC(hWnd);
	HDC MemoryDC = CreateCompatibleDC(ImageDC);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemoryDC, hBit);
	BitBlt(ImageDC, x, y, Width, Height, MemoryDC, 0, 0, SRCCOPY);
	SelectObject(MemoryDC, OldBitmap);
	ReleaseDC(hWnd, ImageDC);
	DeleteDC(MemoryDC);
	return 0;
}
int ClientToBmp(HWND hWnd, RECT& rect, CString str)
{
	BITMAPFILEHEADER bitFile;
	BITMAPINFOHEADER bitInfo;
	RECT ImageRect = rect;
	LONG Width = ImageRect.right - ImageRect.left,
		Height = ImageRect.bottom - ImageRect.top;
	int BitToPixel = 16;
	HDC ImageDC = GetDC(hWnd);
	HDC MemoryDC = CreateCompatibleDC(ImageDC);
	HBITMAP BitMap = CreateCompatibleBitmap(ImageDC, Width, Height);
	HBITMAP OldBitmap = (HBITMAP)SelectObject(MemoryDC, BitMap);
	BitBlt(MemoryDC, 0, 0, Width, Height, ImageDC, ImageRect.left, ImageRect.top, SRCCOPY);
	BitMap = (HBITMAP)SelectObject(MemoryDC, OldBitmap);
	ZeroMemory(&bitInfo, sizeof(BITMAPINFOHEADER));
	bitInfo.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.biWidth = Width;
	bitInfo.biHeight = Height;
	bitInfo.biPlanes = 1;
	bitInfo.biBitCount = BitToPixel;
	bitInfo.biSizeImage = (Width * BitToPixel + 31) / 32 * 4 * Height;
	DWORD dwWritten;
	HANDLE FileHandle = CreateFile(str, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (FileHandle == INVALID_HANDLE_VALUE) 
		return 2;
	bitFile.bfType = ('M' << 8) | 'B'; 
	bitFile.bfSize = bitInfo.biSizeImage + sizeof(bitFile) + bitInfo.biSize; 
	bitFile.bfReserved1 = bitFile.bfReserved2 = 0;
	bitFile.bfOffBits = sizeof(bitFile) + bitInfo.biSize; 
	WriteFile(FileHandle, (LPSTR)&bitFile, sizeof(bitFile), &dwWritten, NULL);
	WriteFile(FileHandle, (LPSTR)&bitInfo, sizeof(BITMAPINFOHEADER), &dwWritten, NULL);
	char *lp = (char *)GlobalAlloc(GMEM_FIXED, bitInfo.biSizeImage);
	GetDIBits(ImageDC, BitMap, 0, (UINT)Height, lp, (LPBITMAPINFO)&bitInfo, DIB_RGB_COLORS);
	WriteFile(FileHandle, lp, bitInfo.biSizeImage, &dwWritten, NULL);
	GlobalFree(GlobalHandle(lp));
	CloseHandle(FileHandle);
	ReleaseDC(hWnd, ImageDC);
	DeleteDC(MemoryDC);
	if (dwWritten == 0) 
		return 2;
	return 0;
}
CMainWin::CMainWin()
{
	this->Create(0, (LPCTSTR)L"Hello World", WS_OVERLAPPEDWINDOW, rectDefault, 0, (LPCTSTR)IDR_MAINFRAME);
}
void CMainWin::OnPaint()
{
	CPaintDC dc(this);
	if (opened)
	{
		FileDialog = new CFileDialog(true);
		FileDialog->DoModal();
		HBITMAP bit = (HBITMAP)LoadImage(NULL, FileDialog->GetPathName(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		ShowBitMap(this->m_hWnd, bit, PaintPosition.x, PaintPosition.y);
		delete FileDialog;
		FileDialog = nullptr;
		opened = false;
	} 
	if (saved)
	{
		FileDialog = new CFileDialog(false);
		FileDialog->DoModal();
		ClientToBmp(m_hWnd, SaveRect, FileDialog->GetPathName());
		delete FileDialog;
		FileDialog = nullptr;
		saved = false;
	}
}
void CMainWin::OnLButtonDown(UINT Flags, CPoint Location)
{
	SaveRect.left = Location.x;
	SaveRect.top = Location.y;
	PaintPosition = Location;
}
void CMainWin::OnLButtonUp(UINT Flags, CPoint Location)
{
	SaveRect.right = Location.x;
	SaveRect.bottom = Location.y;
	if (SaveRect.left > SaveRect.right)
	{
		LONG buffer = SaveRect.left;
		SaveRect.left = SaveRect.right;
		SaveRect.right = buffer;
	}
	if (SaveRect.top > SaveRect.bottom)
	{
		LONG buffer = SaveRect.top;
		SaveRect.top = SaveRect.bottom;
		SaveRect.bottom = buffer;
	}
	if (SaveRect.bottom - SaveRect.top > 5 && SaveRect.right - SaveRect.left > 5)
		saved = true;
	OnPaint();
}
void CMainWin::Open()
{
	opened = true;
	InvalidateRect(0);
}
void CMainWin::Clear()
{
	InvalidateRect(0);
}

BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_COMMAND(ID_CLEAR, &CMainWin::Clear)
	ON_COMMAND(ID_TESTS_IMAGE, &CMainWin::Open)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_PAINT()
END_MESSAGE_MAP()