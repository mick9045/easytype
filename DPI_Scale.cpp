#include "stdafx.h"
#include "DPI_Scale.h"

namespace CourseWork_WinApi
{

	DPI_Scale::DPI_Scale()
	{
		/*UINT32 num_path_array_elements, num_mode_info_array_elements;
		GetDisplayConfigBufferSizes(QDC_DATABASE_CURRENT, &num_path_array_elements, &num_mode_info_array_elements);
		DISPLAYCONFIG_PATH_INFO *lpPathInfo = reinterpret_cast<DISPLAYCONFIG_PATH_INFO *> (LocalAlloc(LMEM_FIXED, sizeof(DISPLAYCONFIG_PATH_INFO) * num_path_array_elements));
		DISPLAYCONFIG_MODE_INFO *lpModeInfo = reinterpret_cast<DISPLAYCONFIG_MODE_INFO *> (LocalAlloc(LMEM_FIXED, sizeof(DISPLAYCONFIG_MODE_INFO) * num_mode_info_array_elements));
		DISPLAYCONFIG_TOPOLOGY_ID TopologyId;
		QueryDisplayConfig(QDC_DATABASE_CURRENT, &num_path_array_elements, lpPathInfo, &num_mode_info_array_elements, lpModeInfo, &TopologyId);
		FLOAT uPhysicsScreenWidth = (FLOAT)lpModeInfo[1].sourceMode.width;*/



		HDC hdcScreen = GetWindowDC(NULL);
		UINT PrimaryMonitorWidth = GetDeviceCaps(hdcScreen, HORZRES);
		WORD wDpi = GetDeviceCaps(hdcScreen, LOGPIXELSX);
		this->_iDpi = MulDiv(wDpi, 100, 96);
	}

	DPI_Scale::DPI_Scale(UINT iDpi)
	{
		this->_iDpi = iDpi;
	}

	INT DPI_Scale::Scale(INT X)
	{
		return MulDiv(X, _iDpi, 100);
	}

	POINT DPI_Scale::ScalePoint(POINT Point)
	{
		Scale(Point.x);
		Scale(Point.y);
		return Point;
	}

	RECT DPI_Scale::ScaleRect(RECT Rect)
	{
		Scale(Rect.top);
		Scale(Rect.bottom);
		Scale(Rect.left);
		Scale(Rect.right);
		return Rect;
	}

	VOID DPI_Scale::SetDpi(UINT iDpi)
	{
		this->_iDpi = iDpi;
	}

	INT DPI_Scale::GetDpi()
	{
		return this->_iDpi;
	}

}