#pragma once
#define VERTEXNUMS 14


class MyData {
public:

	unsigned int bgColor;

	int vertexNums; 

	Vector3 vertexBuff[VERTEXNUMS];

	Vector3 axis;

	float angle;

	MyData() {

		this->bgColor = ((65 << 16) | (105 << 8) | 225);    //背景颜色

		this->vertexNums = VERTEXNUMS;                      //顶点数量

		this->vertexBuff[0] = { -0.1f, -0.3f, 0.0f };       //顶点缓冲
		this->vertexBuff[1] = { -0.3f, -0.3f, 0.0f };
		this->vertexBuff[2] = { -0.1f, -0.1f, 0.0f };
		this->vertexBuff[3] = { -0.3f, -0.1f, 0.0f };
		this->vertexBuff[4] = { -0.3f, -0.1f, 0.3f };
		this->vertexBuff[5] = { -0.3f, -0.3f, 0.0f };
		this->vertexBuff[6] = { -0.3f, -0.3f, 0.3f };
		this->vertexBuff[7] = { -0.1f, -0.3f, 0.0f };
		this->vertexBuff[8] = { -0.1f, -0.3f, 0.3f };
		this->vertexBuff[9] = { -0.1f, -0.1f, 0.0f };
		this->vertexBuff[10] = { -0.1f, -0.1f, 0.3f };
		this->vertexBuff[11] = { -0.3f, -0.1f, 0.3f };
		this->vertexBuff[12] = { -0.1f, -0.3f, 0.3f };
		this->vertexBuff[13] = { -0.3f, -0.3f, 0.3f };

		this->axis = { 0.0f, 1.0f, 0.0f };      //旋转轴

		this->angle = 0.05f;        //旋转角度
	}
};

