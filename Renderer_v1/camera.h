#ifndef CAMERA_H
#define CAMERA_H

#include<string>
#include"primitives.h"

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

void free_camera(Camera* camera);        //销毁相机
void camera_msg(Camera* camera);         //打印相机信息


#endif
