#include "Globals.h"
#include <iostream>


class myMesh
{
public:
	myMesh();
	~myMesh();

	uint id_index = 0;
	uint num_indices = 0;

	uint id_vertex = 0;
	uint num_vertices = 0;

	uint* indices = nullptr;
	float* vertices = nullptr;
	float* textureCoords = nullptr;
	float* normals = nullptr;
	uint* materialIndices = nullptr;
};

namespace Importer
{
	void Debug();
	void CleanDebug();

	std::vector<myMesh> LoadMeshes(char* file_path);
}