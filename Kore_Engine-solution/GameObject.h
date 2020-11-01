#pragma once
#include "Globals.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"

enum Type;

class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	bool Update();

	Component* CreateComponent(Type type);

public:

	string name;
	vector<Component*> components;
	//ComponentTransform* transform = nullptr;
	ComponentMesh* mesh;
	ComponentMaterial* material;


};

