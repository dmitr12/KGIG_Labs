#pragma once
#include "stdafx.h"
#include "Plot2D.h"
#define PI acos(-1)
class CSunSystem
{
private:
	CRect Sun, Mars, Earth, Moon, MarsOrbit, EarthOrbit, MoonOrbit;
	CSize MarsOrbitSize, MarsSize, EarthOrbitSize, EarthSize, MoonOrbitSize, MoonSize;
	CMatrix ECoords, MoonCoords, MoonCoords1, MarsCoords, PMars, PMoon, PE;
	double dfiE, dfiMars, dfiMoon, dt;
public:
	CSunSystem();
	void SetDT(double dtx) { dt = dtx; }
	void SetNewCoords();
	void Draw(CDC& dc);
};
CMatrix Rotate2D(double fi);