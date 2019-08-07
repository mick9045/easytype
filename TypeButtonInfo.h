#pragma once
#include <Windows.h>
#include <tchar.h>

namespace CourseWork_WinApi
{

	class TypeButtonInfo
	{
	public:
		TypeButtonInfo(UINT uButtonID, TCHAR tchCharacter, BOOL bShiftPrssed, BOOL _bShow);
		~TypeButtonInfo();
		UINT Id() const;
		TCHAR Character() const;
		BOOL ShiftPressed() const; 
		BOOL Show() const;
	private:
		UINT _uButtonID;
		TCHAR _tchCaracter;
		BOOL _bShift;
		BOOL _bShow;
	};

}