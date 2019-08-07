#pragma once
#include "BaseDialogWindow.h"

namespace CourseWork_WinApi
{
	class GameStatisticsDialog :
		public BaseDialogWindow
	{
	public:
		GameStatisticsDialog();
		~GameStatisticsDialog();
		VOID UpdateCPM(INT cpm);
		VOID UpdateAccuracy(INT accuracy);
		VOID UpdateUILanguage();
		INT CPM();
		INT WPM();
		INT Accuracy();
		VOID Reset();
	protected:
		BOOL Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);

		// Inherited via BaseDialogWindow
		virtual INT_PTR DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	private:
		HWND _hwndCpm;
		HWND _hwndWpm;
		HWND _hwndAccuracy;
	};
}