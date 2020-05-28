#pragma once
#include "BaseWindow.h"
#include <GL/glew.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>

class OpenGLWindow : public BaseWindow<OpenGLWindow>
{
private:
	HGLRC RenderingContext;
	HDC DeviceContext;
	std::thread MainLoop;
	std::atomic<bool> isRunning = true;
public:
	inline virtual LPCSTR ClassName() const { return "OpenGL Window"; }
	virtual void HandleCreation();
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void Run(int nCmdShow);
	void Join();
	void OpenGlMainLoop();
};