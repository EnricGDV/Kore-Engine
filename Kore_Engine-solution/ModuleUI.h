#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "Libraries/SDL/include/SDL.h"

#include <GL/glew.h>

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"

class Application;

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);

	// Destructor
	virtual ~ModuleUI();

	bool Init();
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	void Draw();
	bool CleanUp();


public:

	ImFont* font;

	bool demoIsActive = false;
	bool aboutIsActive = false;
	bool consoleIsActive = true;
	bool configIsActive = true;

	//Config
	char* textname;
	char* textorganization;



};

#endif // __ModuleWindow_H__