#pragma once
#include<windows.h>

class Window {
public:
    int windowWidth;
    int windowHeight;
    HWND hwnd;
    HDC hdc;    //��ͼ����DC���

    Window() {
        this->windowWidth = 600;
        this->windowHeight = 600;
    }

    Window(int windowWidth, int windowHeight) {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
    }

    void startWindow();      //�򿪴���
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);     //��Ϣ������
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);       //�����¼�����