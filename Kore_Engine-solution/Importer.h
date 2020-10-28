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
	uint id_normal = 0;
	uint id_texcoord = 0;

	uint* indices = nullptr;
	float* vertices = nullptr;
	float* textureCoords = nullptr;
	float* normals = nullptr;
	uint* materialIndices = nullptr;
};

class myTexture
{
public:
	myTexture();
	~myTexture();

	uint id;
	const void* data;
	uint width;
	uint height;

	char* path;
};

namespace Importer
{
	void Debug();
	void CleanDebug();

	std::vector<myMesh> LoadMeshes(char* file_path);
	myTexture LoadTexture(char* file_path);
}