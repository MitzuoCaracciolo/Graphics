#include <Windows.h>
#include <iostream>

#include "GUI/OpenGLWindow.h"

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR pCmdLine, int nCmdShow)
{
	FILE* fp;
	AllocConsole();
	freopen_s(&fp, "CONIN$", "r", stdin);
	freopen_s(&fp, "CONOUT$", "w", stdout);

	OpenGLWindow glWnd;
	glWnd.Create("OpenGL Window", 640, 400);
	glWnd.Run(nCmdShow);

	MSG msg = {};
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	glWnd.Join();
	return 0;
}