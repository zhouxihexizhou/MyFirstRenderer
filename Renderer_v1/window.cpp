#include"window.h"
#include<iostream>

HHOOK kbHook, mHook;    //钩子


//打开窗口
void Window::startWindow()
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0; // 申请缓冲区
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;  // 窗口的背景颜色 
	wc.hCursor = NULL; // 窗口的光标样式，NULL 就是默认的光标样式
	wc.hIcon = NULL; // 图标
	wc.hInstance = NULL;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"main";  // 代表 sz string end of zero
	wc.style = CS_HREDRAW | CS_VREDRAW; // 窗口风格
	wc.lpszMenuName = NULL;

	// 进行注册
	RegisterClass(&wc); // 写入到操作系统，有些窗口类是不用注册的

	// 创建窗口   宽 高
	HWND hWnd = CreateWindow(L"main", L"window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, this->windowWidth, this->windowHeight, NULL, NULL, NULL, NULL);
	this->hwnd = hWnd;

	//获取画图窗口DC句柄
	this->hdc = GetWindowDC(hWnd);

	if (!hWnd)
		return;

	// 显示窗口
	ShowWindow(hWnd, SW_SHOW);

	kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

	mHook = SetWindowsHookEx(WH_MOUSE, MouseProc, 0, 0);

	return;
}


//消息处理函数
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: // 2
		// exit(0);
		PostQuitMessage(0); // 给操作系统发一个消息,关闭程序
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//键盘事件监听
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lparam);

	int key = (int)(p->vkCode);

	switch (key) {
	case 87:std::cout << "w" << std::endl; break;
	case 83:std::cout << "s" << std::endl; break;
	case 65:std::cout << "a" << std::endl; break;
	case 68:std::cout << "d" << std::endl; break;
	}

	return CallNextHookEx(kbHook, code, wparam, lparam);
}


//鼠标事件监听
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	return CallNextHookEx(mHook, nCode, wParam, lParam);
}

