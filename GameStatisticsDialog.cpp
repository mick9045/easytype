#include "stdafx.h"
#include "GameStatisticsDialog.h"
#include <math.h>

namespace CourseWork_WinApi
{
	GameStatisticsDialog::GameStatisticsDialog()
		:BaseDialogWindow(IDD_DIALOG_GAME_STATICS)
	{
		
	}


	GameStatisticsDialog::~GameStatisticsDialog()
	{
	}

	VOID GameStatisticsDialog::UpdateCPM(INT nCPM)
	{
		tString cStr;
		INT wpm;
		cStr.append(to_tstring(nCPM));
		cStr.append(_T(" CPM"));
		SetWindowText(_hwndCpm, cStr.c_str());
		cStr.clear();
		if (nCPM)
		{
			wpm = nCPM / 5;
		}
		else
		{
			wpm = 0;
		}
		cStr.append(to_tstring(wpm));
		cStr.append(_T(" WPM"));
		SetWindowText(_hwndWpm, cStr.c_str());
	}

	VOID GameStatisticsDialog::UpdateAccuracy(INT nAccuracy)
	{
		tString str;
		str.append(to_tstring(nAccuracy));
		str.append(_T("%"));
		SetWindowText(_hwndAccuracy, str.c_str());
	}

	VOID GameStatisticsDialog::UpdateUILanguage()
	{
		SetDlgItemText(
			_hwnd,
			IDC_STATIC_SPEEDBOX,
			_local.QueryString(IDS_STRING_TYPING_SPEED).c_str()
		);
		SetDlgItemText(
			_hwnd,
			IDC_STATIC_ACCURACYBOX,
			_local.QueryString(IDS_STRING_TYPING_ACCURACY).c_str()
		);
	}

	INT GameStatisticsDialog::CPM()
	{
		return std::stoi(GetText(_hwndCpm));
	}

	INT GameStatisticsDialog::WPM()
	{
		return std::stoi(GetText(_hwndWpm));
	}

	INT GameStatisticsDialog::Accuracy()
	{
		return std::stoi(GetText(_hwndAccuracy));
	}

	VOID GameStatisticsDialog::Reset()
	{
		UpdateAccuracy(100);
		UpdateCPM(0);
	}

	BOOL GameStatisticsDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
	{
		EnableWindow(hwnd, FALSE);
		_hwndCpm = GetDlgItem(hwnd, IDC_STATIC_WPM);
		_hwndWpm = GetDlgItem(hwnd, IDC_STATIC_CPM);
		_hwndAccuracy = GetDlgItem(hwnd, IDC_STATIC_ACCURACY);
		Reset();
		UpdateUILanguage();
		return TRUE;
	}

	INT_PTR GameStatisticsDialog::DlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
			HANDLE_MSG(hwnd, WM_INITDIALOG, Cls_OnInitDialog);
		}
		return FALSE;
	}
}
