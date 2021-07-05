#include"camera.h"
#include<iostream>


//销毁相机
void free_camera(Camera* camera)
{
    memset(camera, 0, sizeof(Camera));
    free(camera);
}


//打印相机信息
void camera_msg(Camera* camera)
{
    cout << "  name:      " << camera->name << endl;
    cout << "  is_open:   " << (camera->is_open ? "yes" : "no") << endl;
    printf("  position:   (%f, %f, %f)\n", camera->position.x, camera->position.y, camera->position.z);
    printf("  target      (%f, %f, %f)\n", camera->target.x, camera->target.y, camera->target.z);
    printf("  xDirect     (%f, %f, %f)\n", camera->xDirect.x, camera->xDirect.y, camera->xDirect.z);
    cout << "  fov:       " << camera->fov << endl;
    cout << "  aspect:    " << camera->aspect << endl;
    cout << "  near_range:   " << camera->near_range << endl;
    cout << "  far_range:    " << camera->far_range << endl;
}

