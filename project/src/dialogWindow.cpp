#include "dialogWindow.hpp"
#include "io.hpp"


HINSTANCE hInst = nullptr;	// Representation of application instance.
HWND hWnd = nullptr;		// Main window of application.
BOOL hasChanged = FALSE;	// Used to store globaly information about edit controls state.


BOOL InitDialog (HINSTANCE hInstance) {
	hInst = hInstance;

	hWnd = CreateDialog (hInstance, MAKEINTRESOURCE(IDD_DIALOGBOX), NULL, DlgProc);
	if (!hWnd) {
		return FALSE;
	}

	return TRUE;
}


INT_PTR CALLBACK DlgProc (HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam) {

	// UNREFERENCED_PARAMETER is defined in winnt.h and therefore not portable
	// It simply tells compiler not to worry about unused parameter.
	UNREFERENCED_PARAMETER (lParam);

	switch (message) {
		case WM_INITDIALOG: {

			// Sets the icon for DialogBox window.
			HICON hIcon = LoadIcon(hInst, MAKEINTRESOURCE(IDI_FILESM));
			if (hIcon) {
				SendMessage(hDlg, WM_SETICON, ICON_SMALL, (LPARAM)hIcon);
			}

			/* Subclass the Windows of Edit / Buttons Controls */
			SetWindowSubclass (GetDlgItem (hDlg, IDC_EDITNAME), ControlSubclassProc, 0, 0);
			SetWindowSubclass (GetDlgItem (hDlg, IDC_EDITEXTENSION), ControlSubclassProc, 0, 0);
			SetWindowSubclass (GetDlgItem (hDlg, IDCANCEL), ControlSubclassProc, 0, 0);
			SetWindowSubclass (GetDlgItem (hDlg, IDOK2), ControlSubclassProc, 0, 0);

			return (INT_PTR)FALSE;
		}

		case WM_COMMAND:

			// Set the default push button to "ok" after user enters text
			if ( HIWORD (wParam) == EN_CHANGE && hasChanged == FALSE) {
				hasChanged = TRUE;

				// Change The default button "IDCANCEL" to "IDOK".
				SendMessage (hWnd, DM_SETDEFID, (WPARAM)IDOK2, (LPARAM)0);
			}

			switch (wParam) {
				case IDOK2: {

					// Buffers which later will contain edit's value.
					// Becouse of the dot and null-termination their acctual max-size is 258.
					wchar_t lpszName[_MAX_PATH], lpszExt[_MAX_PATH];
					WORD cchName, cchExt;

					// Get length of characters
					cchName = (WORD) SendDlgItemMessage (
						hDlg, IDC_EDITNAME, EM_LINELENGTH, 
						(WPARAM)0, (LPARAM)0
					);

					cchExt = (WORD) SendDlgItemMessage (
						hDlg, IDC_EDITEXTENSION, EM_LINELENGTH, 
						(WPARAM)0, (LPARAM)0
					);

					// char debug_buf[10] { 0 };
					// debug_buf[0] = cchName + '0';
					// debug_buf[1] = '\,';
					// debug_buf[2] = cchExt + '0';
					// MessageBoxA (nullptr, debug_buf, "Error", MB_OK);
					// exit (1);

					// Check for errs
					if (cchName == 0) {

						MessageBoxW (
							hDlg,
							L"File Name can't be empty!",
							L"ERROR",
							MB_OK
						);

					} 
					
					//1 // NEW FEATURE
					//1 else if (cchExt == 0) {
					//1 
					//1 	MessageBoxW (
					//1 		hDlg,
					//1 		L"File Extension can't be empty!",
					//1 		L"ERROR",
					//1 		MB_OK
					//1 	);
					//1 
					//1 } 
					
					else if (cchName + cchExt >= _MAX_PATH) {

						MessageBoxW (
							hDlg,
							L"Picked Name and Extension creates to long to support pathname!",
							L"ERROR",
							MB_OK
						);

					} else {

						// Put the number of characters into first word buffer
						*((LPWORD)lpszName) = cchName;
						*((LPWORD)lpszExt) = cchExt;

						// Get line of characters
						SendDlgItemMessageW (
							hDlg, 
							IDC_EDITNAME, 
							EM_GETLINE, 
							(WPARAM)0, 
							(LPARAM)lpszName
						);

						if (cchExt == 0) {

							// New Feature
							//  Allow creation of files such as .gitingore or simply typing in filename field only.

							lpszName[cchName] = 0;

						} else {

							SendDlgItemMessageW (
								hDlg, 
								IDC_EDITEXTENSION, 
								EM_GETLINE, 
								(WPARAM)0, 
								(LPARAM)lpszExt
							);

							// Adding the "dot"
							lpszName[cchName] = L'.';

							// Adding the "extension" to the name
							for (int i = 0; i < cchExt; i++) {
								lpszName[cchName + i + 1] = lpszExt[i];
							}

							// NULL-terminate the string
							lpszName[cchName + cchExt + 1] = 0;

						}

						// Create new File 
						if (!FileCreate (lpszName)) {
							MessageBoxW (hDlg, L"Error: File might already exists.", lpszName, MB_OK);
						} else {
							QuitProcedure (wParam);
						}
					}

					return (INT_PTR)TRUE;
				}

				case IDCANCEL:
					QuitProcedure (wParam);
					return (INT_PTR)TRUE;

				case WM_NEXTDLGCTL:
					MessageBeep (MB_ICONASTERISK);
					return (INT_PTR)FALSE;
			}
			break;
	}
	return (INT_PTR)FALSE;
}


