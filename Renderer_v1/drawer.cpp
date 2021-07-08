#include"drawer.h"
#include"primitives.h"
#include"shader.h"
#include"engine.h"

extern Device* device;


//填充贴图
void fillTexture(unsigned int color, Texture* texture) 
{
	for (int row = 0; row < texture->height; ++row)
	{
		for (int col = 0; col < texture->width; ++col)
		{
			int idx = row * texture->width + col;

			(texture->colorBuff)[idx] = color;

			device->depthBuffer[idx] = 1.0f;
		}
	}
}


//是否超出屏幕
bool outofScreen(int x, int y, float z, Texture* texture)
{
	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height && z >= 0.0f && z <= 1.0f) {
		return false;
	}
	else {
		return true;
	}
}


//画点
void drawVertex(Texture* texture, Vertex vertex)
{
	//顶点着色器
	Vertex v = vertexShader(vertex);

	//未超出屏幕
	if (!(outofScreen((int)v.vector.x, (int)v.vector.y, v.vector.z, texture))) {
		int i = (int)v.vector.y * texture->width + (int)v.vector.x;
		(texture->colorBuff)[i] = v.color;
	}
	return;
}


//画线  DDA算法
void drawLine(Texture* texture, Vertex v1, Vertex v2)
{
	v1 = vertexShader(v1);
	v2 = vertexShader(v2);

	Vertex xMin, xMax, yMin, yMax;
	int i, screen_x, screen_y, s, situation;
	float k1, k2, z;

	if (v1.vector.x < v2.vector.x) {
		xMin = v1;
		xMax = v2;
		situation = 1;
	}
	else if (v1.vector.x > v2.vector.x) {
		xMin = v2;
		xMax = v1;
		situation = 1;
	}
	else {
		situation = 2;
		if (v1.vector.y < v2.vector.y) {
			yMin = v1;
			yMax = v2;
		}
		else if (v1.vector.y > v2.vector.y) {
			yMin = v2;
			yMax = v1;
		}
		else {
			situation = 3;
		}
	}

	if (situation == 1) {
		k1 = (xMax.vector.y - xMin.vector.y) / (xMax.vector.x - xMin.vector.x);
		k2 = (xMax.vector.z - xMin.vector.z) / (xMax.vector.x - xMin.vector.x);
		for (i = (int)xMin.vector.x; i <= (int)xMax.vector.x; ++i) {
			screen_x = i;
			screen_y = (int)((k1 * ((float)i - xMin.vector.x)) + xMin.vector.y);
			z = k2 * ((float)i - xMin.vector.x) + xMin.vector.z;

			//未超出屏幕
			if (!(outofScreen(screen_x, screen_y, z, texture))) {
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = xMin.color;
				if ((k1 > 1 || k1 < -1) && (screen_y < texture->height - 1)) {
					screen_y += 1;
					s = screen_y * texture->width + screen_x;
					(texture->colorBuff)[s] = xMin.color;
				}
			}
		}
	}
	else if (situation == 2) {
		screen_x = yMin.vector.x;
		for (i = (int)yMin.vector.y; i <= (int)yMax.vector.y; ++i) {
			screen_y = i;
			k2 = (i - yMin.vector.y) / (yMax.vector.y - yMin.vector.y);
			z = k2 * (yMax.vector.z - yMin.vector.z) + yMin.vector.z;

			//未超出屏幕
			if (!(outofScreen(screen_x, screen_y, z, texture))) {
				s = screen_y * texture->width + screen_x;
				(texture->colorBuff)[s] = xMin.color;
			}
		}
	}
	else if (situation == 3) {
		screen_x = v1.vector.x;
		screen_y = v1.vector.y;
		if (v1.vector.z < v2.vector.z) {
			z = v1.vector.z;
		}
		else {
			z = v2.vector.z;
		}

		//未超出屏幕
		if (!(outofScreen(screen_x, screen_y, z, texture))) {
			s = screen_y * texture->width + screen_x;
			(texture->colorBuff)[s] = v1.color;
		}
	}
}


//画三角形
void drawTriangle(Texture* texture, Triangle triangle)
{
	Vertex v1 = vertexShader(triangle.point1);
	Vertex v2 = vertexShader(triangle.point2);
	Vertex v3 = vertexShader(triangle.point3);
	fillTriangle(texture, v1, v2, v3);
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
	Vertex p = v1;
	Vector3 m;
	Vector3 b1, b2, b3;
	int s;

	for (int i = xMin; i <= xMax; ++i)
	{
		for (int j = yMin; j <= yMax; ++j)
		{
			// 计算是否在三角形内部
			p.vector.x = i;
			p.vector.y = j;
			b1 = (v2.vector - v1.vector) % (p.vector - v1.vector);
			b2 = (v3.vector - v2.vector) % (p.vector - v2.vector);
			b3 = (v1.vector - v3.vector) % (p.vector - v3.vector);

			//在三角形内
			if ((a1 * b1 >= 0) && (a2 * b2 >= 0) && (a3 * b3 >= 0)) {

				if (a1.z != 0.0f) {
					m = p.vector - v1.vector;
					m.z = -((a1.x * m.x) + (a1.y * m.y)) / a1.z;
					p.vector.z = m.z + v1.vector.z;
				}
				else {
					p.vector.z = 1.0f;
				}

				//裁剪
				if (i >= 0 && i < texture->width && j >= 0 && j < texture->height && p.vector.z >= 0.0f && p.vector.z <= 1.0f) {
				    
					//深度测试 
					s = j * texture->width + i;
					if (p.vector.z <= device->depthBuffer[s]) {

						//像素着色器
						p = pixelShader(p);

						(texture->colorBuff)[s] = p.color;
						device->depthBuffer[s] = p.vector.z;
					}
				}
			}
		}
	}
}

