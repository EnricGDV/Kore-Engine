#include "Importer.h"

#include "Libraries/Assimp/include/cimport.h"
#include "Libraries/Assimp/include/scene.h"
#include "Libraries/Assimp/include/postprocess.h"
#include "Libraries/Glew/include/GL/glew.h"
#include "Libraries/SDL/include/SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */
#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")

void Importer::Debug()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

}

void Importer::CleanDebug()
{
	aiDetachAllLogStreams();
}

std::vector<myMesh> Importer::LoadMeshes(char* file_path)
{
	vector<myMesh> meshvector;
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		// Use scene->mNumMeshes to iterate on scene->mMeshes array
		for (int i = 0; i < scene->mNumMeshes; ++i)
		{
			myMesh m;
			m.num_vertices = scene->mMeshes[i]->mNumVertices;
			m.vertices = new float[m.num_vertices * 3];
			memcpy(m.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m.num_vertices * 3);
			LOG("New mesh with %d vertices", m.num_vertices);

			// copy faces
			if (scene->mMeshes[i]->HasFaces())
			{
				m.num_indices = scene->mMeshes[i]->mNumFaces * 3;
				m.indices = new uint[m.num_indices]; // assume each face is a triangle
				for (uint j = 0; j < scene->mMeshes[i]->mNumFaces; ++j)
				{
					if (scene->mMeshes[i]->mFaces[j].mNumIndices != 3)
					{
						LOG("WARNING, geometry face with != 3 indices!");
					}
					else
					{
						memcpy(&m.indices[j * 3], scene->mMeshes[i]->mFaces[j].mIndices, 3 * sizeof(uint));
					}
				}
			}
			meshvector.push_back(m);
		}
		aiReleaseImport(scene);
		return meshvector;
	}
	else
	{
		LOG("Error loading scene % s", file_path);
		return meshvector;
	}
		
}



myMesh::myMesh()
{

}
myMesh::~myMesh()
{

}