#include"window.h"


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

