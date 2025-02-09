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

			// �� ���ø��� ���� �Ǿ��°�?
			// ��Ÿ�� �������� Ȱ���Ϸ��� �ϴ�, ������ Ÿ�ӿ� Ÿ���� �� �� ���� ������ ����
			// �Ű����� Ÿ���� ������ ��쿡��?
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
					objects.emplace_back(std::make_shared<T>(*e)); // move�� �ϸ� �� ��� �������� ���� �ѼյǴ°�?
					// Deep Copy�� �ƴϱ� ����?
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
