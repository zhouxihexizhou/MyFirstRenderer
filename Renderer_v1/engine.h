#pragma once
#include"window.h"
#include"drawer.h"


//�豸
class Device {
public:
	float* depthBuffer;
	Device() {
	}
	void createDepthBuff(Window* window);      //������Ȼ���
};


//������
class SwapChain {
public:
	Texture* frontBuffer;
	Texture* backBuffer;
	SwapChain() {
		this->frontBuffer = nullptr;
		this->backBuffer = nullptr;
	}
	void getBuffer(Window* window);        //��ȡ����
	void present(Window* window);          //չʾ
};


//������
class Context {
public:
	Context() {
	}
	void clearTargetView(unsigned int color, Texture* texture);       //���ָ��ҳ��
	void draw(Texture* texture, Vector3* vec, int num);
};


//���� �豸����������������
void createEngine(Device** device, SwapChain** swapChain, Context** context);

