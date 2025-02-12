#include "GameObject.h"

void XL::GameObjects::GameObject::SetPosition(float x, float y, float z)
{
	translation = XMMatrixTranslation(x, y, z);
}

void XL::GameObjects::GameObject::Translate(float x, float y, float z)
{
	translation = XMMatrixMultiply(translation, XMMatrixTranslation(x, y, z));
}

void XL::GameObjects::GameObject::Rotate(float x, float y, float z)
{
	rotation = XMMatrixRotationRollPitchYaw(x, y, z);
}

void XL::GameObjects::GameObject::Scale(float x, float y, float z)
{
	scale = XMMatrixScaling(x, y, z);
}

// todo: ���� ���̺귯���� ���� �����غ���?
//void XL::GameObjects::GameObject::Yaw(float _angle)
//{
//	// ������ �������� ��ȯ
//	float radian = _angle * 3.14159265358979323846f / 180.0f;
//
//	float cosTheta = cos(radian);
//	float sinTheta = sin(radian);
//
//	// ��� ���ؽ��� ȸ�� ����
//	for (auto& vertex : vertices)
//	{
//		float x = vertex.localPosition.x;
//		float z = vertex.localPosition.x;
//
//		float newX = x * cosTheta + z * sinTheta;
//		float newZ = -x * sinTheta + z * cosTheta;
//
//		vertex.localPosition.x = newX;
//		vertex.localPosition.z = newZ;
//	}
//}