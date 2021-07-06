#ifndef CAMERA_H
#define CAMERA_H

#include<string>
#include"primitives.h"

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

    Camera() {
        this->name = "camera";
        this->is_open = true;
        this->position = { 0.0f,0.0f,-1.0f };
        this->target = { 0.0f,0.0f,1.0f }; 
        this->xDirect = { 1.0f,0.0f,0.0f };
        this->fov = 45.0f;
        this->aspect = 1.0f;
        this->near_range = 0.5f;
        this->far_range = 1.5f;
    }

};

void free_camera(Camera* camera);        //�������
void camera_msg(Camera* camera);         //��ӡ�����Ϣ


#endif
