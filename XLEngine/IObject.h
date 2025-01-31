#pragma once
class IObject
{
public:
	virtual void Initialize() = 0;
	virtual void Build() = 0;
	virtual void Draw() = 0;
};

