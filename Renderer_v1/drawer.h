#pragma once
#include"window.h"
#include"primitives.h"

//ÌùÍ¼
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


void fillTexture(unsigned int color, Texture* texture);


void drawTriangle(unsigned int color, Texture* texture, Triangle triangle);

/*

Vertex drawVertex(unsigned int color, Texture* texture, Vertex vertex);
void drawLine(unsigned int color, Texture* texture, Vertex v1, Vertex v2);
void drawTriangle(unsigned int color, Texture* texture, Triangle triangle);

*/