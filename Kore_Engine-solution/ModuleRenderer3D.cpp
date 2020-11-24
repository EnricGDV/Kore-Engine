#include "Color.h"
#include "Globals.h"
#include "Application.h"
#include "ModuleRenderer3D.h"
#include "ModuleUI.h"
#include "ModuleSceneIntro.h"
#include "Libraries/Glew/include/GL/glew.h"
#include "Libraries/SDL/include/SDL_opengl.h"
#include "Importer.h"
#include "GameObject.h"
#include <gl/GL.h>
#include <gl/GLU.h>

#pragma comment (lib, "glu32.lib")    /* link OpenGL Utility lib     */
#pragma comment (lib, "opengl32.lib") /* link Microsoft OpenGL lib   */

ModuleRenderer3D::ModuleRenderer3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

// Destructor
ModuleRenderer3D::~ModuleRenderer3D()
{}

// Called before render is available
bool ModuleRenderer3D::Init()
{
	LOG("Creating 3D Renderer context");
	App->ConsoleLog("Creating 3D Renderer context");
	bool ret = true;
	
	//Create context
	context = SDL_GL_CreateContext(App->window->window);
	if(context == NULL)
	{
		LOG("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		App->ConsoleLog("OpenGL context could not be created! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	
	if(ret == true)
	{
		
		//LOG GL Properties
		LOG("Vendor: %s", glGetString(GL_VENDOR));
		LOG("Renderer: %s", glGetString(GL_RENDERER));
		LOG("OpenGL version supported %s", glGetString(GL_VERSION));
		LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
		App->ConsoleLog("Vendor: %s", glGetString(GL_VENDOR));
		App->ConsoleLog("Renderer: %s", glGetString(GL_RENDERER));
		App->ConsoleLog("OpenGL version supported %s", glGetString(GL_VERSION));
		App->ConsoleLog("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

		//Use Vsync
		if (VSYNC && SDL_GL_SetSwapInterval(1) < 0)
		{
			LOG("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
			App->ConsoleLog("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
		}
			

		//Initialize Glew
		GLenum err = glewInit();
		LOG("Using Glew %s", glewGetString(GLEW_VERSION));
		App->ConsoleLog("Using Glew %s", glewGetString(GLEW_VERSION));
		//Initialize Projection Matrix
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		//Check for error
		GLenum error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->ConsoleLog("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}

		//Initialize Modelview Matrix
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->ConsoleLog("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glClearDepth(1.0f);
		
		
		//Initialize clear color
		glClearColor(0.f, 0.f, 0.f, 1.f);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//Check for error
		error = glGetError();
		if(error != GL_NO_ERROR)
		{
			LOG("Error initializing OpenGL! %s\n", gluErrorString(error));
			App->ConsoleLog("Error initializing OpenGL! %s\n", gluErrorString(error));
			ret = false;
		}
		
		GLfloat LightModelAmbient[] = {0.0f, 0.0f, 0.0f, 1.0f};
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, LightModelAmbient);
		
		lights[0].ref = GL_LIGHT0;
		lights[0].ambient.Set(0.25f, 0.25f, 0.25f, 1.0f);
		lights[0].diffuse.Set(0.75f, 0.75f, 0.75f, 1.0f);
		lights[0].SetPos(0.0f, 0.0f, 2.5f);
		lights[0].Init();
		
		GLfloat MaterialAmbient[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, MaterialAmbient);

		GLfloat MaterialDiffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, MaterialDiffuse);

		
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		lights[0].Active(true);
		glEnable(GL_LIGHTING);
		glEnable(GL_COLOR_MATERIAL);
		glEnable(GL_TEXTURE_2D);

		//Transparency
		//glEnable(GL_ALPHA_TEST);
		//glAlphaFunc(GL_GREATER, 0.5);

		//Blending
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	// Projection matrix for
	OnResize(App->window->width, App->window->height);
	glBindTexture(GL_TEXTURE_2D, 0);

	return ret;
}

bool ModuleRenderer3D::Start()
{
	//float cubeArray[] = { -2.f, 0.f, 1.f, -2.f, 0.f, 0.f, -1.f, 0.f, 0.f, -1.f, 0.f, 0.f, -1.f, 0.f, 1.f, -2.f, 0.f, 1.f,
	//					  -2.f, 1.f, 0.f, -2.f, 1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f, 0.f, -2.f, 1.f, 0.f,
	//					  -2.f, 0.f, 0.f, -2.f, 0.f, 1.f, -2.f, 1.f, 1.f, -2.f, 1.f, 1.f, -2.f, 1.f, 0.f, -2.f, 0.f, 0.f,
	//					  -1.f, 0.f, 1.f, -1.f, 0.f, 0.f, -1.f, 1.f, 0.f, -1.f, 1.f, 0.f, -1.f, 1.f, 1.f, -1.f, 0.f, 1.f,
	//					  -2.f, 0.f, 1.f, -1.f, 0.f, 1.f, -1.f, 1.f, 1.f, -1.f, 1.f, 1.f, -2.f, 1.f, 1.f, -2.f, 0.f, 1.f,
	//					  -2.f, 0.f, 0.f, -2.f, 1.f, 0.f, -1.f, 1.f, 0.f, -1.f, 1.f, 0.f, -1.f, 0.f, 0.f, -2.f, 0.f, 0.f };
	

	float cubeArray[] = { -2.f, 0.f, 1.f,  -1.f, 0.f, 1.f,  -1.f, 0.f, 0.f,  -2.f, 0.f, 0.f,  -2.f, 1.f, 1.f,  -1.f, 1.f, 1.f,  -1.f, 1.f, 0.f,  -2.f, 1.f, 0.f,
						  -2.f, 0.f, 1.f,  -1.f, 0.f, 1.f,  -1.f, 0.f, 0.f,  -2.f, 0.f, 0.f,  -2.f, 1.f, 1.f,  -1.f, 1.f, 1.f,  -1.f, 1.f, 0.f,  -2.f, 1.f, 0.f, 
						  -2.f, 0.f, 1.f,  -1.f, 0.f, 1.f,  -1.f, 0.f, 0.f,  -2.f, 0.f, 0.f,  -2.f, 1.f, 1.f,  -1.f, 1.f, 1.f,  -1.f, 1.f, 0.f,  -2.f, 1.f, 0.f };

	uint cubeIndex[] = {0, 3, 2, 2, 1, 0,   4, 5, 6, 6, 7, 4,   8, 12, 15, 15, 11, 8,   9, 10, 14, 14, 13, 9,   16, 17, 21, 21, 20, 16,   19, 23, 22, 22, 18, 19};

	float cubeUVs [] = { 0.f, 1.f,  1.f, 1.f,  1.f, 0.f,  0.f, 0.f,  0.f, 0.f,  1.f, 0.f,  1.f, 1.f,  0.f, 1.f,
						 1.f, 0.f,  0.f, 0.f,  1.f, 0.f,  0.f, 0.f,  1.f, 1.f,  0.f, 1.f,  1.f, 1.f,  0.f, 1.f,
						 0.f, 0.f,  1.f, 0.f,  1.f, 0.f,  0.f, 0.f,  0.f, 1.f,  1.f, 1.f,  1.f, 1.f,  0.f, 1.f };
	uvs = cubeUVs;

	int colorArray[] = { 100, 51, 55 };

	cube_id = 0;
	glGenBuffers(1, (GLuint*) & (cube_id));
	glBindBuffer(GL_ARRAY_BUFFER, cube_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 72, cubeArray, GL_STATIC_DRAW);
	index_id = 1;
	glGenBuffers(1, (GLuint*) & (index_id));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 36, cubeIndex, GL_STATIC_DRAW);
	uvs_id = 3;
	glGenBuffers(1, (GLuint*) & (uvs_id));
	glBindBuffer(GL_ARRAY_BUFFER, uvs_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 48, cubeUVs, GL_STATIC_DRAW);

	color_id = 2;
	glGenBuffers(1, (GLuint*) & (color_id));
	glBindBuffer(GL_COLOR_BUFFER_BIT, color_id);
	glBufferData(GL_COLOR_BUFFER_BIT, sizeof(int) * 3, colorArray, GL_STATIC_DRAW);

	GenerateMeshes();
	GenerateTextures();


	return true;
}

// PreUpdate: clear buffer
update_status ModuleRenderer3D::PreUpdate(float dt)
{
	//Buttons

	if (switchDepthTest && !isDepthTest)
	{
		glEnable(GL_DEPTH_TEST);
		isDepthTest = true;
	}
	else if (!switchDepthTest && isDepthTest)
	{
		glDisable(GL_DEPTH_TEST);
		isDepthTest = false;
	}

	if (switchCullFace && !isCullFace)
	{
		glEnable(GL_CULL_FACE);
		isCullFace = true;
	}
	else if (!switchCullFace && isCullFace)
	{
		glDisable(GL_CULL_FACE);
		isCullFace = false;
	}

	if (switchLighting && !isLighting)
	{
		glEnable(GL_LIGHTING);
		isLighting = true;
	}
	else if (!switchLighting && isLighting)
	{
		glDisable(GL_LIGHTING);
		isLighting = false;
	}

	if (switchGlTexture2D && !isGlTexture2D)
	{
		glEnable(GL_TEXTURE_2D);
		isGlTexture2D = true;
	}
	else if (!switchGlTexture2D && isGlTexture2D)
	{
		glDisable(GL_TEXTURE_2D);
		isGlTexture2D = false;
	}



	Color c = Black;
	glClearColor(c.r, c.g, c.b, c.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(App->camera->GetViewMatrix());
	


	//PLANE

	glLineWidth(1.0f);

	glBegin(GL_LINES);

	float d = 200.0f;

	for (float i = -d; i <= d; i += 1.0f)
	{
		glVertex3f(i, 0.0f, -d);
		glVertex3f(i, 0.0f, d);
		glVertex3f(-d, 0.0f, i);
		glVertex3f(d, 0.0f, i);
	}

	glEnd();



	//AXIS

	glLineWidth(2.0f);

	glBegin(GL_LINES);

	glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(1.0f, 0.0f, 0.0f);
	glVertex3f(1.0f, 0.1f, 0.0f); glVertex3f(1.1f, -0.1f, 0.0f);
	glVertex3f(1.1f, 0.1f, 0.0f); glVertex3f(1.0f, -0.1f, 0.0f);

	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.05f, 1.25f, 0.0f); glVertex3f(0.0f, 1.15f, 0.0f);
	glVertex3f(0.0f, 1.15f, 0.0f); glVertex3f(0.0f, 1.05f, 0.0f);

	glColor4f(0.0f, 0.0f, 1.0f, 1.0f);

	glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.05f, 0.1f, 1.05f); glVertex3f(0.05f, 0.1f, 1.05f);
	glVertex3f(0.05f, 0.1f, 1.05f); glVertex3f(-0.05f, -0.1f, 1.05f);
	glVertex3f(-0.05f, -0.1f, 1.05f); glVertex3f(0.05f, -0.1f, 1.05f);

	glEnd();

	glLineWidth(1.0f);
		
	glColor3f(1.0f, 1.0f, 1.0f);




	/*glBegin(GL_POLYGON);
	glColor3b(100, 51, 55);
	glVertex3f(0.f, 0.f, 0.f);
	glColor3b(100, 51, 55);
	glVertex3f(0.f, 0.f, 1.f);
	glColor3b(100, 51, 55);
	glVertex3f(1.f, 1.f, 1.f);
	glColor3b(100, 51, 55);
	glVertex3f(1.f, 1.f, 0.f);
	glEnd();

	glBegin(GL_TRIANGLE_STRIP);
	glColor3b(100, 51, 55);
	glVertex3f(2.f, 2.f, 2.f);
	glColor3b(100, 51, 55);
	glVertex3f(2.f, 2.f, 3.f);
	glColor3b(100, 51, 55);
	glVertex3f(3.f, 2.f, 2.f);
	glColor3b(100, 51, 55);
	glVertex3f(3.f, 2.f, 3.f);
	glColor3b(100, 51, 55);
	glVertex3f(4.f, 3.f, 2.f);
	glColor3b(100, 51, 55);
	glVertex3f(4.f, 3.f, 3.f);
	glEnd();*/


	//// CUBE
	//glBindTexture(GL_TEXTURE_2D, checkerImage_id);
	//glBegin(GL_TRIANGLES);
	////1stface
	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 0.f, 1.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 0.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 0.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 0.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 0.f, 1.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 0.f, 1.f);

	////2ndface
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 1.f, 0.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 1.f, 0.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 1.f, 0.f);

	////3rdface
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 0.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 0.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-2.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-2.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-2.f, 1.f, 0.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 0.f);

	////4thface
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 1.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 0.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 0.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 0.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 1.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 1.f);

	////5thface
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 1.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 1.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 1.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 1.f, 1.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 1.f);

	////6thface
	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 0.f);

	//glTexCoord2f(0.0f, 1.0f);
	//glVertex3f(-2.f, 1.f, 0.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 0.f);

	//glTexCoord2f(1.0f, 1.0f);
	//glVertex3f(-1.f, 1.f, 0.f);

	//glTexCoord2f(1.0f, 0.0f);
	//glVertex3f(-1.f, 0.f, 0.f);

	//glTexCoord2f(0.0f, 0.0f);
	//glVertex3f(-2.f, 0.f, 0.f);

	//glRotatef(0.5f, 1.f, 1.f, 0.f);
	//glEnd();
	//glBindTexture(GL_TEXTURE_2D, 0);
	/////


	// light 0 on cam pos
	lights[0].SetPos(App->camera->Position.x, App->camera->Position.y, App->camera->Position.z);

	for(uint i = 0; i < MAX_LIGHTS; ++i)
		lights[i].Render();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRenderer3D::PostUpdate(float dt)
{
	App->scene_intro->Draw();
	if (debug_draw == true)
	{
		/*BeginDebugDraw();
		App->DebugDraw();
		EndDebugDraw();*/
	}

	for (int i = 0; i < App->scene_intro->meshes.size(); ++i)
	{
		if (App->scene_intro->rootGameObject->active)
		{
			if (App->scene_intro->gameObjects[i]->material->isCheckers)
			{
				isCheckerTex = true;
			}
			if (!App->scene_intro->gameObjects[i]->material->isCheckers)
			{
				isCheckerTex = false;
			}
			if (App->scene_intro->gameObjects[i]->material->isActive)
			{
				drawTex = true;
			}
			if (!App->scene_intro->gameObjects[i]->material->isActive)
			{
				drawTex = false;
			}
			if (App->scene_intro->gameObjects[i]->active && App->scene_intro->gameObjects[i]->mesh->isActive && App->scene_intro->gameObjects[i]->mesh->type == Type::MESH)
			{
				Draw(&App->scene_intro->meshes[i], App->scene_intro->gameObjects[i]->transform->matrix);
			}
		}
		
	}

	//glEnableClientState(GL_VERTEX_ARRAY);
	//glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	//////glBindBuffer(GL_COLOR_BUFFER_BIT, color_id);
	//////glColorPointer(3, GL_INT, 0, NULL);
	//glBindBuffer(GL_ARRAY_BUFFER, cube_id);
	//glVertexPointer(3, GL_FLOAT, 0, NULL);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_id);
	//glBindBuffer(GL_ARRAY_BUFFER, uvs_id);
	//glTexCoordPointer(2, GL_FLOAT, 0, NULL);
	////glDrawArrays(GL_TRIANGLES, 0, 36);
	//glBindTexture(GL_TEXTURE_2D, checkerImage_id);
	//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, NULL);
	//glBindTexture(GL_TEXTURE_2D, 0);
	//glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	//glDisableClientState(GL_VERTEX_ARRAY);

	App->ui->Draw();
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRenderer3D::CleanUp()
{
	LOG("Destroying 3D Renderer");
	App->ConsoleLog("Destroying 3D Renderer");
	SDL_GL_DeleteContext(context);

	return true;
}


void ModuleRenderer3D::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	ProjectionMatrix = perspective(60.0f, (float)width / (float)height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void ModuleRenderer3D::GenerateMeshes()
{
	for (int i = 0; i < App->scene_intro->meshes.size(); ++i)
	{

		glGenBuffers(1, (GLuint*) & (App->scene_intro->meshes[i].id_vertex));
		glBindBuffer(GL_ARRAY_BUFFER, App->scene_intro->meshes[i].id_vertex);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * App->scene_intro->meshes[i].num_vertices * 3, App->scene_intro->meshes[i].vertices, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*) & (App->scene_intro->meshes[i].id_index));
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, App->scene_intro->meshes[i].id_index);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * App->scene_intro->meshes[i].num_indices, App->scene_intro->meshes[i].indices, GL_STATIC_DRAW);


			glGenBuffers(1, (GLuint*) & (App->scene_intro->meshes[i].id_texcoord));
			glBindBuffer(GL_ARRAY_BUFFER, App->scene_intro->meshes[i].id_texcoord);
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * App->scene_intro->meshes[i].num_vertices * 2, App->scene_intro->meshes[i].textureCoords, GL_STATIC_DRAW);

		glGenBuffers(1, (GLuint*) & (App->scene_intro->meshes[i].id_normal));
		glBindBuffer(GL_ARRAY_BUFFER, App->scene_intro->meshes[i].id_normal);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * App->scene_intro->meshes[i].num_vertices * 3, App->scene_intro->meshes[i].normals, GL_STATIC_DRAW);
	}

}

