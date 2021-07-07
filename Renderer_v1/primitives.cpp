#include"primitives.h"


//��άʸ������
Vector3 vector3_scale(const Vector3& a, const float k)
{
    Vector3 b;
    b.x = a.x * k;
    b.y = a.y * k;
    b.z = a.z * k;
    return b;
}


//��άʸ��ͨ������任
Vector3 vector3_transform(const Vector3& a, const Matrix& m)
{
    //Ĭ���������Ϊ1
    Vector3 b;
    b.x = m.mat[0][0] * a.x + m.mat[1][0] * a.y + m.mat[2][0] * a.z + m.mat[3][0] * a.w;
    b.y = m.mat[0][1] * a.x + m.mat[1][1] * a.y + m.mat[2][1] * a.z + m.mat[3][1] * a.w;
    b.z = m.mat[0][2] * a.x + m.mat[1][2] * a.y + m.mat[2][2] * a.z + m.mat[3][2] * a.w;
    b.w = m.mat[0][3] * a.x + m.mat[1][3] * a.y + m.mat[2][3] * a.z + m.mat[3][3] * a.w;
    return b;
}


//��ά������ӣ�����ӣ�c=a+b
Vector3 operator+(const Vector3 &a, const Vector3 &b) 
{
    Vector3 sum = a;
    sum.x += b.x;
    sum.y += b.y;
    sum.z += b.z;
    return sum;
}


//��ά����������������c=a-b
Vector3 operator-(const Vector3 &a, const Vector3 &b)
{
    Vector3 sum = a;
    sum.x -= b.x;
    sum.y -= b.y;
    sum.z -= b.z;
    return sum;
}


//��ά������
float operator*(const Vector3& a, const Vector3& b)
{
    return (a.x * b.x + a.y * b.y + a.z * b.z);
}


//��ά������
Vector3 operator%(const Vector3& a, const Vector3& b)
{
    Vector3 c = a;
    c.x = a.y * b.z - a.z * b.y;
    c.y = a.z * b.x - a.x * b.z;
    c.z = a.x * b.y - a.y * b.x;
    return c;
}


//���������ζ�����Ϣ��������
void Triangle::updateTriangle()
{
    Vector3 v1 = (this->point2).vector - (this->point1).vector;
    Vector3 v2 = (this->point3).vector - (this->point1).vector;
    Vector3 n = v1 % v2;
    (this->point1).normal = n;
    (this->point2).normal = n;
    (this->point3).normal = n;
}


//����������float * Vector3
Vector3 numMulVec(const float& a, const Vector3& b)
{
    Vector3 c;
    c.x = a * b.x;
    c.y = a * b.y;
    c.z = a * b.z;
    return c;
}


//��ά������������ˣ�Vector3 * Vector3
Vector3 vecMulVec(const Vector3& a, const Vector3& b)
{
    Vector3 c;
    c.x = a.x * b.x;
    c.y = a.y * b.y;
    c.z = a.z * b.z;
    return c;
}

