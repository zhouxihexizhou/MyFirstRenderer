#pragma once
#define VERTEXNUMS 14


Vector3 vBuff[VERTEXNUMS] = {        //顶点缓存
		{ -0.1f, -0.3f, 0.0f },
		{ -0.3f, -0.3f, 0.0f },
		{ -0.1f, -0.1f, 0.0f },
		{ -0.3f, -0.1f, 0.0f },
		{ -0.3f, -0.1f, 0.3f },
		{ -0.3f, -0.3f, 0.0f },
		{ -0.3f, -0.3f, 0.3f },
		{ -0.1f, -0.3f, 0.0f },
		{ -0.1f, -0.3f, 0.3f },
		{ -0.1f, -0.1f, 0.0f },
		{ -0.1f, -0.1f, 0.3f },
		{ -0.3f, -0.1f, 0.3f },
		{ -0.1f, -0.3f, 0.3f },
		{ -0.3f, -0.3f, 0.3f }, };


class MyData {
public:

	unsigned int bgColor;

	int vertexNums; 

	Vector3* vertexBuff;

	Vector3 axis;

	float angle;

	MyData() {

		this->bgColor = ((65 << 16) | (105 << 8) | 225);    //背景颜色

		this->vertexNums = VERTEXNUMS;                      //顶点数量

		this->vertexBuff = vBuff;                //顶点缓冲

		this->axis = { 0.0f, 1.0f, 0.0f };      //旋转轴

		this->angle = 1.0f;        //旋转角度，单位：度
	}
};

