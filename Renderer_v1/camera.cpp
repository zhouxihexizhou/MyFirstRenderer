#include"camera.h"
#include<iostream>


//�������
void free_camera(Camera* camera)
{
    memset(camera, 0, sizeof(Camera));
    free(camera);
}

