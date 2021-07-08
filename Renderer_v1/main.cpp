#include<iostream>
#include"camera.h"
#include"window.h"
#include"primitives.h"
#include"engine.h"
#include"effect.h"
#include"transform.h"
#include"database.h"


using namespace std; 


//ȫ�ֱ���
Window* window = NULL;
Camera* camera = NULL;
Light* light = NULL;

Device* device = NULL;
Context* context = NULL;
SwapChain* swapChain = NULL;

MyData* myData = NULL;

HHOOK g_Hook;    //����


//��������
void initWindow();        //��ʼ������
void initDevice();        //��ʼ���豸
void render();            //��Ⱦ����
void cleanupDevice();     //�����豸
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);       //�����¼�����


//������
int main()
{
	initWindow();
	initDevice();

	//��Ϣѭ��  
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			render();
		}
	}
	cleanupDevice();
	return (int)msg.wParam;
}


//��ʼ������
void initWindow() 
{
	window = new Window(800, 800);
	camera = new Camera();
	light = new Light();
	myData = new MyData();

	window->startWindow();
	return;
}


//��ʼ���豸
void initDevice()
{
	//���� �豸����������������
	createEngine(&device, &swapChain, &context);

	swapChain->getBuffer(window);
	device->createDepthBuff(window);

	g_Hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	
	return;
} 


//��Ⱦ����
void render() 
{
	context->clearTargetView(myData->bgColor, swapChain->backBuffer);

	//context->drawPoints(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);
	//context->drawFrame(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);
	//context->rotateLight(light, myData->axis, myData->angle);
	context->drawModel(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);
	//context->rotateModel(myData->vertexBuff, myData->vertexNums, myData->axis, myData->angle);

	swapChain->present(window);
}


//�����豸
void cleanupDevice()
{
	
}


//�����¼�����
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lparam);

	int key = (int)(p->vkCode);
	
	switch (key) {
	case 87:cout << "w" << endl; break;
	case 83:cout << "s" << endl; break;
	case 65:cout << "a" << endl; break;
	case 68:cout << "d" << endl; break;
	}

	return CallNextHookEx(g_Hook, code, wparam, lparam);
}

