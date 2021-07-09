#include<iostream>
#include"camera.h"
#include"window.h"
#include"primitives.h"
#include"engine.h"
#include"effect.h"
#include"transform.h"
#include"database.h"


using namespace std; 


//全局变量
Window* window = NULL;
Camera* camera = NULL;
Light* light = NULL;

Device* device = NULL;
Context* context = NULL;
SwapChain* swapChain = NULL;

MyData* myData = NULL;

HHOOK kbHook, mHook;    //钩子


//方法声明
void initWindow();        //初始化窗口
void initDevice();        //初始化设备
void render();            //渲染过程
void cleanupDevice();     //清理设备
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam);           //键盘事件监听
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);             //鼠标事件监听


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
	myData = new MyData();

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

	//设置键盘，鼠标监听
	kbHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	mHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, 0, 0);
	
	return;
} 


//渲染过程
void render() 
{
	context->clearTargetView(myData->bgColor, swapChain->backBuffer);

	//context->drawPoints(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);
	//context->drawFrame(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);
	//context->rotateModel(myData->vertexBuff, myData->vertexNums, myData->axis, myData->angle);
	//context->rotateLight(light, myData->axis, myData->angle);

	context->drawModel(swapChain->backBuffer, myData->vertexBuff, myData->vertexNums);

	swapChain->present(window);
}


//清理设备
void cleanupDevice()
{
	
}


//键盘事件监听
LRESULT CALLBACK KeyboardProc(int code, WPARAM wparam, LPARAM lparam)
{
	PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lparam);

	int key = (int)(p->vkCode);

	//相机移动
	switch (key) {
	case 87:      //w
		camera->position = moveVec(camera->position, numMulVec(myData->moveSpeed / 100, camera->target));
		break;
	case 83:      //s
		; camera->position = moveVec(camera->position, numMulVec((-1.0f) * myData->moveSpeed / 100, camera->target));
		break; break;
	case 65:      //a
		camera->position = moveVec(camera->position, numMulVec((-1.0f) * myData->moveSpeed / 100, camera->xDirect));
		break; break;
	case 68:      //d
		camera->position = moveVec(camera->position, numMulVec(myData->moveSpeed / 100, camera->xDirect));
		break; break;
	case 74:      //j
		context->rotateModel(myData->vertexBuff, myData->vertexNums, myData->axis, myData->angle);
		break; break;
	case 75:      //k
		context->rotateLight(light, myData->axis, myData->angle);
		break; break;
	}

	return CallNextHookEx(kbHook, code, wparam, lparam);
}


//鼠标事件监听
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPMSLLHOOKSTRUCT p = (LPMSLLHOOKSTRUCT)lParam;
	POINT   pt = p->pt;

	//角度化弧度，acos(-1)=pi
	float a = myData->rotateSpeed / (180 / acos(-1));

	if (camera->lastX < 0.0f || camera->lastY < 0.0f) {
	}
	else {
		//相机旋转
		float xoffset = camera->lastX - pt.x;
		float yoffset = camera->lastY - pt.y;

		float yaw = (xoffset * a);
		float pitch = (yoffset * a);

		Vector3 target = camera->target;
		Vector3 xDirect = camera->xDirect;

		camera->target = rotateVec(camera->target, xDirect, pitch);
		camera->target = rotateVec(camera->target, (target % xDirect), yaw);
		camera->xDirect = rotateVec(camera->xDirect, (target % xDirect), yaw);
	}
	camera->lastX = pt.x;
	camera->lastY = pt.y;

	return CallNextHookEx(mHook, nCode, wParam, lParam);
}

