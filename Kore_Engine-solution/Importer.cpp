#include "Importer.h"
#include "Application.h"
#include "Globals.h"
#include "GameObject.h"

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
		App->ConsoleLog("DevIL version is different!");
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

std::vector<myMesh> Importer::LoadMeshes(const char* file_path)
{
	vector<myMesh> meshvector;
	const aiScene* scene = aiImportFile(file_path, aiProcessPreset_TargetRealtime_MaxQuality);
	if (scene != nullptr && scene->HasMeshes())
	{
		GameObject* rootgo = App->scene_intro->CreateGameObject();
		rootgo->name = scene->mRootNode->mName.C_Str();
		rootgo->mesh->isActive = true;

		App->scene_intro->gameObjects.clear();
		App->scene_intro->meshes.clear();

		if (scene->mRootNode->mNumChildren > 0)
		{
			// Use scene->mNumMeshes to iterate on scene->mMeshes array
			for (int i = 0; i < scene->mNumMeshes; ++i)
			{
				
				if (scene->mRootNode->mChildren[i]->mNumMeshes > 0)
				{

					for (int j = 0; j < scene->mRootNode->mChildren[i]->mNumMeshes; ++j)
					{
						myMesh m;

						int index = scene->mRootNode->mChildren[i]->mMeshes[j];

						GameObject* childgo = App->scene_intro->CreateGameObject();
						

						childgo->name = scene->mMeshes[index]->mName.C_Str();
						childgo->mesh->isActive = true;

						//Importing Transformation
						aiVector3D aiPos;
						aiVector3D aiScale;
						aiQuaternion aiRot;

						scene->mRootNode->mChildren[i]->mTransformation.Decompose(aiScale, aiRot, aiPos);

						childgo->transform->pos.x = aiPos.x;
						childgo->transform->pos.y = aiPos.y;
						childgo->transform->pos.z = aiPos.z;

						childgo->transform->scale.x = aiScale.x;
						childgo->transform->scale.y = aiScale.y;
						childgo->transform->scale.z = aiScale.z;

						Quat rotquat(aiRot.z, aiRot.x, aiRot.y, aiRot.z);
						childgo->transform->rotQuat = rotquat;
						float3 rot(aiRot.GetEuler().x * RADTODEG, aiRot.GetEuler().y * RADTODEG, aiRot.GetEuler().z * RADTODEG);
						childgo->transform->rot = rot;
						childgo->transform->UpdateMatrix();

						//Importing Vertices
						m.num_vertices = scene->mMeshes[index]->mNumVertices;
						childgo->mesh->num_vertices = m.num_vertices;

						m.vertices = new float[m.num_vertices * 3];
						childgo->mesh->vertices = m.vertices;

						memcpy(m.vertices, scene->mMeshes[index]->mVertices, sizeof(float) * m.num_vertices * 3);
						LOG("New mesh with %d vertices", m.num_vertices);
						App->ConsoleLog("New mesh with %d vertices", m.num_vertices);

						//Creating AABB
						m.CreateAABB();
						childgo->mesh->bbox = m.aabb;

						//Importing Normals
						if (scene->mMeshes[index]->HasNormals())
						{
							m.normals = new float[m.num_vertices * 3];
							memcpy(m.normals, scene->mMeshes[index]->mNormals, sizeof(float) * m.num_vertices * 3);
							LOG("Normals loaded");
							App->ConsoleLog("Normals loaded");
						}

						childgo->mesh->normals = m.normals;

						//Importing Texture Coordenates
						if (scene->mMeshes[index]->HasTextureCoords(0))
						{
							m.textureCoords = new float[m.num_vertices * 2];
							for (int k = 0; k < m.num_vertices; k++)
							{
								m.textureCoords[k * 2] = scene->mMeshes[index]->mTextureCoords[0][k].x;
								m.textureCoords[k * 2 + 1] = scene->mMeshes[index]->mTextureCoords[0][k].y;
							}
							LOG("UVs loaded");
							App->ConsoleLog("UVs loaded");
						}

						childgo->mesh->textureCoords = m.textureCoords;

						//Importing Material 
						if (scene->HasMaterials() && scene->mMeshes[index]->mMaterialIndex != NULL)
						{
							aiString materialpath;
							scene->mMaterials[scene->mMeshes[index]->mMaterialIndex]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, m.materialid, &materialpath);

							m.materialpath = materialpath.C_Str();
							App->scene_intro->textures.push_back(LoadTexture(m.materialpath));
							App->renderer3D->GenerateTextures();
							childgo->material->isActive = true;
						}

						childgo->mesh->materialpath = m.materialpath;

						// copy faces
						if (scene->mMeshes[index]->HasFaces())
						{
							m.num_indices = scene->mMeshes[i]->mNumFaces * 3;
							m.indices = new uint[m.num_indices]; // assume each face is a triangle
							childgo->mesh->num_faces = scene->mMeshes[i]->mNumFaces;
							childgo->mesh->num_indices = m.num_indices;
							childgo->mesh->indices = m.indices;
							for (uint k = 0; k < scene->mMeshes[index]->mNumFaces; ++k)
							{
								if (scene->mMeshes[index]->mFaces[k].mNumIndices != 3)
								{
									LOG("WARNING, geometry face with != 3 indices!");
									App->ConsoleLog("WARNING, geometry face with != 3 indices!");
								}
								else
								{
									memcpy(&m.indices[k * 3], scene->mMeshes[index]->mFaces[k].mIndices, 3 * sizeof(uint));
								}
							}
						}

						childgo->father = rootgo;
						rootgo->children.push_back(childgo);
						meshvector.push_back(m);
					}

				}
				else
				{
					App->ConsoleLog("No Children Found");
					myMesh m;

					GameObject* go = App->scene_intro->CreateGameObject();

					go->name = scene->mRootNode->mChildren[i]->mName.C_Str();
					go->mesh->isActive = true;

					//Importing Transformation
					aiVector3D aiPos;
					aiVector3D aiScale;
					aiQuaternion aiRot;

					scene->mRootNode->mChildren[i]->mTransformation.Decompose(aiScale, aiRot, aiPos);

					go->transform->pos.x = aiPos.x;
					go->transform->pos.y = aiPos.y;
					go->transform->pos.z = aiPos.z;

					go->transform->scale.x = aiScale.x;
					go->transform->scale.y = aiScale.y;
					go->transform->scale.z = aiScale.z;

					Quat rotquat(aiRot.z, aiRot.x, aiRot.y, aiRot.z);
					go->transform->rotQuat = rotquat;
					float3 rot(aiRot.GetEuler().x * RADTODEG, aiRot.GetEuler().y * RADTODEG, aiRot.GetEuler().z * RADTODEG);
					go->transform->rot = rot;
					go->transform->UpdateMatrix();

					//Importing Vertices
					m.num_vertices = scene->mMeshes[i]->mNumVertices;
					go->mesh->num_vertices = m.num_vertices;

					m.vertices = new float[m.num_vertices * 3];
					go->mesh->vertices = m.vertices;

					memcpy(m.vertices, scene->mMeshes[i]->mVertices, sizeof(float) * m.num_vertices * 3);
					LOG("New mesh with %d vertices", m.num_vertices);
					App->ConsoleLog("New mesh with %d vertices", m.num_vertices);

					//Importing Normals
					if (scene->mMeshes[i]->HasNormals())
					{
						m.normals = new float[m.num_vertices * 3];
						memcpy(m.normals, scene->mMeshes[i]->mNormals, sizeof(float) * m.num_vertices * 3);
						LOG("Normals loaded");
						App->ConsoleLog("Normals loaded");
					}

					go->mesh->normals = m.normals;

					//Importing Texture Coordinates
					if (scene->mMeshes[i]->HasTextureCoords(0))
					{
						m.textureCoords = new float[m.num_vertices * 2];
						for (int k = 0; k < m.num_vertices; k++)
						{
							m.textureCoords[k * 2] = scene->mMeshes[i]->mTextureCoords[0][k].x;
							m.textureCoords[k * 2 + 1] = scene->mMeshes[i]->mTextureCoords[0][k].y;
						}
						LOG("UVs loaded");
						App->ConsoleLog("UVs loaded");
					}

					go->mesh->textureCoords = m.textureCoords;

					//Importing Material
					if (scene->HasMaterials() && scene->mMeshes[i]->mMaterialIndex != NULL)
					{
						aiString materialpath;
						scene->mMaterials[scene->mMeshes[i]->mMaterialIndex]->GetTexture(aiTextureType::aiTextureType_DIFFUSE, m.materialid, &materialpath);

						m.materialpath = materialpath.C_Str();
						App->scene_intro->textures.push_back(LoadTexture(m.materialpath));
						App->renderer3D->GenerateTextures();
						go->material->isActive = true;

					}

					go->mesh->materialpath = m.materialpath;

					// copy faces
					if (scene->mMeshes[i]->HasFaces())
					{
						m.num_indices = scene->mMeshes[i]->mNumFaces * 3;
						m.indices = new uint[m.num_indices]; // assume each face is a triangle
						go->mesh->num_faces = scene->mMeshes[i]->mNumFaces;
						go->mesh->num_indices = m.num_indices;
						go->mesh->indices = m.indices;
						for (uint k = 0; k < scene->mMeshes[i]->mNumFaces; ++k)
						{
							if (scene->mMeshes[i]->mFaces[k].mNumIndices != 3)
							{
								LOG("WARNING, geometry face with != 3 indices!");
								App->ConsoleLog("WARNING, geometry face with != 3 indices!");
							}
							else
							{
								memcpy(&m.indices[k * 3], scene->mMeshes[i]->mFaces[k].mIndices, 3 * sizeof(uint));
							}
						}
					}
					meshvector.push_back(m);
					go->father = rootgo;
					rootgo->children.push_back(go);
				}
			}
			App->scene_intro->rootGameObject = rootgo;
		}
		
		

		aiReleaseImport(scene);
		return meshvector;
	}
	else
	{
		LOG("Error loading scene % s", file_path);
		App->ConsoleLog("Error loading scene % s", file_path);
		return meshvector;
	}
	
}

myTexture Importer::LoadTexture(const char* file_path)
{
	myTexture tex;

	if (ilLoadImage(file_path))
	{
		LOG("Texture path loaded properly");
		App->ConsoleLog("Texture path loaded properly");
		tex.path = file_path;
		App->scene_intro->textures.clear();
	}
	else
	{
		LOG("Texture path didn't load properly");
		App->ConsoleLog("Texture path didn't load properly");
		return tex;
	}

	tex.id = ilutGLBindTexImage();
	tex.data = ilGetData();
	tex.width = ilGetInteger(IL_IMAGE_WIDTH);
	tex.height = ilGetInteger(IL_IMAGE_HEIGHT);

	// PASSING MATERIAL DATA TO GAMEOBJECT 
	//go->material->data = tex.data;
	//go->material->height = tex.height;
	//go->material->width = tex.width;
	//go->material->id = tex.id;
	//go->material->path = tex.path;
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