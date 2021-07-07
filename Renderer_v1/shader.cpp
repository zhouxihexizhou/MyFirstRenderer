#include"shader.h"
#include"transform.h"
#include"effect.h"



extern Window* window;
extern Camera* camera;
extern Light* light;

Vector3 yellow = { 1.0f, 1.0f, 0.0f };

//������ɫ��
Vertex vertexShader(Vertex vertex)
{
	vertex.vector = transformAll(vertex.vector, *camera, *window);

	vertex.vColor = yellow;
	vertex.color = vecToInt(vertex.vColor);

	Vertex b = gouraudLight(vertex);
	return b;
}


//gouraud������ɫ
Vertex gouraudLight(Vertex vertex)
{
	//������
	Vector3 ambient = numMulVec(light->ambientStrength, light->lightColor);

	//��λ��
	Vector3 norm = vecNormalize(vertex.normal);
	Vector3 lightDir = vecNormalize(numMulVec(-1.0f, light->direction));      //����ⷽ��

	//�����䣬���
	float diff = norm * lightDir;
	if (diff < 0.0f) {
		diff = 0.0f;
	}
	//ɢ���
	Vector3 diffuse = numMulVec(diff, light->lightColor);

	//�ϳ�
	Vector3 result = vecMulVec((ambient + diffuse), vertex.vColor);

	vertex.vColor = result;
	vertex.color = vecToInt(vertex.vColor);

	return vertex;
}


//������ɫ��
Vertex pixelShader(Vertex vertex)
{
	return vertex;
}

