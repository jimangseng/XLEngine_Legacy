#pragma once
#undef GetObject

#include <vector>
#include <memory>
#include "IObject.h"


namespace XL
{
	namespace GamePlay
	{
		class GameScene
		{
		public:

			// todo
			template <typename T>
			void AddObject(T& object)
			{
				objects.emplace_back(std::make_shared<T>(std::move(object)));
			}

			template <typename T>
			void AddObject(T&& object)
			{
				objects.emplace_back(std::make_shared<T>(std::move(object)));
			}

		public:
			void Start();
			void Update();
			void Finish();

		public:
			IObject* GetObject(unsigned int i) { return objects.at(i).get(); }
			std::vector<std::shared_ptr<IObject>>& GetObjects() { return objects; }

		private:
			std::vector<std::shared_ptr<IObject>> objects;
		};
	}
}
