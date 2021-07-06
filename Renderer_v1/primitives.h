#pragma once

//矩阵
class Matrix {
public:
    float mat[4][4];
};

//点
class Vector3 {
public:
    float x, y, z;

    Vector3() {
        this->x = 0.0f;
        this->y = 0.0f;
        this->z = 0.0f;
    }

    Vector3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }
};


//顶点
class Vertex {
public:
    Vector3 vector;    //方向向量
    Vector3 normal;    //法向量

    unsigned int color;
    Vector3 vColor;

    Vertex() {
        this->vector = { 0.0f, 0.0f, 0.0f };
        this->color = ((255 << 16) | (255 << 8) | 255);
        this->vColor = { 1.0f, 1.0f, 1.0f };
    }
};


//三角形
class Triangle {
public:
    Vertex point1;
    Vertex point2;
    Vertex point3;

    Triangle() {
        (this->point1).vector = { -0.3f, -0.3f, 0.0f };
        (this->point2).vector = { 0.0f, 0.3f, 0.0f };
        (this->point3).vector = { 0.3f, -0.3f, 0.0f };
    }
    void updateTriangle();       //更新顶点信息：法向量
};


//数学库
Vector3 vector3_scale(const Vector3& a, const float k);          //三维矢量缩放
Vector3 vector3_transform(const Vector3& a, const Matrix& m);    //三维矢量通过矩阵变换


Vector3 operator+(const Vector3& a, const Vector3& b);           //三维坐标相加，点相加，c=a+b
Vector3 operator-(const Vector3& a, const Vector3& b);           //三维坐标相减，点相减，c=a-b
float operator*(const Vector3& a, const Vector3& b);             //三维坐标点积
Vector3 operator%(const Vector3& a, const Vector3& b);           //三维坐标叉积


Vector3 numMulVec(const float& a, const Vector3& b);           //数乘向量，float * Vector3
Vector3 vecMulVec(const Vector3& a, const Vector3& b);           //三维向量各坐标相乘，Vector3 * Vector3

