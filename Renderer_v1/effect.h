#pragma once
#include"primitives.h"


class Light 
{
public:
    Vector3 position;       //位置
    Vector3 direction;      //方向
    Vector3 lightColor;     //光颜色
    float ambientStrength;  //环境光系数
    Light() {
        this->position = { 0.5f, 0.5f, -0.5f };
        this->direction = { -0.5f, -0.5f, 0.5f };
        this->lightColor = { 1.0f, 1.0f, 1.0f };     //白色
        this->ambientStrength = 0.1f;
    }
};

