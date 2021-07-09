#include"camera.h"
#include<iostream>


//Ïú»ÙÏà»ú
void free_camera(Camera* camera)
{
    memset(camera, 0, sizeof(Camera));
    free(camera);
}

