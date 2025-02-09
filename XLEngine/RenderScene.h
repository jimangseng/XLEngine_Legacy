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
			void Initialize();
			void RenderUpdate();
			void Build();
			void Draw();
			void Finalize();
		
		public:
			std::vector<std::shared_ptr<IRenderable>> renderObjects;
		};
	}
}