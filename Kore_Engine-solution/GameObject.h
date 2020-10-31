#ifndef __GAMEOBJECT__
#define __GAMEOBJECT__

#include "Globals.h"
#include "Component.h"
#include "ComponentTransform.h"
#include "ComponentMaterial.h"
#include "ComponentMesh.h"


class ComponentTransform; 

enum Type;

class GameObject
{
public:
	GameObject(string name);
	~GameObject();

	bool Update();
	bool Draw();

	Component* CreateComponent(Type type);

public:

	string name;
	vector<Component*> components;

	ComponentMesh* mesh;
	ComponentMaterial* material;
	ComponentTransform* transform;

};

#endif