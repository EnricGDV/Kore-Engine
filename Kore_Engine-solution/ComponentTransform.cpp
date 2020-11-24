#include "ComponentTransform.h"

ComponentTransform::ComponentTransform(GameObject* owner) :Component(owner, Type::TRANSFORM)
{
	this->pos.x = 0;
	this->pos.y = 0;
	this->pos.z = 0;

	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;

	this->rotQuat = Quat::FromEulerXYZ(rot.x * DEGTORAD, rot.y * DEGTORAD, rot.z * DEGTORAD);

	this->scale.x = 1;
	this->scale.y = 1;
	this->scale.z = 1;

	this->matrix = float4x4::FromTRS( pos, rotQuat, scale );

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

Quat ComponentTransform::GetRotQuat() const
{
	return rotQuat;
}

float3 ComponentTransform::GetScale() const
{
	return scale;
}

void ComponentTransform::UpdateMatrix()
{
	this->matrix = float4x4::FromTRS(pos, rotQuat, scale);
}