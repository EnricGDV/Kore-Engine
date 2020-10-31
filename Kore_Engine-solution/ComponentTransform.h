#pragma once
#include "Component.h"
#include "Globals.h"
#include "GameObject.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* GameObj);
	~ComponentTransform();

	std::vector<float*> GetPos() const;

public:

	std::vector<float*> pos;
	std::vector<float*> rot;
	std::vector<float*> scale;


};

