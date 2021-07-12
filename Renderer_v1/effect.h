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
    Vector3 position;       //λ��
    Vector3 direction;      //����
    Vector3 lightColor;     //����ɫ
    float ambientStrength;  //������ϵ��
    Light() {
        this->position = { 0.3f, 0.4f, -0.5f };
        this->direction = { -0.3f, -0.4f, 0.5f };
        this->lightColor = { 1.0f, 1.0f, 1.0f };     //��ɫ
        this->ambientStrength = 0.05f;
    }
};


//��ȡ����ͼƬ
void getAllTex(string path, vector<string>& files, string fileType, vector<string>& fileName);  

//��ȡ��ͼ����
void getTexBuff(string path, string name);

