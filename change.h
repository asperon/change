#ifndef __CHANGE_H
#define __CHANGE_H
#ifdef NDEBUG
// /Og (global optimizations), /Os (favor small code), /Oy (no frame pointers)
#pragma optimize("gsy",on)

#if _MSC_VER >= 1000
// Only supported/needed with VC6; VC5 already does 0x200 for release builds.
// Totally undocumented! And if you set it lower than 512 bytes, the program crashes.
// Either leave at 0x200 or 0x1000
#pragma comment(linker,"/FILEALIGN:0x200")
#endif // _MSC_VER >= 1000
#endif

#include "../lsapi/lsapi.h"

#define snprintf _snprintf 
#define stricmp _stricmp

typedef struct {
    char szName[512];
	char szWindow[512];
	char szMessage[512];
	char szParameters[512];
    } messageType;

void BangSend(HWND caller, char *args);
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

#ifdef __cplusplus
extern "C" {
#endif

__declspec( dllexport ) int initModule(HWND ParentWnd, HINSTANCE dllInst, wharfDataType* wd);
__declspec( dllexport ) int initModuleEx(HWND ParentWnd, HINSTANCE dllInst, LPCSTR szPath);
__declspec( dllexport ) void quitModule(HINSTANCE dllInst);

#ifdef __cplusplus
}
#endif


#endif /* __ALARM_H */
