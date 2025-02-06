#pragma once

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
			void AddObject(std::shared_ptr<IObject> object);

		public:
			void Start();
			void Update();
			void Finish();

		public:
			std::vector<std::shared_ptr<IObject>> objects;
		};
	}
}
