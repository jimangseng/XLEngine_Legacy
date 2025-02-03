#include "Scene.h"

Scene::Scene()
{

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
