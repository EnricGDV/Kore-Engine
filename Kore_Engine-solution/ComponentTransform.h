#pragma once
#include "Component.h"
#include "Globals.h"
#include "GameObject.h"

#include "Libraries/MathGeoLib/include/MathBuildConfig.h"
#include "Libraries/MathGeoLib/include/MathGeoLib.h"

class ComponentTransform : public Component
{
public:
	ComponentTransform(GameObject* owner);
	~ComponentTransform();

	float3 GetPos() const;
	float3 GetRot() const;
	float3 GetScale() const;

	Quat GetRotQuat() const;

	void UpdateMatrix();


public:

	float3 pos;
	float3 rot;
	float3 scale;

	Quat rotQuat;

	float4x4 matrix;


};

