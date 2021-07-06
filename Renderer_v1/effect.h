#pragma once
#include"primitives.h"


class Light 
{
public:
    Vector3 position;       //λ��
    Vector3 direction;      //����
    Vector3 lightColor;     //����ɫ
    float ambientStrength;  //������ϵ��
    Light() {
        this->position = { 0.5f, 0.5f, -0.5f };
        this->direction = { -0.5f, -0.5f, 0.5f };
        this->lightColor = { 1.0f, 1.0f, 1.0f };     //��ɫ
        this->ambientStrength = 0.1f;
    }
};

