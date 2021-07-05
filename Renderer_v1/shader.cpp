#include"shader.h"
#include"transform.h"

extern Window* window;
extern Camera* camera;


Vertex vertexShader(unsigned int color, Vertex vertex)
{
	Vertex v;
	v.color = color;
	v.vector = transformAll(vertex.vector, *camera, *window);
	return v;
}