void ModuleRenderer3D::GenerateTextures()
{
	GLubyte checkerImage[32][32][4];
	for (int i = 0; i < 32; i++) {
		for (int j = 0; j < 32; j++) {
			int c = ((((i & 0x8) == 0) ^ (((j & 0x8)) == 0))) * 255;
			checkerImage[i][j][0] = (GLubyte)c;
			checkerImage[i][j][1] = (GLubyte)c;
			checkerImage[i][j][2] = (GLubyte)c;
			checkerImage[i][j][3] = (GLubyte)255;
		}
	}

	checkerImage_id = 0;
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, &checkerImage_id);
	glBindTexture(GL_TEXTURE_2D, checkerImage_id);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 32, 32, 0, GL_RGBA, GL_UNSIGNED_BYTE, checkerImage);

	/*for (int i = 0; i < App->scene_intro->textures.size(); ++i)
	{
		glGenTextures(1, &App->scene_intro->textures[i].id);
		glBindTexture(GL_TEXTURE_2D, App->scene_intro->textures[i].id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 512, 512, 0, GL_RGBA, GL_UNSIGNED_BYTE, App->scene_intro->textures[i].data);
	}*/
	
}

void ModuleRenderer3D::Draw(myMesh* mesh, float4x4 transform)
{
	glPushMatrix();
	glMultMatrixf((GLfloat*)&transform.Transposed());


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);		
	glEnableClientState(GL_NORMAL_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_vertex);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->id_index);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_texcoord);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	if (isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glColor3f(0.f, 1.f, 0.5f);
	}
	
	if (drawNormals)
	{

		for (int i = 0; i < mesh->num_vertices * 3; i += 3)
		{
			glBegin(GL_LINES);
			glColor3f(0.f, 1.f, 0.f);

			float vX = mesh->vertices[i];
			float vY = mesh->vertices[i + 1];
			float vZ = mesh->vertices[i + 2];

			
			glVertex3f(vX, vY, vZ);
			glVertex3f(vX + mesh->normals[i], vY + mesh->normals[i + 1], vZ + mesh->normals[i + 2]);
		}

		glEnd();
		glColor3f(1.f, 1.f, 1.f);
	}

	glBindBuffer(GL_ARRAY_BUFFER, mesh->id_normal);
	glNormalPointer(GL_FLOAT, 0, NULL);
	

	if (drawTex && App->scene_intro->textures.size() > 0)
	{
		if (isCheckerTex)
			glBindTexture(GL_TEXTURE_2D, checkerImage_id);
		if (!isCheckerTex)
			glBindTexture(GL_TEXTURE_2D, App->scene_intro->textures[0].id);
	}
	else
	{
		if (isCheckerTex)
			glBindTexture(GL_TEXTURE_2D, checkerImage_id);
	}


	glDrawElements(GL_TRIANGLES, mesh->num_indices, GL_UNSIGNED_INT, NULL);
	if ((drawTex && App->scene_intro->textures.size() > 0) || isCheckerTex)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	

	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (isWireframe)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColor3f(1.f, 1.f, 1.f);
	}

	glPopMatrix();
}