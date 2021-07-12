#pragma once
#include"primitives.h"
#include <vector>
#include <string.h>
#include <iostream>
#include <stdio.h>

using namespace std;

class Light 
{
public:
    Vector3 position;       //位置
    Vector3 direction;      //方向
    Vector3 lightColor;     //光颜色
    float ambientStrength;  //环境光系数
    Light() {
        this->position = { 0.3f, 0.4f, -0.5f };
        this->direction = { -0.3f, -0.4f, 0.5f };
        this->lightColor = { 1.0f, 1.0f, 1.0f };     //白色
        this->ambientStrength = 0.05f;
    }
};


//获取所有图片
void getAllTex(string path, vector<string>& files, string fileType, vector<string>& fileName);  

//获取贴图缓存
void getTexBuff(string path, string name);

