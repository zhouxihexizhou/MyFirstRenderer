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


void fillTexture(unsigned int color, Texture* texture);                 //Ìî³äÆÁÄ»

bool outofScreen(int x, int y, float z, Texture* texture);              //ÊÇ·ñ³¬³öÆÁÄ»

void drawVertex(Texture* texture, Vertex vertex);                       //»­µã
void drawLine(Texture* texture, Vertex v1, Vertex v2);                  //»­Ïß  DDAËã·¨
void drawTriangle(Texture* texture, Triangle triangle);                 //»­Èı½ÇĞÎ

void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3);   //Ìî³äÈı½ÇĞÎ

