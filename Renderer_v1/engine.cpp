#include"engine.h"
#include"primitives.h"
#include<math.h>


//������Ȼ���
void Device::createDepthBuff(Window* window)
{
	this->depthBuffer = new float[window->windowWidth * window->windowHeight];
}


//���� �豸����������������
void createEngine(Device** device, SwapChain** swapChain, Context** context)
{
    *device = new Device();
    *swapChain = new SwapChain();
    *context = new Context();
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


//��
void Context::draw(Texture* texture, Vector3* vec, int num)
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


//��ת
void Context::rotateModel(Vector3* vec, int num, Vector3 axis, float a)
{
	Matrix matrix;

	//��ת����
	matrix.mat[0][0] = cos(a) + (axis.x * axis.x * (1 - (cos(a))));
	matrix.mat[0][1] = axis.x * axis.y * (1 - (cos(a))) + (axis.z * (sin(a)));
	matrix.mat[0][2] = axis.x * axis.z * (1 - (cos(a))) - (axis.y * (sin(a)));
	matrix.mat[0][3] = 0.0f;

	matrix.mat[1][0] = axis.x * axis.y * (1 - (cos(a))) - (axis.z * (sin(a)));
	matrix.mat[1][1] = cos(a) + (axis.y * axis.y * (1 - (cos(a))));
	matrix.mat[1][2] = axis.y * axis.z * (1 - (cos(a))) + (axis.x * (sin(a)));
	matrix.mat[1][3] = 0.0f;

	matrix.mat[2][0] = axis.x * axis.z * (1 - (cos(a))) + (axis.y * (sin(a)));
	matrix.mat[2][1] = axis.y * axis.z * (1 - (cos(a))) - (axis.x * (sin(a)));
	matrix.mat[2][2] = cos(a) + (axis.z * axis.z * (1 - (cos(a))));
	matrix.mat[2][3] = 0.0f;

	matrix.mat[3][0] = 0.0f;
	matrix.mat[3][1] = 0.0f;
	matrix.mat[3][2] = 0.0f;
	matrix.mat[3][3] = 1.0f;

	for (int i = 0; i < num; ++i) {
		vec[i] = vector3_transform(vec[i], matrix);
	}
}

