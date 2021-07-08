#pragma once
#include"window.h"
#include"drawer.h"
#include"effect.h"


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
	void drawPoints(Texture* texture, Vector3* vec, int num);         //����
	void drawFrame(Texture* texture, Vector3* vec, int num);          //�����
	void drawModel(Texture* texture, Vector3* vec, int num);          //��ģ��
	void rotateModel(Vector3* vec, int num, Vector3 axis, float a);   //��תģ��
	void rotateLight(Light* light, Vector3 axis, float a);            //��ת��Դ
}; 


//���� �豸����������������
void createEngine(Device** device, SwapChain** swapChain, Context** context);

