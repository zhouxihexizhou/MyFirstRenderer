#pragma once
#include"window.h"
#include"primitives.h"

//��ͼ
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


void fillTexture(unsigned int color, Texture* texture);                 //�����ͼ

Vertex drawVertex(Texture* texture, Vertex vertex);                     //����
void drawLine(Texture* texture, Vertex v1, Vertex v2);                  //����  DDA�㷨
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3);   //���������
void drawTriangle(Texture* texture, Triangle triangle);                 //��������

