#include"drawer.h"
#include"primitives.h"
#include"shader.h"



//填充贴图
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


//画点
Vertex drawVertex(Texture* texture, Vertex vertex)
{
	Vertex v = vertexShader(vertex);
	int i = (int)v.vector.y * texture->width + (int)v.vector.x;
	(texture->colorBuff)[i] = v.color;
	return v;
}


//画线  DDA算法
void drawLine(Texture* texture, Vertex v1, Vertex v2)
{

	int i, j, screen_x, screen_y, s;
	float k;
	if (v1.vector.x < v2.vector.x) {
		k = (v2.vector.y - v1.vector.y) / (v2.vector.x - v1.vector.x);
		for (i = (int)v1.vector.x; i <= (int)v2.vector.x; ++i) {
			screen_x = i;
			screen_y = (int)((k * ((float)i - v1.vector.x)) + v1.vector.y);
			s = screen_y * texture->width + screen_x;
			(texture->colorBuff)[s] = v1.color;
			if ((k > 1 || k < -1) && (screen_y < texture->height - 1)) {
				screen_y += 1;
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = v1.color;
			}
		}
	}
	else {
		k = (v1.vector.y - v2.vector.y) / (v1.vector.x - v2.vector.x);
		for (i = (int)v2.vector.x; i <= (int)v1.vector.x; ++i) {
			screen_x = i;
			screen_y = (int)((k * ((float)i - v2.vector.x)) + v2.vector.y);
			s = screen_y * texture->width + screen_x;
			(texture->colorBuff)[s] = v1.color;
			if ((k > 1 || k < -1) && (screen_y < texture->height - 1)) {
				screen_y += 1;
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = v1.color;
			}
		}
	}

}


//填充三角形  scanline
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3)
{
	float xMin = v1.vector.x; if (v2.vector.x < xMin) xMin = v2.vector.x; if (v3.vector.x < xMin) xMin = v3.vector.x;
	float xMax = v1.vector.x; if (v2.vector.x > xMax) xMax = v2.vector.x; if (v3.vector.x > xMax) xMax = v3.vector.x;
	float yMin = v1.vector.y; if (v2.vector.y < yMin) yMin = v2.vector.y; if (v3.vector.y < yMin) yMin = v3.vector.y;
	float yMax = v1.vector.y; if (v2.vector.y > yMax) yMax = v2.vector.y; if (v3.vector.y > yMax) yMax = v3.vector.y;

	Vector3 a1 = (v2.vector - v1.vector) % (v3.vector - v1.vector);
	Vector3 a2 = (v3.vector - v2.vector) % (v1.vector - v2.vector);
	Vector3 a3 = (v1.vector - v3.vector) % (v2.vector - v3.vector);
	Vector3 p = v1.vector;
	Vector3 b1, b2, b3;
	int s;
	
	for (int i = xMin; i <= xMax; ++i)
	{
		for (int j = yMin; j <= yMax; ++j)
		{
			// 计算是否在三角形内部
			p.x = i;
			p.y = j;
			b1 = (v2.vector - v1.vector) % (p - v1.vector);
			b2 = (v3.vector - v2.vector) % (p - v2.vector);
			b3 = (v1.vector - v3.vector) % (p - v3.vector);

			if ((a1 * b1 >= 0) && (a2 * b2 >= 0) && (a3 * b3 >= 0)) {
				s = j * texture->width + i;
				(texture->colorBuff)[s] = v1.color;
			}
		}
	}
}


//画三角形
void drawTriangle(Texture* texture, Triangle triangle)
{
	Vertex v1 = drawVertex(texture, triangle.point1);
	Vertex v2 = drawVertex(texture, triangle.point2);
	Vertex v3 = drawVertex(texture, triangle.point3);
	//drawLine(texture, v1, v2);
	//drawLine(texture, v2, v3);
	//drawLine(texture, v3, v1);
	fillTriangle(texture, v1, v2, v3);
}

