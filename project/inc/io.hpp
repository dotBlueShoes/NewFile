#pragma once
#include "framework.hpp"

// ABOUT
//  CreateFile - Function and a handle to the File being created via function.

extern HANDLE hFile; 

// Function creating and validating new file.
BOOL FileCreate (wchar_t* fName);
