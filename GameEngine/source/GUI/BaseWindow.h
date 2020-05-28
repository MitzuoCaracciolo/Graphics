#pragma once
#include <Windows.h>

/////////////////////////////////////////////////////////////////////
//Posteriormente adicionar métodos mais localizados para modificar //
//as propriedades da janela, como WNDCLASS, comprimento, largura,  //
//x, y, estilos, etc...	Antes de chamar o método de Criar a janela //
/////////////////////////////////////////////////////////////////////

template<typename DERIVED_TYPE>
class BaseWindow
{
protected:
	HWND m_Hwnd;
	inline virtual LPCSTR ClassName() const = 0;
	virtual void HandleCreation() = 0;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
public:
	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	BOOL Create(LPCSTR lpWindowName,
		int nWidth = CW_USEDEFAULT,
		int nHeight = CW_USEDEFAULT,
		int x = CW_USEDEFAULT,
		int y = CW_USEDEFAULT,
		HWND hWndParent = 0,
		DWORD dwStyle = WS_OVERLAPPEDWINDOW,
		DWORD dwExStyle = 0,
		HMENU hMenu = 0);

	inline HWND Window() const { return m_Hwnd; }
};

template<typename DERIVED_TYPE>
void BaseWindow<DERIVED_TYPE>::HandleCreation()
{
}

template<typename DERIVED_TYPE>
LRESULT CALLBACK BaseWindow<DERIVED_TYPE>::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	DERIVED_TYPE *pThis = nullptr;
	if (uMsg == WM_CREATE)
	{
		CREATESTRUCT* pCreate = (CREATESTRUCT*)lParam;
		pThis = (DERIVED_TYPE*)pCreate->lpCreateParams;
		SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)pThis);
		pThis->m_Hwnd = hwnd;
		pThis->HandleCreation();
	}
	else
	{
		LONG_PTR ptr = GetWindowLongPtr(hwnd, GWLP_USERDATA);
		pThis = reinterpret_cast<DERIVED_TYPE*>(ptr);
	}
	if (pThis)
		return pThis->HandleMessage(uMsg, wParam, lParam);
	else
		return DefWindowProc(hwnd, uMsg, wParam, lParam);

}
template<typename DERIVED_TYPE>
BOOL BaseWindow<DERIVED_TYPE>::Create(LPCSTR lpWindowName, int nWidth,	int nHeight, int x,	int y, HWND hWndParent, DWORD dwStyle, DWORD dwExStyle, HMENU hMenu)
{
	WNDCLASS wc = { };
	wc.lpfnWndProc = DERIVED_TYPE::WindowProc;
	wc.hInstance = GetModuleHandle(nullptr);
	wc.lpszClassName = ClassName();
	wc.style = CS_OWNDC;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);

	RegisterClass(&wc);

	m_Hwnd = CreateWindowEx(
		dwExStyle,
		ClassName(),
		lpWindowName,
		dwStyle,
		x,
		y,
		nWidth,
		nHeight,
		hWndParent,
		hMenu,
		GetModuleHandle(NULL),
		this
	);

	return (m_Hwnd == nullptr ? false : true);
}