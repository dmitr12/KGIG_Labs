#include "stdafx.h"
#include "CSunSystem.h"
CSunSystem::CSunSystem()
{
	ECoords.RedimMatrix(3, 1);
	MoonCoords.RedimMatrix(3, 1);
	MoonCoords1.RedimMatrix(3, 1);
	MarsCoords.RedimMatrix(3, 1);
	PMars.RedimMatrix(3, 3);
	PMoon.RedimMatrix(3, 3);
	PE.RedimMatrix(3, 3);
	Sun = CRect(-30, 30, 30, -30);
	EarthOrbit = CRect(Sun.left - 200, Sun.top + 200, Sun.right + 200, Sun.bottom - 200);
	MarsOrbit = CRect(Sun.left - 100, Sun.top + 100, Sun.right + 100, Sun.bottom - 100);
	EarthOrbitSize.cx = (EarthOrbit.right - EarthOrbit.left) / 2;
	EarthOrbitSize.cy = (EarthOrbit.top - EarthOrbit.bottom) / 2;
	MarsOrbitSize.cx = (MarsOrbit.right - MarsOrbit.left) / 2;
	MarsOrbitSize.cy = (MarsOrbit.top - MarsOrbit.bottom) / 2;
	Mars = CRect(MarsOrbit.right - 15, MarsOrbitSize.cy + MarsOrbit.bottom + 15, MarsOrbit.right + 15, MarsOrbitSize.cy + MarsOrbit.bottom - 15);
	MarsSize.cx = (Mars.right - Mars.left) / 2;
	MarsSize.cy = (Mars.top - Mars.bottom) / 2;
	MarsCoords(0) = Mars.left + MarsSize.cx;
	MarsCoords(1) = Mars.bottom + MarsSize.cy;
	MarsCoords(2) = 1;
	Earth = CRect(EarthOrbit.right - 20, EarthOrbitSize.cy + EarthOrbit.bottom + 20, EarthOrbit.right + 20, EarthOrbitSize.cy + EarthOrbit.bottom - 20);
	EarthSize.cx = (Earth.right - Earth.left) / 2;
	EarthSize.cy = (Earth.top - Earth.bottom) / 2;
	ECoords(0) = Earth.left + EarthSize.cx;
	ECoords(1) = Earth.bottom + EarthSize.cy;
	ECoords(2) = 1;
	MoonOrbit = CRect(Earth.left - 30, Earth.top + 30, Earth.right + 30, Earth.bottom - 30);
	MoonOrbitSize.cx = (MoonOrbit.right - MoonOrbit.left) / 2;
	MoonOrbitSize.cy = (MoonOrbit.top - MoonOrbit.bottom) / 2;
	Moon = CRect(MoonOrbit.right - 10, MoonOrbitSize.cy + MoonOrbit.bottom + 10, MoonOrbit.right + 10, MoonOrbitSize.cy + MoonOrbit.bottom - 10);
	MoonSize.cx = (Moon.right - Moon.left) / 2;
	MoonSize.cy = (Moon.top - Moon.bottom) / 2;
	MoonCoords(0) = Moon.left + MoonSize.cx;
	MoonCoords(1) = Moon.bottom + MoonSize.cy;
	MoonCoords(2) = 1;
	MoonCoords1(0) = MoonOrbitSize.cx;
	MoonCoords1(1) = 0;
	MoonCoords1(2) = 1;
	dfiMars = 15;
	dfiE = 10;
	dfiMoon = 20;
	PMars = Rotate2D(dfiMars);
	PMoon = Rotate2D(dfiMoon);
	PE = Rotate2D(dfiE);
}
void CSunSystem::SetNewCoords()
{
	ECoords = PE * ECoords;
	MarsCoords = PMars * MarsCoords;
	MoonCoords = PE * MoonCoords;
	MoonCoords1 = PMoon * MoonCoords1;
}
void CSunSystem::Draw(CDC& dc)
{
	//dc.Ellipse(EarthOrbit);
	//dc.Ellipse(MarsOrbit);
	dc.Ellipse(MarsCoords(0) - MarsSize.cx,
		MarsCoords(1) + MarsSize.cy,
		MarsCoords(0) + MarsSize.cx,
		MarsCoords(1) - MarsSize.cy);
	/*dc.Ellipse(ECoords(0) - (MoonOrbit.right - MoonOrbit.left) / 2,
		ECoords(1) + (MoonOrbit.top - MoonOrbit.bottom) / 2,
		ECoords(0) + (MoonOrbit.right - MoonOrbit.left) / 2,
		ECoords(1) - (MoonOrbit.top - MoonOrbit.bottom) / 2);*/
	dc.Ellipse(ECoords(0) + MoonCoords1(0) - MoonSize.cx,
		ECoords(1) + MoonCoords1(1) + MoonSize.cy,
		ECoords(0) + MoonCoords1(0) + MoonSize.cx,
		ECoords(1) + MoonCoords1(1) - MoonSize.cy);
	dc.Ellipse(ECoords(0) - EarthSize.cx,
		ECoords(1) + EarthSize.cy,
		ECoords(0) + EarthSize.cx,
		ECoords(1) - EarthSize.cy);
	dc.Ellipse(Sun);
}
CMatrix Rotate2D(double fi)
{
	CMatrix T(3, 3);
	T(2, 2) = 1;
	T(0, 0) = T(1, 1) = cos(fi * PI / 180);
	T(1, 0) = sin(fi * PI / 180);
	T(0, 1) = -sin(fi * PI / 180);
	return T;
}