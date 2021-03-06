#include"shader.h"
#include"transform.h"
#include"effect.h"


extern Window* window;
extern Camera* camera;
extern Light* light;

Vector3 yellow = { 1.0f, 1.0f, 0.0f };

Vector3 color[3] = { { 1.0f, 0.0f, 0.0f } ,     //红
                     { 0.0f, 1.0f, 0.0f } ,     //绿
                     { 0.0f, 0.0f, 1.0f } };    //蓝
static int colorPit = 0;

//顶点着色器
Vertex vertexShader(Vertex vertex)
{
	vertex.vector = transformAll(vertex.vector, *camera, *window);

	vertex.vColor = color[colorPit];
	vertex.color = vecToInt(vertex.vColor);
	colorPit++;
	if (colorPit >= 2) {
		colorPit = 0;
	}

	if (!(vertex.normal.x==0.0f && vertex.normal.y == 0.0f && vertex.normal.z == 0.0f)) {
		vertex = gouraudLight(vertex);
	}

	return vertex;
}


//gouraud光照着色
Vertex gouraudLight(Vertex vertex)
{
	//环境光
	Vector3 ambient = numMulVec(light->ambientStrength, light->lightColor);

	//单位化
	Vector3 norm = vecNormalize(vertex.normal);
	Vector3 lightDir = vecNormalize(numMulVec(-1.0f, light->direction));      //反射光方向

	//漫反射，点积
	float diff = norm * lightDir;
	if (diff < 0.0f) {
		diff = 0.0f;
	}
	//散射光
	Vector3 diffuse = numMulVec(diff, light->lightColor);

	//合成
	Vector3 result = vecMulVec((ambient + diffuse), vertex.vColor);

	if (result.x > 1.0f) {
		result.x = 1.0f;
	}
	if (result.y > 1.0f) {
		result.y = 1.0f;
	}
	if (result.z > 1.0f) {
		result.z = 1.0f;
	}

	vertex.vColor = result;
	vertex.color = vecToInt(vertex.vColor);

	return vertex;
}


//像素着色器
Vertex pixelShader(Vertex vertex)
{
	return vertex;
}

