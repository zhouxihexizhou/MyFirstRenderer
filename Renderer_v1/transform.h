#pragma once
#include"window.h"
#include"primitives.h"
#include"camera.h"

class WorldTrans {   
public:
    Matrix matrix;      //默认单位矩阵

    WorldTrans() {
    }

    Vector3 wTrans(const Vector3& a);     //世界转换：对象坐标->世界坐标
};


class ViewTrans {
public:                                                    //默认
    Matrix matrix;                                         // 1.0f, 0.0f, 0.0f, 0.0f
                                                           // 0.0f, 1.0f, 0.0f, 0.0f
    ViewTrans() {                                          // 0.0f, 0.0f, 1.0f, 0.0f
        (this->matrix).mat[3][2] = 1.0f;                   // 0.0f, 0.0f, 1.0f, 1.0f
    }

    Vector3 vTrans(const Vector3& a, const Camera& camera);    //视图转换：世界坐标->视图坐标
};



class ProjectTrans {
public:
    Matrix matrix;

    ProjectTrans() {
        (this->matrix).mat[0][0] = 2.4142f;        // 2.4142f, 0.0f, 0.0f, 0.0f
        (this->matrix).mat[1][1] = 2.4142f;        // 0.0f, 2.4142f, 0.0f, 0.0f
        (this->matrix).mat[2][2] = 1.5f;           // 0.0f, 0.0f, 1.5f, 1.0f
        (this->matrix).mat[2][3] = 1.0f;           // 0.0f, 0.0f, -0.75f, 0.0f
        (this->matrix).mat[3][2] = -0.75f;
        (this->matrix).mat[3][3] = 0.0f;
    }

    Vector3 pTrans(const Vector3& a, const Camera& camera);    //投影转换：视图坐标->投影坐标
};


Vector3 sTrans(const Vector3& a, const Window& win);     //屏幕转换：投影坐标->屏幕坐标 
Vector3 transformAll(const Vector3& a, const Camera& camera, const Window& win);    //全部转换

unsigned int vecToInt(Vector3 v);        //类型转换：Vector3 -> unsigned int 
Vector3 vecNormalize(Vector3 vector);    //三维向量单位化

Vector3 rotateVec(Vector3 vec, Vector3 axis, float a);      //旋转
Vector3 moveVec(Vector3 vec, Vector3 target);               //平移

