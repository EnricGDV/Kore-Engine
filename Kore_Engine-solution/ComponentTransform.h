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


public:

	float3 pos;
	//std::vector<float*> pos;
	float3 rot;
	float3 scale;


};

