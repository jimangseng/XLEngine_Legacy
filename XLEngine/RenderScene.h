#pragma once

#include <vector>
#include <memory>
#include "IRenderable.h"
#include "GameScene.h"

namespace XL
{
	namespace Graphics
	{
		class RenderScene
		{
		public:
			void Initialize(GamePlay::GameScene* _gameScene);
			void Update(GamePlay::GameScene* _gameScene);
			void Draw();
			void Finalize();
		
		private:
			std::vector<std::shared_ptr<Components::IRenderable>> Load(GamePlay::GameScene* _gameScene);

		public:
			std::vector<std::shared_ptr<Components::IRenderable>>& GetObjects() { return renderObjects; }
		
		private:
			std::vector<std::shared_ptr<Components::IRenderable>> renderObjects;
		};
	}
}