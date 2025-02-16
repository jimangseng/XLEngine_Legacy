#pragma once

#include <vector>
#include <memory>
#include "GameObject.h"
#include "Camera.h"

#undef GetObject
namespace XL
{
	using namespace GameObjects;

	namespace GamePlay
	{
		class GameScene
		{
		public:

			// todo
			template <typename T>
			void AddObject(T& object)
			{
				objects.emplace_back(std::make_shared<T>(std::move(object)));	// ��ĳ��Ʈ �߻�		// RenderScene�� ConvertScene()���� �ٿ�ĳ������ �߻�
			}

		public:
			void Start();
			void Update();
			void Finish();

		public:
			GameObject* GetObject(unsigned int i) { return objects.at(i).get(); }
			std::vector<std::shared_ptr<GameObject>>& GetObjects() { return objects; }

		public:
			Camera camera;
		private:
			std::vector<std::shared_ptr<GameObject>> objects;
		};
	}
}
