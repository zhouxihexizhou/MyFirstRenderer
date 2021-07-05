#include"primitives.h"


//三维矢量缩放
Vector3 vector3_scale(const Vector3& a, const float k)
{
    Vector3 b;
    b.x = a.x * k;
    b.y = a.y * k;
    b.z = a.z * k;
    return b;
}


//三维矢量通过矩阵变换
Vector3 vector3_transform(const Vector3& a, const Matrix& m)
{
    //默认齐次坐标为1
    Vector3 b;
    b.x = m.mat[0][0] * a.x + m.mat[1][0] * a.y + m.mat[2][0] * a.z + m.mat[3][0];
    b.y = m.mat[0][1] * a.x + m.mat[1][1] * a.y + m.mat[2][1] * a.z + m.mat[3][1];
    b.z = m.mat[0][2] * a.x + m.mat[1][2] * a.y + m.mat[2][2] * a.z + m.mat[3][2];
    return b;
}


//三维坐标相加，点相加，c=a+b
Vector3 operator+(const Vector3 &a, const Vector3 &b) 
{
    Vector3 sum = a;
    sum.x += b.x;
    sum.y += b.y;
    sum.z += b.z;
    return sum;
}


//三维坐标相减，点相减，c=a-b
Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
    Vector3 sum = a;
    sum.x -= b.x;
    sum.y -= b.y;
    sum.z -= b.z;
    return sum;
}


//三维坐标点积
float operator*(const Vector3& a, const Vector3& b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}


//三维坐标叉积
Vector3 operator%(const Vector3& a, const Vector3& b)
{
    Vector3 c = a;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}
