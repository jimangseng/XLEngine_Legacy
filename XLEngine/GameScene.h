#pragma once

#include <vector>
#include <memory>
#include "IObject.h"

class Cube;

namespace XL
{
	namespace GamePlay
	{
		class GameScene
		{
		public:

			// 왜 템플릿을 쓰게 되었는가?
			// 런타임 다형성을 활용하려고 하니, 컴파일 타임에 타입을 알 수 없어 오류가 났다
			// 매개변수 타입이 벡터인 경우에는?
			template <typename T>
			void AddObject(T& object)
			{
				objects.emplace_back(std::make_shared<T>(object));
			}

			template <typename T>
			void AddObject(std::vector<T>& _objects)
			{
				for (auto e = _objects.begin(); e < _objects.end(); ++e)
				{
					objects.emplace_back(std::make_shared<T>(*e)); // move를 하면 왜 멤버 변수들의 값이 훼손되는가?
					// Deep Copy가 아니기 때문?
				}
			}

		public:
			void Start();
			void Update();
			void Finish();

		public:
			std::vector<std::shared_ptr<IObject>> objects;
		};
	}
}
