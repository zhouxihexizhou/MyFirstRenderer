#pragma once
#include<windows.h>

class Window {
public:
    int windowWidth;
    int windowHeight;
    HWND hwnd;
    HDC hdc;    //画图窗口DC句柄

    Window() {
        this->windowWidth = 600;
        this->windowHeight = 600;
    }

    Window(int windowWidth, int windowHeight) {
        this->windowWidth = windowWidth;
        this->windowHeight = windowHeight;
    }

    void startWindow();      //打开窗口
};


LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);     //消息处理函数
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);       //键盘事件监听