#pragma once
#include"window.h"
#include"primitives.h"
#include"camera.h"

class WorldTrans {
public:
    Matrix matrix;

    WorldTrans() {
        int i, j;                                          //默认
        for (i = 0; i < 4; ++i) {                          // 1.0f, 0.0f, 0.0f, 0.0f
            for (j = 0; j < 4; ++j) {                      // 0.0f, 1.0f, 0.0f, 0.0f
                if (i == j) {                              // 0.0f, 0.0f, 1.0f, 0.0f
                    (this->matrix).mat[i][j] = 1.0f;       // 0.0f, 0.0f, 0.0f, 1.0f
                }
                else {
                    (this->matrix).mat[i][j] = 0.0f;
                }
            }
        }
    }

    Vector3 wTrans(const Vector3& a);     //世界转换：对象坐标->世界坐标
};


class ViewTrans {
public:
    Matrix matrix;

    ViewTrans() {
        int i, j;                                          //默认
        for (i = 0; i < 4; ++i) {                          // 1.0f, 0.0f, 0.0f, 0.0f
            for (j = 0; j < 4; ++j) {                      // 0.0f, 1.0f, 0.0f, 0.0f
                if (i == j) {                              // 0.0f, 0.0f, 1.0f, 0.0f
                    (this->matrix).mat[i][j] = 1.0f;       // 0.0f, 0.0f, 1.0f, 1.0f
                }
                else {
                    (this->matrix).mat[i][j] = 0.0f;
                }
            }
        }
        (this->matrix).mat[3][2] = 1.0f;
    }

    Vector3 vTrans(const Vector3& a, const Camera& camera);    //视图转换：世界坐标->视图坐标
};


class ProjectTrans {
public:
    Matrix matrix;

    ProjectTrans() {
        (this->matrix).mat[0][0] = 2.4142f;(this->matrix).mat[0][1] = 0.0f;   (this->matrix).mat[0][2] = 0.0f;  (this->matrix).mat[0][3] = 0.0f;
        (this->matrix).mat[1][0] = 0.0f;   (this->matrix).mat[1][1] = 2.4142f;(this->matrix).mat[1][2] = 0.0f;  (this->matrix).mat[1][3] = 0.0f;
        (this->matrix).mat[2][0] = 0.0f;   (this->matrix).mat[2][1] = 0.0f;   (this->matrix).mat[2][2] = 1.5f;  (this->matrix).mat[2][3] = 1.0f;
        (this->matrix).mat[3][0] = 0.0f;   (this->matrix).mat[3][1] = 0.0f;   (this->matrix).mat[3][2] = -0.75f;(this->matrix).mat[3][3] = 0.0f;
    }

    Vector3 pTrans(const Vector3& a, const Camera& camera);    //投影转换：视图坐标->投影坐标
};


Vector3 sTrans(const Vector3& a, const Window& win);     //屏幕转换：投影坐标->屏幕坐标 
Vector3 transformAll(const Vector3& a, const Camera& camera, const Window& win);    //全部转换

