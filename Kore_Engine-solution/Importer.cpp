#include "Importer.h"

#include "Libraries/Assimp/include/cimport.h"
#include "Libraries/Assimp/include/scene.h"
#include "Libraries/Assimp/include/postprocess.h"
#include "Libraries/DevIL/include/IL/il.h"
#include "Libraries/DevIL/include/IL/ilu.h"
#include "Libraries/DevIL/include/IL/ilut.h"

#pragma comment (lib, "Libraries/Assimp/libx86/assimp.lib")
#pragma comment (lib, "Libraries/DevIL/libx86/DevIL.lib")
#pragma comment (lib, "Libraries/DevIL/libx86/ILU.lib")
#pragma comment (lib, "Libraries/DevIL/libx86/ILUT.lib")

void Importer::Debug()
{
	struct aiLogStream stream;
	stream = aiGetPredefinedLogStream(aiDefaultLogStream_DEBUGGER, nullptr);
	aiAttachLogStream(&stream);

	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION || iluGetInteger(ILU_VERSION_NUM) < ILU_VERSION || ilutGetInteger(ILUT_VERSION_NUM) < ILUT_VERSION) 
	{
		LOG("DevIL version is different!");
	}
	else
	{
		ilInit();
		ilutRenderer(ILUT_OPENGL);
	}
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

			if (scene->mMeshes[i]->HasNormals())
			{
				m.normals = new float [m.num_vertices * 3];
				memcpy(m.normals, scene->mMeshes[i]->mNormals, sizeof(float) * m.num_vertices * 3);
				LOG("Normals loaded");
			}

			if (scene->mMeshes[i]->HasTextureCoords(0))
			{
				m.textureCoords = new float[m.num_vertices * 2];
				for (int j = 0; j < m.num_vertices; j++)
				{
					m.textureCoords[j * 2] = scene->mMeshes[i]->mTextureCoords[0][j].x;
					m.textureCoords[j * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][j].y;
				}
				LOG("UVs loaded");
			}

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

myTexture Importer::LoadTexture(char* file_path)
{
	myTexture tex;

	if (ilLoadImage(file_path))
	{
		LOG("Texture path loaded properly");
		tex.path = file_path;
	}
	else
	{
		LOG("Texture path didn't load properly");
		return tex;
	}

	tex.id = ilutGLBindTexImage();
	tex.data = ilGetData();
	tex.width = ilGetInteger(IL_IMAGE_WIDTH);
	tex.height = ilGetInteger(IL_IMAGE_HEIGHT);

	return tex;
}

myMesh::myMesh()
{

}
myMesh::~myMesh()
{

}

myTexture::myTexture()
{

}
myTexture::~myTexture()
{

}