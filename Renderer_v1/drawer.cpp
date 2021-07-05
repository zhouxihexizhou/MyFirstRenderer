#include"drawer.h"
#include"primitives.h"
#include"shader.h"
#include<iostream>

//Ìî³äÌùÍ¼
void fillTexture(unsigned int color, Texture* texture) 
{
	for (int row = 0; row < texture->height; ++row)
	{
		for (int col = 0; col < texture->width; ++col)
		{
			int idx = row * texture->width + col;

			(texture->colorBuff)[idx] = color;
		}
	}
}


//»­µã
Vertex drawVertex(unsigned int color, Texture* texture, Vertex vertex)
{
	Vertex v = vertexShader(color, vertex);
	int i = (int)v.vector.y * texture->width + (int)v.vector.x;
	(texture->colorBuff)[i] = color;
	return v;
}


//»­Ïß  DDAËã·¨
void drawLine(unsigned int color, Texture* texture, Vertex v1, Vertex v2)
{

	int i, j, screen_x, screen_y, s;
	float k;
	if (v1.vector.x < v2.vector.x) {
		k = (v2.vector.y - v1.vector.y) / (v2.vector.x - v1.vector.x);
		for (i = (int)v1.vector.x; i <= (int)v2.vector.x; ++i) {
			screen_x = i;
			screen_y = (int)((k * ((float)i - v1.vector.x)) + v1.vector.y);
			s = screen_y * texture->width + screen_x;
			(texture->colorBuff)[s] = color;
			if ((k > 1 || k < -1) && (screen_y < texture->height - 1)) {
				screen_y += 1;
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = color;
			}
		}
	}
	else {
		k = (v1.vector.y - v2.vector.y) / (v1.vector.x - v2.vector.x);
		for (i = (int)v2.vector.x; i <= (int)v1.vector.x; ++i) {
			screen_x = i;
			screen_y = (int)((k * ((float)i - v2.vector.x)) + v2.vector.y);
			s = screen_y * texture->width + screen_x;
			(texture->colorBuff)[s] = color;
			if ((k > 1 || k < -1) && (screen_y < texture->height - 1)) {
				screen_y += 1;
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = color;
			}
		}
	}

}


//»­Èý½ÇÐÎ
void drawTriangle(unsigned int color, Texture* texture, Triangle triangle)
{
	Vertex v1 = drawVertex(color, texture, triangle.point1);
	Vertex v2 = drawVertex(color, texture, triangle.point2);
	Vertex v3 = drawVertex(color, texture, triangle.point3);
	drawLine(color, texture, v1, v2);
	drawLine(color, texture, v2, v3);
	drawLine(color, texture, v3, v1);
}
