#include "RenderScene.h"

void XL::Graphics::RenderScene::Initialize()
{
	for (auto& object : renderObjects)
	{
		object->Initialize();
	}
}

void XL::Graphics::RenderScene::RenderUpdate()
{
	for (auto& object : renderObjects)
	{
		object->RenderUpdate();
	}
}

void XL::Graphics::RenderScene::Build()
{
	for (auto& object : renderObjects)
	{
		object->Build();
	}
}

void XL::Graphics::RenderScene::Draw()
{
	for (auto& object : renderObjects)
	{
		object->Draw();
	}
}

void XL::Graphics::RenderScene::Finalize()
{
	delete[] renderObjects.data();
}


