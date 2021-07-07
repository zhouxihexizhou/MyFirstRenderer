#include<iostream>
#include"camera.h"
#include"window.h"
#include"primitives.h"
#include"engine.h"
#include"effect.h"
#include"transform.h"

using namespace std; 


//ȫ�ֱ���
Window* window = NULL;
Camera* camera = NULL;
Light* light = NULL;

Device* device = NULL;
Context* context = NULL;
SwapChain* swapChain = NULL;

unsigned int bgColor = ((65 << 16) | (105 << 8) | 225);    //������ɫ

#define bufferNums 14

Vector3 vertexBuff[14]={ 
{ -0.1f, -0.3f, 0.0f },
{ -0.3f, -0.3f, 0.0f },
{ -0.1f, -0.1f, 0.0f },
{ -0.3f, -0.1f, 0.0f },
{ -0.3f, -0.1f, 0.3f },
{ -0.3f, -0.3f, 0.0f },
{ -0.3f, -0.3f, 0.3f },
{ -0.1f, -0.3f, 0.0f },
{ -0.1f, -0.3f, 0.3f },
{ -0.1f, -0.1f, 0.0f },
{ -0.1f, -0.1f, 0.3f },
{ -0.3f, -0.1f, 0.3f },
{ -0.1f, -0.3f, 0.3f },
{ -0.3f, -0.3f, 0.3f }, };


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

	light = new Light();
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
	 
	return;
}


//��Ⱦ����
void render() 
{
	context->clearTargetView(bgColor, swapChain->backBuffer);
	context->draw(swapChain->backBuffer, vertexBuff, bufferNums);

	swapChain->present(window);
}


//�����豸
void cleanupDevice()
{
	
}

