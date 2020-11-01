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
	bool active = true;
	bool selected = false;
	vector<Component*> components;
	//ComponentTransform* transform;
	ComponentMesh* mesh;
	ComponentMaterial* material;

	vector<GameObject*> children;
	GameObject* father;

};

