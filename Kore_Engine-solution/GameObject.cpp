#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(string name)
{
	this->name = name;
	transform = (ComponentTransform*)CreateComponent(Type::TRANSFORM);
	mesh = (ComponentMesh*)CreateComponent(Type::MESH);
	material = (ComponentMaterial*)CreateComponent(Type::MATERIAL);

}
GameObject::~GameObject()
{

}

bool GameObject::Update()
{
	return true;
}


Component* GameObject::CreateComponent(Type type)
{
	Component* _component = nullptr;

	switch (type)
	{
	case Type::TRANSFORM:
		_component = new ComponentTransform(this);
		break;
	case Type::MATERIAL:
		_component = new ComponentMaterial(this);
		break;
	case Type::MESH: 
		_component = new ComponentMesh(this);
		break;
	}

	components.push_back(_component);

	return _component;

}