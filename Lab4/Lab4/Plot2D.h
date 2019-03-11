#pragma once
#include "stdafx.h"
#include "CMatrix.h"
class CRectD
{
public:
	double left, top, right, bottom;
	CRectD() { left = top = right = bottom = 0; }
	CRectD(double _left, double _top, double _right, double _bottom)
	{
		left = _left;
		top = _top;
		right = _right;
		bottom = _bottom;
	}
	operator CRect() { return CRect(left, top, right, bottom); }
};
struct CMyPen
{
	int PenStyle;
	double PenWidth;
	COLORREF PenColor;
	CMyPen();
	void Set(int PS, int PW, COLORREF PC);
};
class CPlot2D
{
private:
	CMatrix X, Y, K;
	CRectD Rs;
	CRect Rw;
	CMyPen PenLine;
	CMyPen PenAxis;
public:
	CPlot2D() { K.RedimMatrix(3, 3); }
	void SetParams(CMatrix& XX, CMatrix& YY);
	void SetWindowRect(CRect& RWX) { Rw = RWX; }
	void GetWindowCoords(double xs, double ys, int &xw, int &yw);
	void SetPenLine(CMyPen& PLine) { PenLine = PLine; }
	void SetPenAxis(CMyPen& PAxis) { PenAxis = PAxis; }
	void Draw(CDC& dc, int Ind1, int Int2);
	void Draw1(CDC& dc, int Ind1, int Int2);
	void GetRS(CRectD& RS) { RS = Rs; }
	void GetRW(CRect& RW) { RW = Rw; }
};
CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
void SetMyMode(CDC& dc, CRectD& rs, CRect& rw);