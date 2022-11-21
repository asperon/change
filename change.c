#include <stdio.h>
#include <windows.h>
#include <string.h>
#include "change.h"

const char rcsRevision[] = "$Revision: 0.1 $"; 
const char rcsId[] = "$Id: ChangeLine version 0.1 coded by Asperon  $"; 
char szLitestepPath[256];
char szAppName[] = "ChangeLine";
HWND parent;
HWND hMainWnd;

// Function done by slimer (ola@miranda.org) thnx!
int osncmp(char *str,char *str2,int l)
{
	int i;

	if (strlen(str) < l)
		return -1;
	if (strlen(str2) < l)
		return 1;

	for (i=0;i<l;i++)
		if (str[i] != str2[i])
			return -1;

	return 0;
}

// Function done by slimer (ola@miranda.org) thnx!
char *osstr(char *haystack,char *needle)
{
	int i=0;

	while (haystack[i] != '\0') {
		if (osncmp(haystack+i,needle,strlen(needle))==0)
			return haystack+i;
		i++;
	}

	return NULL;
}

cToUpper(char *sPtr)
{
	while (*sPtr != '\0') {
		*sPtr = toupper(*sPtr);
		++sPtr;
	}


}

void BangChangeLine(HWND caller, char *args) {

	FILE *f, *sr;
	char tmpline[256];
	char line[256];
	char source[256];
	char target[256];
	char szToken1[256];
	char szToken2[256];
	char szToken3[256];
	int mode = 0;
	
	LPTSTR rgszTokens[3];
	
	rgszTokens[0] = szToken1;
	rgszTokens[1] = szToken2;		
	rgszTokens[2] = szToken3;
	
	if(CommandTokenize(args, rgszTokens, 3, NULL ) == 3) {

		cToUpper(szToken3);
		if (osncmp(szToken3,"SUBSTRING",256) == 0) {
			mode = 1;
		}

		if (osncmp(szToken3,"FORCE",256) == 0) {
			mode = 2;
		}

		strcpy(source, szLitestepPath);
		strcat(source, "\\step.rc");
		sr = fopen(source, "r");

		strcpy(target, szLitestepPath);
		strcat(target, "\\temp.rc");
		f = fopen(target, "w");

		while (fgets(line,256,sr) != NULL) {
			strcpy(tmpline,line);
			cToUpper(tmpline);
			if (osstr(tmpline, "!CHANGELINE") == NULL) {
				if (mode == 1) {
					if (osstr(line, szToken1) != NULL) {
						fprintf(f,"%s\n",szToken2);
					} else {
						fprintf(f, "%s", line);
					}
				} else {
					if (osncmp(line,szToken1,strlen(szToken1)) == 0) {
						if (mode == 2) {
							mode = 0;
						}
						fprintf(f,"%s\n",szToken2);
					} else {
						fprintf(f, "%s", line);
					}	
				}
			} else {
				fprintf(f, "%s", line);
			}
		}

		if (mode == 2) {
			fprintf(f,"%s\n",szToken2);
		}
		fclose(f);
		fclose(sr);
		strcpy(line, szLitestepPath);

		CopyFile(source, line, 0);
		CopyFile(target, source, 0);
		DeleteFile(target);
	}
}


int initModule(HWND ParentWnd, HINSTANCE dllInst, wharfDataType* wd) {
	return initModuleEx (ParentWnd, dllInst, wd->lsPath);
}

int initModuleEx(HWND ParentWnd, HINSTANCE dllInst, LPCSTR szPath) {

	int Msgs[10];
	strcpy(szLitestepPath, szPath);

	parent = ParentWnd;
	{
		WNDCLASS wc;
		memset(&wc, 0, sizeof(wc));
		wc.lpfnWndProc = WndProc;
		wc.hInstance = dllInst;
		wc.lpszClassName = szAppName;
		wc.style = 0;

		if (!RegisterClass(&wc)) {
			MessageBox(hMainWnd, "Error registering window class", szAppName, MB_OK);
			return 1;
		}
	}
	hMainWnd = CreateWindowEx(WS_EX_TOOLWINDOW,szAppName,szAppName,WS_CHILD,0,0,0,0,parent,NULL,dllInst,NULL);

	Msgs[0] = LM_GETREVID;
	Msgs[1] = 0;
	SendMessage(parent, LM_REGISTERMESSAGE, (WPARAM) hMainWnd, (LPARAM) Msgs);

	AddBangCommand("!CHANGELINE", BangChangeLine);
	return 0;
}

void quitModule(HINSTANCE dllInst) {
	RemoveBangCommand("!CHANGELINE");
	DestroyWindow(hMainWnd);
	UnregisterClass(szAppName, dllInst);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {

	switch (message) {
		case LM_GETREVID: {
			char *buf = (char *) lParam;

			if (wParam == 0) {
				strcpy(buf, "change.dll (coded by asperon): ");
				strcat(buf, &rcsRevision[11]);
				buf[strlen(buf)-1] = '\0';
			}
			else if (wParam == 1) {
				strcpy(buf, &rcsId[1]);
				buf[strlen(buf)-1] = '\0';
			} else {
				strcpy(buf, "");
			}
			return strlen(buf);
		}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}