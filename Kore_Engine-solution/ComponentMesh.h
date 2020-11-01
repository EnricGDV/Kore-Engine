#pragma once
#include "Component.h"
#include "Globals.h"

#include "Libraries/MathGeoLib/include/MathBuildConfig.h"
#include "Libraries/MathGeoLib/include/MathGeoLib.h"

class myMesh;

class ComponentMesh : public Component
{
public:

	ComponentMesh(GameObject* GameObj);
	~ComponentMesh();

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
};

