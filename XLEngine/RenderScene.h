#pragma once

#include <vector>
#include <memory>
#include "IRenderable.h"
#include "IObject.h"
#include "GameScene.h"

namespace XL
{
	namespace Graphics
	{
		class RenderScene
		{
		public:
			void Start();
			void Build();
			void Draw();
			void Finalize();

		public:
			void Sync(XL::GamePlay::GameScene* gameScene);
		
		private:
			void SetGameObjects(std::vector<std::shared_ptr<IObject>> _gameObjects);

		public:
			std::vector<std::shared_ptr<IRenderable>> objects;
			std::vector<std::shared_ptr<IObject>> gameObjects;
		};
	}
}