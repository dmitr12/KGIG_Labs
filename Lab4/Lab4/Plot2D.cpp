#include "stdafx.h"
#include "Plot2D.h"
CMyPen::CMyPen()
{
	PenStyle = PS_SOLID;
	PenWidth = 1;
	PenColor = RGB(0, 0, 0);
}
void CMyPen::Set(int PS, int PW, COLORREF PC)
{
	PenStyle = PS;
	PenWidth = PW;
	PenColor = PC;
}
void CPlot2D::SetParams(CMatrix& XX, CMatrix& YY)
{
	X.RedimMatrix(XX.rows(), 1);
	X = XX;
	Y.RedimMatrix(YY.rows(), 1);
	Y = YY;
	for (int i = 0; i < X.rows(); i++)
	{
		if (X(i) < Rs.left)
			Rs.left = X(i);
		if (X(i) > Rs.right)
			Rs.right = X(i);
		if (Y(i) < Rs.bottom)
			Rs.bottom = Y(i);
		if (Y(i) > Rs.top)
			Rs.top = Y(i);
	}
}
void CPlot2D::GetWindowCoords(double xs, double ys, int &xw, int &yw)
{
	CMatrix V(3), W(3);
	V(0) = xs;
	V(1) = ys;
	V(2) = 1;
	W = K * V;
	xw = (int)W(0);
	yw = (int)W(1);
}
void CPlot2D::Draw(CDC& dc, int Ind1, int Int2)
{
	CPen pen;
	pen.CreatePen(0, 0, RGB(0, 0, 0));
	dc.SelectObject(pen);
	int xw, yw;
	K = SpaceToWindow(Rs, Rw);
	dc.Rectangle(Rw);
	pen.Detach();
	pen.CreatePen(PenAxis.PenStyle, PenAxis.PenWidth, PenAxis.PenColor);
	dc.SelectObject(pen);
	GetWindowCoords(Rs.left, 0, xw, yw);
	dc.MoveTo(xw, yw);
	GetWindowCoords(Rs.right, 0, xw, yw);
	dc.LineTo(xw, yw);
	GetWindowCoords(0, Rs.top, xw, yw);
	dc.MoveTo(xw, yw);
	GetWindowCoords(0, Rs.bottom, xw, yw);
	dc.LineTo(xw, yw);
	pen.Detach();
	pen.CreatePen(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	dc.SelectObject(pen);
	if (Ind1 < X.rows() && Int2 <= X.rows())
		for (int i = Ind1 + 1; i < X.rows(); i += Int2)
		{
			GetWindowCoords(X(i - 1), Y(i - 1), xw, yw);
			dc.MoveTo(xw, yw);
			GetWindowCoords(X(i), Y(i), xw, yw);
			dc.LineTo(xw, yw);
		}
}
void CPlot2D::Draw1(CDC& dc, int Ind1, int Int2)
{
	CPen pen;
	pen.CreatePen(0, 0, RGB(0, 0, 0));
	dc.SelectObject(pen);
	CRect Rss = Rs;
	dc.Rectangle(Rss);
	pen.Detach();
	pen.CreatePen(PenAxis.PenStyle, PenAxis.PenWidth, PenAxis.PenColor);
	dc.SelectObject(pen);
	dc.MoveTo(Rs.left, 0);
	dc.LineTo(Rs.right, 0);
	dc.MoveTo(0, Rs.top);
	dc.LineTo(0, Rs.bottom);
	pen.Detach();
	pen.CreatePen(PenLine.PenStyle, PenLine.PenWidth, PenLine.PenColor);
	dc.SelectObject(pen);
	if (Ind1 < X.rows() && Int2 <= X.rows())
		for (int i = Ind1 + 1; i < X.rows(); i += Int2)
		{
			dc.MoveTo(X(i - 1), Y(i - 1));
			dc.LineTo(X(i), Y(i));
		}
}
CMatrix SpaceToWindow(CRectD& rs, CRect& rw)
{
	CMatrix T(3, 3);
	double kx = (rw.right - rw.left) / (rs.right - rs.left),
		ky = (rw.bottom - rw.top) / (rs.top - rs.bottom);
	T(0, 0) = kx;
	T(0, 2) = rw.left - kx * rs.left;
	T(1, 1) = -ky;
	T(1, 2) = rw.bottom + ky * rs.bottom;
	T(2, 2) = 1;
	return T;
}
void SetMyMode(CDC& dc, CRectD& rs, CRect& rw)
{
	int dsx = rs.right - rs.left,
		dsy = rs.top - rs.bottom,
		xsL = rs.left,
		ysL = rs.bottom,
		dwx = rw.right - rw.left,
		dwy = rw.bottom - rw.top,
		xwL = rw.left,
		ywH = rw.bottom;
	dc.SetMapMode(MM_ANISOTROPIC);
	dc.SetWindowExt(dsx, dsy);
	dc.SetViewportExt(dwx, -dwy);
	dc.SetWindowOrg(xsL, ysL);
	dc.SetViewportOrg(xwL, ywH);
}
