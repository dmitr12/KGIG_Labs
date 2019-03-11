#pragma once
#include "stdafx.h"
#include "resource.h"
#include "CSunSystem.h"
class CMainWin : public CFrameWnd
{
private:
	UINT time = 100;
	bool start = false, visible = false;
	CRect window = CRect(0, 0, 750, 750);
	CSunSystem sunSystem;
public:
	CMainWin();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT id);
	afx_msg void OnLButtonDblClk(UINT flags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT flags, CPoint point);
	afx_msg void Start();
	afx_msg void Clear();
	afx_msg void MyClose();
	DECLARE_MESSAGE_MAP()
};
