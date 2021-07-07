#pragma once
#include"primitives.h"


Vertex vertexShader(Vertex vertex);     //顶点着色器
Vertex gouraudLight(Vertex vertex);     //gouraud光照着色

Vertex pixelShader(Vertex vertex);      //像素着色器

