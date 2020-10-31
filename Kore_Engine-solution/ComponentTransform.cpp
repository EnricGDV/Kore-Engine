#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* GameObj) :Component(GameObj, Type::TRANSFORM)
{
	this->pos[0] = 0;
	this->pos[1] = 0;
	this->pos[2] = 0;

	this->rot[0] = 0;
	this->rot[1] = 0;
	this->rot[2] = 0;

}

ComponentTransform::~ComponentTransform()
{
}

vector<float*> ComponentTransform::GetPos() const
{
	return pos;
}