#include "OpenGLWindow.h"


void OpenGLWindow::HandleCreation()
{
	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    // Flags
		PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
		32,                   // Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                   // Number of bits for the depthbuffer
		8,                    // Number of bits for the stencilbuffer
		0,                    // Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};

	DeviceContext = GetDC(m_Hwnd);
	int PixelFormat = ChoosePixelFormat(DeviceContext, &pfd);
	SetPixelFormat(DeviceContext, PixelFormat, &pfd);
	RenderingContext = wglCreateContext(DeviceContext);
	glewInit();
}

LRESULT OpenGLWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_DESTROY:
		wglMakeCurrent(DeviceContext, nullptr);
		wglDeleteContext(RenderingContext);
		ReleaseDC(m_Hwnd, DeviceContext);
		isRunning = false;
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(this->m_Hwnd, uMsg, wParam, lParam);
}

void OpenGLWindow::Run(int nCmdShow)
{
	ShowWindow(m_Hwnd, nCmdShow);
	MainLoop = std::thread(&OpenGLWindow::OpenGlMainLoop, this);
}

void OpenGLWindow::Join()
{
	MainLoop.join();
}

void OpenGLWindow::OpenGlMainLoop()
{
	wglMakeCurrent(DeviceContext, RenderingContext);
	std::cout << glGetString(GL_VERSION) << std::endl;
	while (isRunning)
	{
		auto startTime = std::chrono::steady_clock::now();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		std::chrono::milliseconds ms(1);
		std::this_thread::sleep_for(ms);
		
		glEnd();
		SwapBuffers(GetDC(m_Hwnd));
		auto endTime = std::chrono::steady_clock::now();
		std::cout << "Time elapsed: " << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count() << " ms\n";
	}
}
