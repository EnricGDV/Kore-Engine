#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"

#include "Libraries/SDL/include/SDL.h"

#include <GL/glew.h>

#include "Libraries/ImGui/imgui.h"
#include "Libraries/ImGui/imgui_impl_sdl.h"
#include "Libraries/ImGui/imgui_impl_opengl3.h"

#include "Window.h"
#include "WindowConsole.h"
#include "WindowAbout.h"
#include "WindowConfig.h"
#include "WindowHierarchy.h"
#include "WindowInspector.h"
#include "WindowMenuBar.h"

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
	bool Draw();
	bool CleanUp();


public:

	ImFont* font;

	//Enable windows
	bool demoIsActive = false;
	bool aboutIsActive = false;
	bool consoleIsActive = true;
	bool configIsActive = true;
	bool hierarchyIsActive = true;
	bool inspectorIsActive = false;

	//Config
	char* textname;
	char* textorganization;

	//Windows
	WindowConsole* console = nullptr;
	WindowAbout* about = nullptr;
	WindowConfig* config = nullptr;
	WindowHierarchy* hierarchy = nullptr;
	WindowInspector* inspector = nullptr;
	WindowMenuBar* menubar = nullptr;

	// Config Window //
	float brightness;

	//Window Size
	int windowWidth;
	int windowHeight;

	//Checkboxes
	bool fullscreen = false;
	bool isFullscreen = false;
	bool resizable = false;
	bool isResizable = false;
	bool borderless = false;
	bool isBorderless = false;
	bool fulldesktop = false;
	bool isFulldesktop = false;

	std::list<Window*> windows;
};

#endif // __ModuleWindow_H__