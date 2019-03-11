#include "stdafx.h"
#include "CMainWin.h"
#include "CMatrix.h"
CMainWin::CMainWin()
{
	this->Create(0, (LPCTSTR)L"Hello World", WS_OVERLAPPED, window, 0, (LPCTSTR)IDR_MAINFRAME);
	SetTimer(0, time, 0);
}
void CMainWin::OnPaint()
{
	CPaintDC dc(this);
	CRectD rs;
	rs.left = rs.top = -400;
	rs.right = rs.bottom = 400;
	if (visible)
	{
		SetMyMode(dc, rs, window);
		sunSystem.Draw(dc);
	}
}
void CMainWin::OnTimer(UINT id)
{
	if (id == 0 && start && visible) sunSystem.SetNewCoords();
	InvalidateRect(0);
}
void CMainWin::OnLButtonDblClk(UINT flags, CPoint point)
{
	if (visible)
		start = true;
	InvalidateRect(0);
}
void CMainWin::OnRButtonDblClk(UINT flags, CPoint point)
{
	start = false;
	InvalidateRect(0);
}
void CMainWin::Start()
{
	visible = true;
	InvalidateRect(0);
}
void CMainWin::Clear()
{
	start = false;
	visible = false;
	InvalidateRect(0);
}
void CMainWin::MyClose()
{
	this->OnClose();
}
BEGIN_MESSAGE_MAP(CMainWin, CFrameWnd)
	ON_COMMAND(ID_CLEAR, &CMainWin::Clear)
	ON_COMMAND(ID_EXIT, &CMainWin::MyClose)
	ON_COMMAND(ID_LABPLANETS_PLANETS, &CMainWin::Start)
	ON_WM_TIMER()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_RBUTTONDBLCLK()
	ON_WM_PAINT()
END_MESSAGE_MAP()