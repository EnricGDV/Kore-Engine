#include "Component.h"

Component::Component(GameObject* GameObj, Type type)
{
	this->GameObj = GameObj;
}

Component::~Component()
{

}

bool Component::Update()
{
	return true;
}

bool Component::Draw()
{
	return true;
}