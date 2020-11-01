#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"



#define MAX_LIGHTS 8

class myMesh;
class myTexture;

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void OnResize(int width, int height);

	void GenerateMeshes();
	void GenerateTextures();

	void Draw(myMesh* mesh);

public:

	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;

	uint cube_id;
	uint uvs_id;
	float* uvs;
	uint index_id;
	uint color_id;
	uint checkerImage_id;
	
	

	//Buttons
	bool isDepthTest = true;
	bool isCullFace = true;
	bool isLighting = true;
	bool isColorMaterial = true;
	bool isGlTexture2D = true;
	bool isWireframe = false;

	bool switchDepthTest = true;
	bool switchCullFace = true;
	bool switchLighting = true;
	bool switchColorMaterial = true;
	bool switchGlTexture2D = true;

	bool drawNormals = false;
	bool isCheckerTex = false;
	bool drawTex = true;

	float brightness = 1.f;
	bool debug_draw = false;
};