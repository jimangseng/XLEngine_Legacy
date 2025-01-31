#pragma once
#include <memory>
#include "Cube.h"
#include "IObject.h"

class Scene
{
public:
	Scene()
	{
		//std::unique_ptr<Cube> cube = std::make_unique<Cube>();
		//objects.emplace_back(cube);
	}

private:
	//std::vector<IObject> objects;

public:
	std::unique_ptr<Cube> cube = std::make_unique<Cube>();

};

