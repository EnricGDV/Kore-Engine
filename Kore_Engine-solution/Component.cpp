#include "Component.h"

Component::Component(GameObject* owner, Type type)
{
	this->owner = owner;
	this->type = type;
}

Component::~Component()
{

}

bool Component::Enable()
{
	return true;
}

bool Component::Update()
{
	return true;
}

bool Component::Disable()
{
	type = NONE;
	return true;
}
