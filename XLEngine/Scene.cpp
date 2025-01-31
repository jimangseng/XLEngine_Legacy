#include "Scene.h"

Scene::Scene()
{
	shared_ptr<Cube> cube;

	cube = make_shared<Cube>();
	cube->size = 0.8f;
	cube->color = XMFLOAT4{ 0.0f, 0.5f, 1.0f, 1.0f };	// ÇÏ´Ã
	objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.5f;
	cube->color = XMFLOAT4{ 1.0f, 0.0f, 0.0f, 1.0f };	// »¡°­
	objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.3f;
	cube->color = XMFLOAT4{ 0.0f, 0.0f, 1.0f, 1.0f };	// ÆÄ¶û
	objects.emplace_back(cube);

	cube = make_shared<Cube>();
	cube->size = 0.1f;
	cube->color = XMFLOAT4{ 1.0f, 1.0f, 0.0f, 1.0f };	// ³ë¶û
	cube->Translate({ 1.0f, 0.0f, 0.0f });
	objects.emplace_back(cube);
}

void Scene::Initialize()
{
	for (auto& object : objects)
	{
		object->Initialize();
	}
}

void Scene::Build()
{
	for (auto& object : objects)
	{
		object->Build();
	}
}

void Scene::Draw()
{
	for (auto& object : objects)
	{
		object->Draw();
	}
}

void Scene::Finalize()
{
	delete[] objects.data();
}