LRESULT CALLBACK ControlSubclassProc (
	HWND hCtr, 
	UINT message, 
	WPARAM wParam,
	LPARAM lParam, 
	UINT_PTR uIdSubclass, 
	DWORD_PTR dwRefData
) {

	switch (message) {		
		case WM_KEYDOWN: {
			switch (wParam) {
				case VK_UP: // Process the UP ARROW key. 
					SendMessage (hWnd, WM_NEXTDLGCTL, TRUE, FALSE);
					return FALSE;

				case VK_DOWN: // Process the DOWN ARROW key. 
					SendMessage (hWnd, WM_NEXTDLGCTL, FALSE, FALSE);
					return FALSE;

				case VK_LEFT: // Process the LEFT ARROW key. 
					SendMessage (hWnd, WM_NEXTDLGCTL, TRUE, FALSE);
					//MessageBoxW (hCtr, L"<-", L"Key was Pressed!", MB_OK);
					return TRUE;

				case VK_RIGHT: // Process the RIGHT ARROW key. 
					SendMessage (hWnd, WM_NEXTDLGCTL, FALSE, FALSE);
					//MessageBoxW (hCtr, L"->", L"Key was Pressed!", MB_OK);
					return TRUE;

				case VK_DELETE: // Process the DEL key. 
					MessageBoxW (hCtr, L"Delete", L"Key was Pressed!", MB_OK);
					return TRUE;

				case VK_F2: // Process the F2 key. 
					MessageBoxW (hCtr, L"F2", L"Key was Pressed!", MB_OK);
					return TRUE;
			}
		} break;

		case WM_CHAR: {
			switch (wParam) {

				case 0x1B: {// Escape

					QuitProcedure (wParam);
					return TRUE;
				}

				case 0x0D: {// Enter

					if (hasChanged == TRUE) {
						if (GetDlgCtrlID (hCtr) == IDCANCEL) QuitProcedure (wParam);
						else SendMessage (hWnd, WM_COMMAND, IDOK2, 0);
					} else {
						if (GetDlgCtrlID (hCtr) == IDOK2) SendMessage (hWnd, WM_COMMAND, IDOK2, 0);
						else QuitProcedure (wParam);
					}

					return TRUE;
				}
			}
		} break;
	}

	return DefSubclassProc (hCtr, message, wParam, lParam);
}

void SetDialogFocus (HWND hdlg, HWND hCtr) {
	SendMessage (hdlg, WM_NEXTDLGCTL, (WPARAM)hCtr, TRUE);
}

void QuitProcedure (WPARAM wParam) {
	EndDialog (hWnd, LOWORD(wParam));
	PostQuitMessage (0);
}







