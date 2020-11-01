#pragma once
#include "Component.h"
#include "Globals.h"



class ComponentMaterial : public Component
{
public:
	ComponentMaterial(GameObject* GameObj);
	~ComponentMaterial();

public:

	uint id;
	const void* data;
	uint width;
	uint height;

	const char* path;

};

