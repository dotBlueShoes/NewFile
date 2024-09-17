﻿#include "dialogWindow.hpp"

LRESULT CALLBACK WndProc (HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(
	_In_		HINSTANCE hInstance,
	_In_opt_	HINSTANCE hPrevInstance,
	_In_		LPWSTR    lpCmdLine,
	_In_		int       nCmdShow
) {

	UNREFERENCED_PARAMETER (hPrevInstance);
	UNREFERENCED_PARAMETER (lpCmdLine);
	UNREFERENCED_PARAMETER (nCmdShow);

	if (!InitDialog (hInstance)) {
		return FALSE;
	}

	MSG msg;

	while (GetMessage (&msg, nullptr, 0, 0)) {
		TranslateMessage (&msg);
		DispatchMessage (&msg);
	}

	return (int) msg.wParam;
}
