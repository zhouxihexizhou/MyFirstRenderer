#pragma once

//����
class Matrix {
public:
    float mat[4][4];
};

//��
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


//����
class Vertex {
public:
    Vector3 vector;    //��������
    Vector3 normal;    //������

    unsigned int color;
    Vector3 vColor;

    Vertex() {
        this->vector = { 0.0f, 0.0f, 0.0f };
        this->color = ((255 << 16) | (255 << 8) | 255);
        this->vColor = { 1.0f, 1.0f, 1.0f };
    }
};


//������
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
    void updateTriangle();       //���¶�����Ϣ��������
};


//��ѧ��
Vector3 vector3_scale(const Vector3& a, const float k);          //��άʸ������
Vector3 vector3_transform(const Vector3& a, const Matrix& m);    //��άʸ��ͨ������任


Vector3 operator+(const Vector3& a, const Vector3& b);           //��ά������ӣ�����ӣ�c=a+b
Vector3 operator-(const Vector3& a, const Vector3& b);           //��ά����������������c=a-b
float operator*(const Vector3& a, const Vector3& b);             //��ά������
Vector3 operator%(const Vector3& a, const Vector3& b);           //��ά������


Vector3 numMulVec(const float& a, const Vector3& b);           //����������float * Vector3
Vector3 vecMulVec(const Vector3& a, const Vector3& b);           //��ά������������ˣ�Vector3 * Vector3

