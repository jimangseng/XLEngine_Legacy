#pragma once

#include "XLMath.h"

using namespace DirectX;

// ���� �����Լ��� ����ϴ��� ����غ� ��
// ��� ������Ʈ�� ���������� �� �����̶�� ������ ���� �ʰ� �����ع����� ���� ����?
namespace XL
{
	namespace GameObjects
	{
		class GameObject
		{
		public:
			// Transform ����
			// �ڽ� Ŭ�������� ��ӹ޾� ���
			virtual void SetPosition(float x, float y, float z);
			virtual void Translate(float x, float y, float z);
			virtual void Rotate(float x, float y, float z);
			virtual void Scale(float x, float y, float z);

			// todo: ���� ���̺귯�� �����
			//virtual void Yaw(float _angle);
			//virtual void Pitch(float _angle);
			//virtual void Roll(float _angle);

		public:
			// GameScene ����
			virtual void InitializeGameObject() = 0;
			virtual void UpdateGameObject() = 0;
			virtual void FinalizeGameObject() = 0;

		protected:
			// Transform ���� ��� ������
			XMMATRIX translation = XMMatrixIdentity();
			XMMATRIX rotation = XMMatrixIdentity();
			XMMATRIX scale = XMMatrixIdentity();

			XMMATRIX worldMatrix = XMMatrixIdentity();
			XMMATRIX viewMatrix = XMMatrixIdentity();
			XMMATRIX projectionMatrix = XMMatrixIdentity();

			XMMATRIX WVPMatrix = XMMatrixIdentity();

			// todo: ���� ���̺귯�� �����
			// XL::Math::Matrix translation;
			// XL::Math::Matrix rotation;
			// XL::Math::Matrix scale;
		};
	}
}