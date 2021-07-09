#pragma once
#include"window.h"
#include"primitives.h"
#include"camera.h"

class WorldTrans {   
public:
    Matrix matrix;      //Ĭ�ϵ�λ����

    WorldTrans() {
    }

    Vector3 wTrans(const Vector3& a);     //����ת������������->��������
};


class ViewTrans {
public:                                                    //Ĭ��
    Matrix matrix;                                         // 1.0f, 0.0f, 0.0f, 0.0f
                                                           // 0.0f, 1.0f, 0.0f, 0.0f
    ViewTrans() {                                          // 0.0f, 0.0f, 1.0f, 0.0f
        (this->matrix).mat[3][2] = 1.0f;                   // 0.0f, 0.0f, 1.0f, 1.0f
    }

    Vector3 vTrans(const Vector3& a, const Camera& camera);    //��ͼת������������->��ͼ����
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

    Vector3 pTrans(const Vector3& a, const Camera& camera);    //ͶӰת������ͼ����->ͶӰ����
};


Vector3 sTrans(const Vector3& a, const Window& win);     //��Ļת����ͶӰ����->��Ļ���� 
Vector3 transformAll(const Vector3& a, const Camera& camera, const Window& win);    //ȫ��ת��

unsigned int vecToInt(Vector3 v);        //����ת����Vector3 -> unsigned int 
Vector3 vecNormalize(Vector3 vector);    //��ά������λ��

Vector3 rotateVec(Vector3 vec, Vector3 axis, float a);      //��ת
Vector3 moveVec(Vector3 vec, Vector3 target);               //ƽ��

