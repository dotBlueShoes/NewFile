#pragma once

#include "../res/targetver.h"
#include "../res/resource.h"


#define WIN32_LEAN_AND_MEAN         // Wyklucz rzadko używane rzeczy z nagłówków systemu Windows       
#include <windows.h>                // Pliki nagłówkowe systemu Windows

// Only `dialogWindow` uses it for Subclassing
// ??? Still is there a better way to connect it / other / better
#pragma comment(lib, "comctl32.lib")
#include <commctrl.h>

#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
