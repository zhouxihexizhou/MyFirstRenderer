#include<iostream>
#include"camera.h"
#include"window.h"
#include"primitives.h"
#include"engine.h"

using namespace std; 


//ȫ�ֱ���
Window* window = NULL;
Camera* camera = NULL;

Device* device = NULL;
Context* context = NULL;
SwapChain* swapChain = NULL;

unsigned int bgColor = ((65 << 16) | (105 << 8) | 225);    //������ɫ


//��������
void initWindow();        //��ʼ������
void initDevice();        //��ʼ���豸
void render();            //��Ⱦ����
void cleanupDevice();     //�����豸


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
	window->startWindow();
	return;
}


//��ʼ���豸
void initDevice()
{
	//���� �豸����������������
	createEngine(&device, &swapChain, &context);

	swapChain->getBuffer(window);
	 
	return;
}


//��Ⱦ����
void render() 
{
	context->clearTargetView(bgColor, swapChain->backBuffer);
	context->draw(swapChain->backBuffer);

	swapChain->present(window);
}


//�����豸
void cleanupDevice()
{
	
}

