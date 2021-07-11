#ifndef CAMERA_H
#define CAMERA_H

#include"primitives.h"
#include<string>

using namespace std;

class Camera {

public:
    string name;            //����
    bool is_open;           //�Ƿ���
    Vector3 position;       //λ��-----------������������ϵ
    Vector3 target;         //����-----------������������ϵ
    Vector3 xDirect;        //�ҷ���----------������������ϵ
    float fov;              //��Ұ
    float aspect;           //��߱�
    float near_range;       //����Χ
    float far_range;        //Զ��Χ

    float lastX;            //���λ�ó�ʼ   Ҫ < 0.0f
    float lastY;

    float pitch;            //������
    float yaw;              //ƫ����

    Camera() {
        this->name = "camera";
        this->is_open = true;
        this->position = { 0.0f,0.0f,-1.5f };
        this->target = { 0.0f,0.0f,1.0f }; 
        this->xDirect = { 1.0f,0.0f,0.0f };
        this->fov = 45.0f;
        this->aspect = 1.0f;
        this->near_range = 0.5f;
        this->far_range = 2.5f;

        this->lastX = -10.0f; 
        this->lastY = -10.0f;

        this->pitch = 0.0f;
        this->yaw = 0.0f;
    }
};

void free_camera(Camera* camera);         //�������

#endif
