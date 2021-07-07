#include<iostream>
#include"camera.h"
#include"window.h"
#include"primitives.h"
#include"engine.h"
#include"effect.h"
#include"transform.h"

using namespace std; 


//全局变量
Window* window = NULL;
Camera* camera = NULL;
Light* light = NULL;

Device* device = NULL;
Context* context = NULL;
SwapChain* swapChain = NULL;

unsigned int bgColor = ((65 << 16) | (105 << 8) | 225);    //背景颜色

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


//方法声明
void initWindow();        //初始化窗口
void initDevice();        //初始化设备
void render();            //渲染过程
void cleanupDevice();     //清理设备


//主函数
int main()
{
	initWindow();
	initDevice();

	//消息循环  
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


//初始化窗口
void initWindow() 
{
	window = new Window(800, 800);
	camera = new Camera();

	light = new Light();
	window->startWindow();
	return;
}


//初始化设备
void initDevice()
{
	//创建 设备、交换链、上下文
	createEngine(&device, &swapChain, &context);

	swapChain->getBuffer(window);
	device->createDepthBuff(window);
	 
	return;
}


//渲染过程
void render() 
{
	context->clearTargetView(bgColor, swapChain->backBuffer);
	context->draw(swapChain->backBuffer, vertexBuff, bufferNums);

	swapChain->present(window);
}


//清理设备
void cleanupDevice()
{
	
}

