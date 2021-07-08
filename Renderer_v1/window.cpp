#include"window.h"
#include<iostream>

HHOOK kbHook, mHook;    //����


//�򿪴���
void Window::startWindow()
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0; // ���뻺����
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW + 1;  // ���ڵı�����ɫ 
	wc.hCursor = NULL; // ���ڵĹ����ʽ��NULL ����Ĭ�ϵĹ����ʽ
	wc.hIcon = NULL; // ͼ��
	wc.hInstance = NULL;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"main";  // ���� sz string end of zero
	wc.style = CS_HREDRAW | CS_VREDRAW; // ���ڷ��
	wc.lpszMenuName = NULL;

	// ����ע��
	RegisterClass(&wc); // д�뵽����ϵͳ����Щ�������ǲ���ע���

	// ��������   �� ��
	HWND hWnd = CreateWindow(L"main", L"window", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, this->windowWidth, this->windowHeight, NULL, NULL, NULL, NULL);
	this->hwnd = hWnd;

	//��ȡ��ͼ����DC���
	this->hdc = GetWindowDC(hWnd);

	if (!hWnd)
		return;

	// ��ʾ����
	ShowWindow(hWnd, SW_SHOW);

	kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);

	mHook = SetWindowsHookEx(WH_MOUSE, MouseProc, 0, 0);

	return;
}


//��Ϣ������
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY: // 2
		// exit(0);
		PostQuitMessage(0); // ������ϵͳ��һ����Ϣ,�رճ���
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


//�����¼�����
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


//����¼�����
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{

	return CallNextHookEx(mHook, nCode, wParam, lParam);
}

