#include "io.hpp"

// Handle to the created file.
// No Use For Global Right Now.
HANDLE hFile = nullptr;

BOOL FileCreate (wchar_t* fName) {

	hFile = CreateFileW (
		fName,   				// name of the write
		GENERIC_WRITE,          // open for writing
		0,                      // do not share
		NULL,                   // default security
		CREATE_NEW,             // create new file only
		FILE_ATTRIBUTE_NORMAL,  // normal file
		NULL					// template
	);					

	if (hFile == INVALID_HANDLE_VALUE) {
		return FALSE;
	}

	CloseHandle (hFile);
	return TRUE;
}
