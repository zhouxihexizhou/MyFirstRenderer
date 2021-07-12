#pragma once
#include"window.h"
#include"primitives.h"

//贴图
class Texture {
public:
	int width;
	int height;
	unsigned int* colorBuff;
	HBITMAP hbitmap;
	HDC tempDC;
	Texture() {
		this->width = 600;
		this->height = 600;
	}
	Texture(int width, int height) {
		this->width = width;
		this->height = height;
	}
};


void fillTexture(unsigned int color, Texture* texture);                 //填充屏幕

bool outofScreen(int x, int y, float z, Texture* texture);              //是否超出屏幕
void drawVertex(Texture* texture, Vertex vertex);                       //画点

Vector3* colorInter(Vector3 sColor, Vector3 eColor, int num);           //颜色插值
void drawLine(Texture* texture, Vertex v1, Vertex v2);                  //画线  DDA算法

void drawTriangle(Texture* texture, Triangle triangle);                 //画三角形
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3);                                    //填充三角形     scanline算法
void fillTopTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero);        //平顶三角形
void fillBottomTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero);     //平底三角形 

