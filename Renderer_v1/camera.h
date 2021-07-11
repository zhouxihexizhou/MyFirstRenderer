#ifndef CAMERA_H
#define CAMERA_H

#include"primitives.h"
#include<string>

using namespace std;

class Camera {

public:
    string name;            //名字
    bool is_open;           //是否开启
    Vector3 position;       //位置-----------基于世界坐标系
    Vector3 target;         //方向-----------基于世界坐标系
    Vector3 xDirect;        //右方向----------基于世界坐标系
    float fov;              //视野
    float aspect;           //宽高比
    float near_range;       //近范围
    float far_range;        //远范围

    float lastX;            //相机位置初始   要 < 0.0f
    float lastY;

    float pitch;            //俯仰角
    float yaw;              //偏航角

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

void free_camera(Camera* camera);         //销毁相机

#endif
