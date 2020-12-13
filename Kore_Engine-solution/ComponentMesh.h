#pragma once
#include "Component.h"
#include "Globals.h"

#include "Libraries/MathGeoLib/include/MathBuildConfig.h"
#include "Libraries/MathGeoLib/include/MathGeoLib.h"
#include "Libraries/MathGeoLib/include/Geometry/AABB.h"

class myMesh;

class ComponentMesh : public Component
{
public:

	ComponentMesh(GameObject* owner);
	~ComponentMesh();

	void DrawAABB();

	bool Update();
	math::AABB GetAABB();

public:

	uint id_index = 0;
	uint num_indices = 0;

	uint num_faces = 0;

	uint id_vertex = 0;
	uint num_vertices = 0;
	uint id_normal = 0;
	uint id_texcoord = 0;

	uint* indices = nullptr;
	float* vertices = nullptr;
	float* textureCoords = nullptr;
	float* normals = nullptr;

	uint* materialIndices = nullptr;
	uint materialid;
	const char* materialpath;

	math::AABB bbox;
	math::AABB Gbbox;
	math::OBB obb;
};

