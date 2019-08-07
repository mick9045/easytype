#include "stdafx.h"
#include "TypeButtonInfo.h"

namespace CourseWork_WinApi
{


	TypeButtonInfo::TypeButtonInfo(
		UINT uButtonID,
		TCHAR tchCharacter,
		BOOL bShiftPrssed,
		BOOL bShow)
	{
		_uButtonID = uButtonID;
		_tchCaracter = tchCharacter;
		_bShift = bShiftPrssed;
		_bShow = bShow;
	}


	TypeButtonInfo::~TypeButtonInfo()
	{
	}

	UINT TypeButtonInfo::Id() const
	{
		return _uButtonID;
	}

	TCHAR TypeButtonInfo::Character() const
	{
		return _tchCaracter;
	}

	BOOL TypeButtonInfo::ShiftPressed() const
	{
		return _bShift;
	}

	BOOL TypeButtonInfo::Show() const
	{
		return _bShow;
	}

}