#pragma once
#include "framework.hpp"

// ABOUT
//  DialogWindow - Creates a dialog based representation of a windows window that retrives input and procedures output.

extern HINSTANCE hInst;

// Creates the dialog window and assigns the DlgProc function as procedure. 
BOOL				InitDialog (HINSTANCE); 

// Procedure, reads the messages and does stuff as it hits the correct message.
//  As if it returns False it countinues via standard dialog box procedure. 
//  If it returns True program understands that the message has been proccesed by as 
//  and doesn't have to go through standard procedure anymore.
INT_PTR CALLBACK	DlgProc (HWND, UINT, WPARAM, LPARAM);

// Subclass procedure for our Edit and Button Control/s
//  When it processes our messages it countinues it's standard window procedure after.
//  Therefore all the messages that returned False or breaked goes to the DefSubclassProc procedure-function.
//  It requires commctrl.h version 6.0.0 or higer.
LRESULT CALLBACK	ControlSubclassProc (HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

// Procedure for focus managment.
//  SetFocus, and SetDefault wasn't working good at all. It somehow even managed to make 2 default buttons.
void				SetDialogFocus (HWND, HWND);

// Procedure for Quiting the Application
//  It 'should' be a good replacement for 'WM_DESTORY'.
void				QuitProcedure (WPARAM);
