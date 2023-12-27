#include "../Headers/BaseWindow.h"



BaseWindow::WindowClass BaseWindow::WindowClass::wndClass;


BaseWindow::WindowClass::WindowClass() noexcept
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX winClass = { 0 };
	winClass.cbSize = sizeof(winClass);
	winClass.style = CS_OWNDC;
	winClass.lpfnWndProc = HandleMsgSetup;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = GetInstance();
	winClass.hIcon = nullptr;
	winClass.hCursor = nullptr;
	winClass.hbrBackground = nullptr;
	winClass.lpszMenuName = nullptr;
	winClass.lpszClassName = GetName();
	winClass.hIconSm = nullptr;


	RegisterClassEx(&winClass);
}


BaseWindow::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* BaseWindow::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE BaseWindow::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}




BaseWindow::BaseWindow(int width, int height, const char* title) 
	: width(width), height(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	if (FAILED(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE)))
	{
		
	};


	handleWin = CreateWindow(
		WindowClass::GetName(),
		title,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		wr.right - wr.left,
		wr.bottom - wr.top,
		nullptr,
		nullptr,
		WindowClass::GetInstance(),
		this
	);

	if (handleWin == nullptr)
	{
		
	}

	ShowWindow(handleWin, SW_SHOWDEFAULT);
}

BaseWindow::~BaseWindow()
{
	DestroyWindow(handleWin);
}


void BaseWindow::Update()
{
}

void BaseWindow::Draw()
{
}


LRESULT WINAPI  BaseWindow::HandleMsgSetup(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)
	{

		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);

		BaseWindow* const pWnd = static_cast<BaseWindow*>(pCreate->lpCreateParams);

		SetWindowLongPtr(handleWin, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));

		SetWindowLongPtr(handleWin, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&BaseWindow::HandleMsgThunk));

		return pWnd->HandleMsg(handleWin, msg, wParam, lParam);
	}

	return DefWindowProc(handleWin, msg, wParam, lParam);
}

LRESULT WINAPI  BaseWindow::HandleMsgThunk(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{

	BaseWindow* const pWnd = reinterpret_cast<BaseWindow*>(GetWindowLongPtr(handleWin, GWLP_USERDATA));

	return pWnd->HandleMsg(handleWin, msg, wParam, lParam);
}

void BaseWindow::OnMessage(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	DefWindowProc(handleWin, msg, wParam, lParam);
}

LRESULT BaseWindow::HandleMsg(HWND handleWin, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(handleWin, msg, wParam, lParam);
}