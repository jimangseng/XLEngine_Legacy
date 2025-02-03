#pragma once
#include <memory>
#include "IObject.h"
#include "Cube.h"

class Scene
{
public:
	Scene();

public:
	void Initialize();
	void Build();
	void Draw();
	void Finalize();
public:
	std::vector<shared_ptr<IObject>> objects;

};