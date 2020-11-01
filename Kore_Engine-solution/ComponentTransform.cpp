#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* owner) :Component(owner, Type::TRANSFORM)
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->pos.z = 0;

	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;

	this->scale.x = 1;
	this->scale.y = 1;
	this->scale.z = 1;

}

ComponentTransform::~ComponentTransform()
{
}

float3 ComponentTransform::GetPos() const
{
	return pos;
}

float3 ComponentTransform::GetRot() const
{
	return rot;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}