/* Old Code using setDefault & setFocus
case WM_KEYDOWN:
	switch (wParam) {
		case VK_UP: // Process the UP ARROW key. 
			//SetFocus(GetNextDlgTabItem(hWnd, hCtr, TRUE));
			SendMessage(hWnd, WM_NEXTDLGCTL, TRUE, FALSE);
			return FALSE;

		case VK_DOWN: // Process the DOWN ARROW key. 
			//SetFocus(GetNextDlgTabItem(hWnd, hCtr, FALSE));
			SendMessage(hWnd, WM_NEXTDLGCTL, FALSE, FALSE);
			return FALSE;

		case VK_LEFT: // Process the LEFT ARROW key. 
			MessageBox(hCtr, L"<-", L"Key was Pressed!", MB_OK);
			return TRUE;

		case VK_RIGHT: // Process the RIGHT ARROW key. 
			MessageBox(hCtr, L"->", L"Key was Pressed!", MB_OK);
			return TRUE;

		case VK_DELETE: // Process the DEL key. 
			MessageBox(hCtr, L"Delete", L"Key was Pressed!", MB_OK);
			return TRUE;

		case VK_F2: // Process the F2 key. 
			MessageBox(hCtr, L"F2", L"Key was Pressed!", MB_OK);
			return TRUE;
	}
	break;

case WM_SETFOCUS:
	if (GetDlgCtrlID(hCtr) == IDOK2) {
		//SendMessage(GetDlgItem(hWnd, IDCANCEL), 0, (LPARAM)BM_SETSTYLE, TRUE);
		//SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDOK2, (LPARAM)0);
		//MessageBeep(MB_ICONASTERISK);
		return FALSE;
	}

	// If Text did Change and It's Cancel button //
	if (hasChanged == TRUE && GetDlgCtrlID(hCtr) == IDCANCEL) {
		//SendMessage(GetDlgItem(hWnd, IDOK2), 0, (LPARAM)BM_SETSTYLE, TRUE);
		//SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDCANCEL, (LPARAM)0);
		return FALSE;
	}
	//MessageBeep(MB_ICONASTERISK);
	break;

case WM_KILLFOCUS:
	if (GetDlgCtrlID(hCtr) == IDOK2) {
		//SendMessage(GetDlgItem(hWnd, IDOK2), 0, (LPARAM)BM_SETSTYLE, TRUE);
		//SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDCANCEL, (LPARAM)0);
		//MessageBeep(MB_ICONASTERISK);
		return FALSE;
	}

	// If Text did Change and It's Cancel button //
	if (hasChanged == TRUE && GetDlgCtrlID(hCtr) == IDCANCEL) {
		//SendMessage(GetDlgItem(hWnd, IDCANCEL), 0, (LPARAM)BM_SETSTYLE, TRUE);
		//SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDOK2, (LPARAM)0);
		return FALSE;
	}

	// If Text did Change and It's Cancel button //
	//if (hasChanged == FALSE && GetDlgCtrlID(hCtr) == IDCANCEL) {
	//	SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDCANCEL, (LPARAM)0);
	//	return FALSE;
	//}
	break;

case WM_CHAR:
	switch (wParam) {
		//case 0x1B: // Escape
		//	QuitProcedure(wParam);
		//	return TRUE;

		case 0x0D: // Enter
			if (GetDlgCtrlID(hCtr) == IDCANCEL)
				QuitProcedure(wParam);
			else
				SendMessage(hWnd, WM_COMMAND, IDOK2, 0);

			
			//if (hasChanged == TRUE) {
			//	if (GetDlgCtrlID(hCtr) == IDCANCEL)
			//		SendMessage(hWnd, WM_COMMAND, IDCANCEL, 0);
			//	else
			//		SendMessage(hWnd, WM_COMMAND, IDOK2, 0);
			//} else {
			//	if (GetDlgCtrlID(hCtr) == IDOK2)
			//		SendMessage(hWnd, WM_COMMAND, IDOK2, 0);
			//	else
			//		SendMessage(hWnd, WM_COMMAND, IDCANCEL, 0);
			//
			//}
			

			return TRUE;
	}
	break;
*/

// Those whu betrayed..
//SendMessage(GetDlgItem(hWnd, IDOK2), BM_SETCHECK, (WPARAM)BST_INDETERMINATE, (LPARAM)0);
//SendMessage(GetDlgItem(hWnd, IDOK2), BM_SETSTATE, FALSE, 0);
//SendMessage(hWnd, DM_SETDEFID, (WPARAM)IDCANCEL, (LPARAM)0);			// HERE!
