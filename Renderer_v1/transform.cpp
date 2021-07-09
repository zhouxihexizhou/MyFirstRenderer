#include"transform.h"
#include<math.h>


//世界转换：对象坐标->世界坐标
Vector3 WorldTrans::wTrans(const Vector3& a)
{
    Vector3 b;
    b = vector3_transform(a, this->matrix);
    return b;
}


//视图转换：世界坐标->视图坐标
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

//投影转换：视图坐标->投影坐标
Vector3 ProjectTrans::pTrans(const Vector3& a, const Camera& camera)
{
    (this->matrix).mat[0][0] = 1 / (camera.aspect * tan(camera.fov / 2));
    (this->matrix).mat[1][1] = 1 / tan(camera.fov / 2);
    (this->matrix).mat[2][2] = camera.far_range / (camera.far_range - camera.near_range);
    (this->matrix).mat[3][2] = (camera.far_range * camera.near_range) / (camera.near_range - camera.far_range);
    Vector3 b; 
    b = vector3_transform(a, this->matrix);
    b.x /= b.w;
    b.y /= b.w;
    b.z /= b.w;
    b.w /= b.w;
    return b;
}

//屏幕转换：投影坐标->屏幕坐标 
//屏幕：左上角原点，x向右，y向下，2D坐标
Vector3 sTrans(const Vector3& a, const Window& win)
{
    Vector3 b;
    b.x = (win.windowWidth / 2) + (a.x * win.windowWidth / 2);
    b.y = (win.windowHeight / 2) - (a.y * win.windowHeight / 2);
    b.z = a.z;
    return b;
}

//全部转换
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


//类型转换：Vector3 -> unsigned int 
unsigned int vecToInt(Vector3 v)
{
    unsigned int colorR = (unsigned int)(v.x * 255);
    unsigned int colorG = (unsigned int)(v.y * 255);
    unsigned int colorB = (unsigned int)(v.z * 255);
    unsigned int result = ((colorR << 16) | (colorG << 8) | colorB);
    return result;
}


//三维向量单位化
Vector3 vecNormalize(Vector3 vector)
{
    float m = sqrt(vector.x * vector.x + vector.y * vector.y + vector.z * vector.z);
    vector.x = vector.x / m;
    vector.y = vector.y / m;
    vector.z = vector.z / m;
    return vector;
}


//旋转
Vector3 rotateVec(Vector3 vec, Vector3 axis, float a)
{
    //角度化弧度，acos(-1)=pi
    a /= (180 / acos(-1));

    axis = vecNormalize(axis);

    Matrix matrix;
    //旋转矩阵
    matrix.mat[0][0] = cos(a) + (axis.x * axis.x * (1 - (cos(a))));
    matrix.mat[0][1] = axis.x * axis.y * (1 - (cos(a))) + (axis.z * (sin(a)));
    matrix.mat[0][2] = axis.x * axis.z * (1 - (cos(a))) - (axis.y * (sin(a)));

    matrix.mat[1][0] = axis.x * axis.y * (1 - (cos(a))) - (axis.z * (sin(a)));
    matrix.mat[1][1] = cos(a) + (axis.y * axis.y * (1 - (cos(a))));
    matrix.mat[1][2] = axis.y * axis.z * (1 - (cos(a))) + (axis.x * (sin(a)));

    matrix.mat[2][0] = axis.x * axis.z * (1 - (cos(a))) + (axis.y * (sin(a)));
    matrix.mat[2][1] = axis.y * axis.z * (1 - (cos(a))) - (axis.x * (sin(a)));
    matrix.mat[2][2] = cos(a) + (axis.z * axis.z * (1 - (cos(a))));

    return vector3_transform(vec, matrix);
}


//平移
Vector3 moveVec(Vector3 vec, Vector3 target)
{
    Matrix matrix;
    //平移矩阵
    matrix.mat[3][0] = target.x;
    matrix.mat[3][1] = target.y;
    matrix.mat[3][2] = target.z;

    return vector3_transform(vec, matrix);
}

