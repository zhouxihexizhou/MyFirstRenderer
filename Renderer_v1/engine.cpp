#include"engine.h"
#include"primitives.h"
#include"transform.h"
#include<math.h>


//���� �豸����������������
void createEngine(Device** device, SwapChain** swapChain, Context** context)
{
	*device = new Device();
	*swapChain = new SwapChain();
	*context = new Context();
}


//������Ȼ���
void Device::createDepthBuff(Window* window)
{
	this->depthBuffer = new float[window->windowWidth * window->windowHeight];
}


//��ȡ����
void SwapChain::getBuffer(Window* window)
{
	//����bitmap����  32λɫ
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), window->windowWidth, -window->windowHeight, 1, 32, BI_RGB,
		(DWORD)(window->windowWidth * window->windowHeight * 4), 0, 0, 0, 0 } };

	//ǰ���壬�󻺳�
	unsigned int* frontBuff;
	unsigned int* backBuff;

	this->frontBuffer = new Texture(window->windowWidth, window->windowHeight);
	this->backBuffer = new Texture(window->windowWidth, window->windowHeight);

	this->frontBuffer->tempDC = CreateCompatibleDC(window->hdc);
	this->backBuffer->tempDC = CreateCompatibleDC(window->hdc);

	this->frontBuffer->hbitmap = CreateDIBSection(frontBuffer->tempDC, &bi, DIB_RGB_COLORS, (void**)&frontBuff, 0, 0);
	this->backBuffer->hbitmap = CreateDIBSection(backBuffer->tempDC, &bi, DIB_RGB_COLORS, (void**)&backBuff, 0, 0);

	this->frontBuffer->colorBuff = frontBuff;
	this->backBuffer->colorBuff = backBuff;
}


//չʾ
void SwapChain::present(Window* window)
{
	//����ǰ�󻺳�
	Texture* mid = new Texture(window->windowWidth, window->windowHeight);
	mid = this->frontBuffer;
	this->frontBuffer = this->backBuffer;
	this->backBuffer = mid;
	(HBITMAP)SelectObject(this->frontBuffer->tempDC, this->frontBuffer->hbitmap);
	BitBlt(window->hdc, 0, 0, window->windowWidth, window->windowHeight, this->frontBuffer->tempDC, 0, 0, SRCCOPY);
}


//���ָ��ҳ��
void Context::clearTargetView(unsigned int color, Texture* texture)
{
    fillTexture(color, texture);
}


//����
void Context::drawPoints(Texture* texture, Vector3* vec, int num)
{
	Vertex v;
	for (int i = 0; i < num; ++i) {
		v.vector = vec[i];
		drawVertex(texture, v);
	}
}


//�����
void Context::drawFrame(Texture* texture, Vector3* vec, int num)
{
	Vertex v1, v2, v3;
	for (int i = 0; i <= num - 3; ++i) {
		v1.vector = vec[i];
		v2.vector = vec[i+1];
		v3.vector = vec[i+2];
		drawLine(texture, v1, v2);
		drawLine(texture, v2, v3);
		drawLine(texture, v3, v1);
	}
}


//��ģ��
void Context::drawModel(Texture* texture, Vector3* vec, int num)
{
	Triangle triangle;
	for (int i = 0; i <= num - 3; ++i) {
		if (i % 2 == 0) {    //����
			triangle.point1.vector = vec[i];
			triangle.point2.vector = vec[i+1];
			triangle.point3.vector = vec[i+2];
		}
		else {    //ż��
			triangle.point1.vector = vec[i+1];
			triangle.point2.vector = vec[i];
			triangle.point3.vector = vec[i+2];
		}
		triangle.updateTriangle();
		drawTriangle(texture, triangle);
	}
}


//��תģ��
void Context::rotateModel(Vector3* vec, int num, Vector3 axis, float a)
{
	for (int i = 0; i < num; ++i) {
		vec[i] = rotateVec(vec[i], axis, a);
	}
}


//��ת��Դ
void Context::rotateLight(Light* light, Vector3 axis, float a)
{
	light->direction = rotateVec(light->direction, axis, a);
}

