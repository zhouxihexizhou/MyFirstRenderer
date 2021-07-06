#pragma once
#include"window.h"
#include"drawer.h"


//设备
class Device {
public:
	Device() {
	}
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
	void draw(Texture* texture, Vector3* vec, int num);
};


//创建 设备、交换链、上下文
void createEngine(Device** device, SwapChain** swapChain, Context** context);

