#pragma once
#include "stdafx.h"

namespace CourseWork_WinApi
{
	//When constructor without parameters is invoked
	//scale factor is caclulated automatically
	class DPI_Scale
	{
	public:
		DPI_Scale();
		DPI_Scale(UINT iDpi);
		INT Scale(INT X);
		POINT ScalePoint(POINT Point);
		RECT ScaleRect(RECT Rect);
		VOID SetDpi(UINT iDpi);
		INT GetDpi();
	private:
		UINT _iDpi;
	};

}