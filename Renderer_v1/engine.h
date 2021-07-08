#pragma once
#include"window.h"
#include"drawer.h"
#include"effect.h"


//设备
class Device {
public:
	float* depthBuffer;
	Device() {
	}
	void createDepthBuff(Window* window);      //创建深度缓冲
};


//交换链
class SwapChain {
public:
	Texture* frontBuffer;
	Texture* backBuffer;
	SwapChain() {
		this->frontBuffer = nullptr;
		this->backBuffer = nullptr;
	}
	void getBuffer(Window* window);        //获取缓冲
	void present(Window* window);          //展示
};


//上下文
class Context {
public:
	Context() {
	}
	void clearTargetView(unsigned int color, Texture* texture);       //填充指定页面
	void drawPoints(Texture* texture, Vector3* vec, int num);         //画点
	void drawFrame(Texture* texture, Vector3* vec, int num);          //画框架
	void drawModel(Texture* texture, Vector3* vec, int num);          //画模型
	void rotateModel(Vector3* vec, int num, Vector3 axis, float a);   //旋转模型
	void rotateLight(Light* light, Vector3 axis, float a);            //旋转光源
}; 


//创建 设备、交换链、上下文
void createEngine(Device** device, SwapChain** swapChain, Context** context);

