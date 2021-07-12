#include"drawer.h"
#include"primitives.h"
#include"shader.h"
#include"engine.h"
#include<iostream>

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


//画线  Bresenham算法
void drawLine(Texture* texture, Vertex v1, Vertex v2)
{
	v1 = vertexShader(v1);
	v2 = vertexShader(v2);

	int dx, dy, dx2, dy2, x_inc, y_inc, error, index, s;

	s = (int)v1.vector.y * texture->width + (int)v1.vector.x;

	dx = v2.vector.x - v1.vector.x;
	dy = v2.vector.y - v1.vector.y;

	if (dx >= 0) {
		x_inc = 1;
	}
	else {
		x_inc = -1;
		dx = -dx;
	}

	if (dy >= 0) {
		y_inc = texture->width;
	}
	else {
		y_inc = -texture->width;
		dy = -dy;
	}

	dx2 = dx * 2;
	dy2 = dy * 2;

	if (dx > dy) {
		error = dy2 - dx;
		for (index = 0; index <= dx; index++) {
			(texture->colorBuff)[s] = v1.color;
			if (error >= 0) {
				error -= dx2;
				s += y_inc;
			}
			error += dy2;
			s += x_inc;
		}
	}
	else {
		error = dx2 - dy;
		for (index = 0; index <= dy; index++) {
			(texture->colorBuff)[s] = v1.color;
			if (error >= 0) {
				error -= dy2;
				s += x_inc;
			}
			error += dx2;
			s += y_inc;
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


//填充三角形  scanline算法
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3)
{
	float new_x;
	Vertex temp;

	Vector3 normal;
	Vector3 zero;
	normal = (v2.vector - v1.vector) % (v3.vector - v1.vector);
	zero = v1.vector;

	if ((v1.vector.x == v2.vector.x && v2.vector.x == v3.vector.x) || (v1.vector.y == v2.vector.y && v2.vector.y == v3.vector.y)) {
		return;
	}
	if (v2.vector.y < v1.vector.y) {
		temp = v2;
		v2 = v1;
		v1 = temp;
	}
	if (v3.vector.y < v1.vector.y) {
		temp = v3;
		v3 = v1;
		v1 = temp;
	}
	if (v3.vector.y < v2.vector.y) {
		temp = v3;
		v3 = v2;
		v2 = temp;
	}
	//超出范围
	if (v3.vector.y < 0 || v1.vector.y >= texture->height ||
		(v1.vector.x < 0 && v2.vector.x < 0 && v3.vector.x < 0) ||
		(v1.vector.x >= texture->width && v2.vector.x >= texture->width && v3.vector.x >= texture->width))
		return;

	if (v1.vector.y == v2.vector.y) {
		fillTopTri(texture, v1, v2, v3, normal, zero);
	}
	else if (v2.vector.y == v3.vector.y) {
		fillBottomTri(texture, v1, v2, v3, normal, zero);
	}
	else {
		new_x = v1.vector.x + ((v2.vector.y - v1.vector.y) * (v3.vector.x - v1.vector.x) / (v3.vector.y - v1.vector.y));
		Vertex new_v = v2;
		new_v.vector.x = new_x;
		fillBottomTri(texture, v1, new_v, v2, normal, zero);
		fillTopTri(texture, v2, new_v, v3, normal, zero);
	}
}


//平顶三角形
void fillTopTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero)
{
	float dx_right, dx_left, xs, xe, height, xMin, xMax;
	int temp_y, right, left, s, i;
	Vertex temp;
	Vector3 m, p;
	s = 0;
	if (v2.vector.x < v1.vector.x) {
		temp = v2;
		v2 = v1;
		v1 = temp;
	}
	height = v3.vector.y - v1.vector.y;
	dx_left = (v3.vector.x - v1.vector.x) / height;
	dx_right = (v3.vector.x - v2.vector.x) / height;

	xs = v1.vector.x;
	xe = v2.vector.x;

	//裁剪
	if (v1.vector.y < 0.0f) {
		xs = xs + dx_left * (-v1.vector.y);
		xe = xe + dx_right * (-v1.vector.y);
		v1.vector.y = 0.0f;
	}
	if (v3.vector.y >= (float)texture->height) {
		v3.vector.y = (float)(texture->height - 1);
	}
	s = ((int)v1.vector.y) * texture->width;

	if (v2.vector.x < v3.vector.x) {
		xMax = v3.vector.x;
	}
	else {
		xMax = v2.vector.x;
	}
	if (v1.vector.x < v3.vector.x) {
		xMin = v1.vector.x;
	}
	else {
		xMin = v3.vector.x;
	}

	if (v1.vector.x >= 0.0f && v1.vector.x < (float)texture->width &&
		v2.vector.x >= 0.0f && v2.vector.x < (float)texture->width &&
		v3.vector.x >= 0.0f && v3.vector.x < (float)texture->width) {
		for (temp_y = (int)v1.vector.y; temp_y <= (int)v3.vector.y; temp_y++, s += texture->width) {
			for (i = s + (int)xs; i <= s + (int)xe; ++i) {

				//计算深度
				p.x = (float)(i - s);
				p.y = (float)(temp_y);
				if (normal.z != 0.0f) {
					m = p - zero;
					m.z = -((normal.x * m.x) + (normal.y * m.y)) / normal.z;
					p.z = m.z + zero.z;
				}
				else {
					p.z = 1.0f;
				}

				//深度测试
				if (p.z < device->depthBuffer[i]) {
					(texture->colorBuff)[i] = v1.color;
					device->depthBuffer[i] = p.z;
				}
			}
			xs += dx_left;
			if (xs < xMin) {
				xs = xMin;
			}
			else if (xs > xMax) {
				xs = xMax;
			}
			xe += dx_right;
			if (xe < xMin) {
				xe = xMin;
			}
			else if (xe > xMax) {
				xe = xMax;
			}
		}
	}
	else {
		for (temp_y = (int)v1.vector.y; temp_y <= (int)v3.vector.y; temp_y++, s += texture->width) {
			left = (int)xs;
			right = (int)xe;
			xs += dx_left;
			xe += dx_right;
			if (left < 0) {
				left = 0;
				if (right < 0) {
					continue;
				}
			}
			if (right >= texture->width) {
				right = texture->width - 1;
				if (left >= texture->width) {
					continue;
				}
			}
			for (i = s + left; i <= s + right; ++i) {

				//计算深度
				p.x = (float)(i - s);
				p.y = (float)(temp_y);
				if (normal.z != 0.0f) {
					m = p - zero;
					m.z = -((normal.x * m.x) + (normal.y * m.y)) / normal.z;
					p.z = m.z + zero.z;
				}
				else {
					p.z = 1.0f;
				}

				//深度测试
				if (p.z < device->depthBuffer[i]) {
					(texture->colorBuff)[i] = v1.color;
					device->depthBuffer[i] = p.z;
				}
			}
		}
	}
}


//平底三角形
void fillBottomTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3, Vector3 normal, Vector3 zero)
{
	float dx_right, dx_left, xs, xe, height, xMin, xMax;
	int temp_y, right, left, s, i;
	Vertex temp;
	Vector3 m, p;
	s = 0;
	if (v3.vector.x < v2.vector.x) {
		temp = v2;
		v2 = v3;
		v3 = temp;
	}
	height = v3.vector.y - v1.vector.y;
	dx_left = (v2.vector.x - v1.vector.x) / height;
	dx_right = (v3.vector.x - v1.vector.x) / height;

	xs = v1.vector.x;
	xe = v1.vector.x;

	if (v1.vector.y < 0.0f) {
		xs = xs + dx_left * (-v1.vector.y);
		xe = xe + dx_right * (-v1.vector.y);
		v1.vector.y = 0.0f;
	}
	if (v3.vector.y >= (float)texture->height) {
		v3.vector.y = (float)(texture->height - 1);
	}
	s = ((int)v1.vector.y) * texture->width;

	if (v1.vector.x < v3.vector.x) {
		xMax = v3.vector.x;
	}
	else {
		xMax = v1.vector.x;
	}
	if (v1.vector.x < v2.vector.x) {
		xMin = v1.vector.x;
	}
	else {
		xMin = v2.vector.x;
	}

	if (v1.vector.x >= 0.0f && v1.vector.x < (float)texture->width &&
		v2.vector.x >= 0.0f && v2.vector.x < (float)texture->width &&
		v3.vector.x >= 0.0f && v3.vector.x < (float)texture->width) {
		for (temp_y = (int)v1.vector.y; temp_y <= (int)v3.vector.y; temp_y++, s += texture->width) {
			for (i = s + (int)xs; i <= s + (int)xe; ++i) {

				//计算深度
				p.x = (float)(i - s);
				p.y = (float)temp_y;
				if (normal.z != 0.0f) {
					m = p - zero;
					m.z = -((normal.x * m.x) + (normal.y * m.y)) / normal.z;
					p.z = m.z + zero.z;
				}
				else {
					p.z = 1.0f;
				}

				//深度测试
				if (p.z < device->depthBuffer[i]) {
					(texture->colorBuff)[i] = v1.color;
					device->depthBuffer[i] = p.z;
				}
			}
			xs += dx_left;
			if (xs < xMin) {
				xs = xMin;
			}
			else if (xs > xMax) {
				xs = xMax;
			}
			xe += dx_right;
			if (xe < xMin) {
				xe = xMin;
			}
			else if (xe > xMax) {
				xe = xMax;
			}
		}
	}
	else {
		for (temp_y = (int)v1.vector.y; temp_y <= (int)v3.vector.y; temp_y++, s += texture->width) {
			left = (int)xs;
			right = (int)xe;
			xs += dx_left;
			xe += dx_right;
			if (left < 0) {
				left = 0;
				if (right < 0) {
					continue;
				}
			}
			if (right >= texture->width) {
				right = texture->width - 1;
				if (left >= texture->width) {
					continue;
				}
			}
			for (i = s + left; i <= s + right; i++) {

				//计算深度
				p.x = (float)(i - s);
				p.y = (float)(temp_y);
				if (normal.z != 0.0f) {
					m = p - zero;
					m.z = -((normal.x * m.x) + (normal.y * m.y)) / normal.z;
					p.z = m.z + zero.z;
				}
				else {
					p.z = 1.0f;
				}

				//深度测试
				if (p.z < device->depthBuffer[i]) {
					(texture->colorBuff)[i] = v1.color;
					device->depthBuffer[i] = p.z;
				}
			}
		}
	}
}

