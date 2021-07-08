#pragma once
#define VERTEXNUMS 14


Vector3 vBuff[VERTEXNUMS] = {        //���㻺��
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

		this->bgColor = ((65 << 16) | (105 << 8) | 225);    //������ɫ

		this->vertexNums = VERTEXNUMS;                      //��������

		this->vertexBuff = vBuff;                //���㻺��

		this->axis = { 0.0f, 1.0f, 0.0f };      //��ת��

		this->angle = 1.0f;        //��ת�Ƕȣ���λ����
	}
};

