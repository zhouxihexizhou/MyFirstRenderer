#include"engine.h"
#include"primitives.h"


//创建 设备、交换链、上下文
void createEngine(Device** device, SwapChain** swapChain, Context** context)
{
    *device = new Device();
    *swapChain = new SwapChain();
    *context = new Context();
}


//获取缓冲
void SwapChain::getBuffer(Window* window)
{
	//创建bitmap缓冲  32位色
	BITMAPINFO bi = { { sizeof(BITMAPINFOHEADER), window->windowWidth, -window->windowHeight, 1, 32, BI_RGB,
		(DWORD)(window->windowWidth * window->windowHeight * 4), 0, 0, 0, 0 } };

	//前缓冲，后缓冲
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


//展示
void SwapChain::present(Window* window)
{
	//交换前后缓冲
	Texture* mid = new Texture(window->windowWidth, window->windowHeight);
	mid = this->frontBuffer;
	this->frontBuffer = this->backBuffer;
	this->backBuffer = mid;
	(HBITMAP)SelectObject(this->frontBuffer->tempDC, this->frontBuffer->hbitmap);
	BitBlt(window->hdc, 0, 0, window->windowWidth, window->windowHeight, this->frontBuffer->tempDC, 0, 0, SRCCOPY);
}


//填充指定页面
void Context::clearTargetView(unsigned int color, Texture* texture)
{
    fillTexture(color, texture);
}


//画
void Context::draw(Texture* texture)
{
	unsigned int yellow = ((255 << 16) | (255 << 8) | 0);
	Triangle triangle;
    drawTriangle(yellow, texture, triangle);
}