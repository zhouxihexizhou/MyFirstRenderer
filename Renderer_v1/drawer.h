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


void fillTexture(unsigned int color, Texture* texture);                 //�����Ļ

bool outofScreen(int x, int y, float z, Texture* texture);              //�Ƿ񳬳���Ļ
void drawVertex(Texture* texture, Vertex vertex);                       //����

Vector3* colorInter(Vector3 sColor, Vector3 eColor, int num);           //��ɫ��ֵ
void drawLine(Texture* texture, Vertex v1, Vertex v2);                  //����  DDA�㷨

void drawTriangle(Texture* texture, Triangle triangle);                 //��������
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3);                                    //���������     scanline�㷨
void fillTopTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero);        //ƽ��������
void fillBottomTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero);     //ƽ�������� 

