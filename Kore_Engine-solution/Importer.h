#include "Globals.h"
#include <iostream>

class myTexture
{
public:
	myTexture();
	~myTexture();

	uint id;
	const void* data;
	uint width;
	uint height;

	const char* path;
};

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
	uint materialid;
	const char* materialpath;
	//myTexture* material;
};



namespace Importer
{
	void Debug();
	void CleanDebug();

	std::vector<myMesh> LoadMeshes(const char* file_path);
	myTexture LoadTexture(const char* file_path);
}