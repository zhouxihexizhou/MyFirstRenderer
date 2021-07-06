#include"transform.h"


//����ת������������->��������
Vector3 WorldTrans::wTrans(const Vector3& a)
{
    Vector3 b;
    b = vector3_transform(a, this->matrix);
    return b;
}


//��ͼת������������->��ͼ����
Vector3 ViewTrans::vTrans(const Vector3& a, const Camera& camera)
{
    Vector3 y = camera.target % camera.xDirect; 
    (this->matrix).mat[0][0] = camera.xDirect.x;    (this->matrix).mat[0][1] = camera.xDirect.y;   (this->matrix).mat[0][2] = camera.xDirect.z;
    (this->matrix).mat[1][0] = y.x;                 (this->matrix).mat[1][1] = y.y;                (this->matrix).mat[1][2] = y.z;
    (this->matrix).mat[2][0] = camera.target.x;     (this->matrix).mat[2][1] = camera.target.y;    (this->matrix).mat[2][2] = camera.target.z;
    (this->matrix).mat[3][0] = -camera.position.x;  (this->matrix).mat[3][1] = -camera.position.y; (this->matrix).mat[3][2] = -camera.position.z;
    Vector3 b;
    b = vector3_transform(a, this->matrix);
    return b;
}

//ͶӰת������ͼ����->ͶӰ����
Vector3 ProjectTrans::pTrans(const Vector3& a, const Camera& camera)
{
    (this->matrix).mat[0][0] = 1 / (camera.aspect * tan(camera.fov / 2));
    (this->matrix).mat[1][1] = 1 / tan(camera.fov / 2);
    (this->matrix).mat[2][2] = camera.far_range / (camera.far_range - camera.near_range);
    (this->matrix).mat[3][2] = (camera.far_range * camera.near_range) / (camera.near_range - camera.far_range);
    Vector3 b;
    b = vector3_transform(a, this->matrix);
    return b;
}

//��Ļת����ͶӰ����->��Ļ���� 
//��Ļ�����Ͻ�ԭ�㣬x���ң�y���£�2D����
Vector3 sTrans(const Vector3& a, const Window& win)
{
    Vector3 b;
    b.x = (win.windowWidth / 2) + (a.x * win.windowWidth / 2);
    b.y = (win.windowHeight / 2) - (a.y * win.windowHeight / 2);
    return b;
}

//ȫ��ת��
Vector3 transformAll(const Vector3& a, const Camera& camera, const Window& win)
{
    WorldTrans worldTrans;
    Vector3 b = worldTrans.wTrans(a);
    ViewTrans viewTrans;
    Vector3 c = viewTrans.vTrans(b, camera);
    ProjectTrans projectTrans;
    Vector3 e = projectTrans.pTrans(c, camera);
    Vector3 f = sTrans(e, win);
    return f;
}


//����ת����Vector3 -> unsigned int 
unsigned int vecToInt(Vector3 v)
{
    unsigned int colorR = (unsigned int)(v.x * 255);
    unsigned int colorG = (unsigned int)(v.y * 255);
    unsigned int colorB = (unsigned int)(v.z * 255);
    unsigned int result = ((colorR << 16) | (colorG << 8) | colorB);
    return result;
}


//��ά������λ��
Vector3 vecNormalize(Vector3 vector)
{
    float m = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    vector.x = vector.x / m;
    vector.y = vector.y / m;
    vector.z = vector.z / m;
    return vector;
}

