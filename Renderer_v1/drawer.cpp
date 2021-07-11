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


//填充三角形  scanline
void fillTriangle(Texture* texture, Vertex v1, Vertex v2, Vertex v3)
{
	int new_x;
	Vertex temp;

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
	//裁剪
	if (v3.vector.y < 0 || v1.vector.y >= texture->height ||
		(v1.vector.x < 0 && v2.vector.x < 0 && v3.vector.x < 0) ||
		(v1.vector.x >= texture->width && v2.vector.x >= texture->width && v3.vector.x >= texture->width))
		return;

	if (v1.vector.y == v2.vector.y) {
		fillTopTri(texture, v1, v2, v3);
	}
	else if (v2.vector.y == v3.vector.y) {
		fillBottomTri(texture, v1, v2, v3);
	}
	else {
		new_x = v1.vector.x + (int)(0.5 + (float)(v2.vector.y - v1.vector.y) * (float)(v3.vector.x - v1.vector.x) / (float)(v3.vector.y - v1.vector.y));
		Vertex new_v = v2;
		new_v.vector.x = new_x;
		fillBottomTri(texture, v1, new_v, v2);
		fillTopTri(texture, v2, new_v, v3);
	}
}


//平顶三角形
void fillTopTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3)
{
	float dx_right, dx_left, xs, xe, height;
	int temp_x, temp_y, right, left, s, i;
	s = 0;
	if (v2.vector.x < v1.vector.x) {
		temp_x = v2.vector.x;
		v2.vector.x = v1.vector.x;
		v1.vector.x = temp_x;
	}
	height = v3.vector.y - v1.vector.y;
	dx_left = (v3.vector.x - v1.vector.x) / height;
	dx_right = (v3.vector.x - v2.vector.x) / height;

	xs = (float)v1.vector.x;
	xe = (float)v2.vector.x + (float)0.5;
	if (v1.vector.y < 0) {
		xs = xs + dx_left * (float)(-v1.vector.y + 0);
		xe = xe + dx_right * (float)(-v1.vector.y + 0);
		v1.vector.y = 0;
	}
	if (v3.vector.y >= texture->height) {
		v3.vector.y = texture->height - 1;
	}

	s = v1.vector.y * texture->width;
	if (v1.vector.x >= 0 && v1.vector.x < texture->width &&
		v2.vector.x >= 0 && v2.vector.x < texture->width &&
		v3.vector.x >= 0 && v3.vector.x < texture->width) {
		for (temp_y = v1.vector.y; temp_y <= v3.vector.y; temp_y++, s += texture->width) {
			for (i = s + xs; i <= s + xe; i++) {
				(texture->colorBuff)[i] = v1.color;
			}
			xs += dx_left;
			xe += dx_right;
		}
	}
	else {
		for (temp_y = v1.vector.y; temp_y <= v3.vector.y; temp_y++, s += texture->width) {
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
				if (left > texture->width) {
					continue;
				}
			}
			for (i = s + left; i <= s + right; i++) {
				(texture->colorBuff)[i] = v1.color;
			}
		}
	}
}


//平底三角形
void fillBottomTri(Texture* texture, Vertex v1, Vertex v2, Vertex v3)
{

}

