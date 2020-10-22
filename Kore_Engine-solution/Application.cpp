#include "Application.h"

#include <iostream>
#include <list>

Application::Application()
{
	window = new ModuleWindow(this);
	input = new ModuleInput(this);
	scene_intro = new ModuleSceneIntro(this);
	renderer3D = new ModuleRenderer3D(this);
	camera = new ModuleCamera3D(this);
	ui = new ModuleUI(this);

	// The order of calls is very important!
	// Modules will Init() Start() and Update in this order
	// They will CleanUp() in reverse order

	// Main Modules
	AddModule(window);
	AddModule(camera);
	AddModule(input);

	// Scenes
	AddModule(scene_intro);
	AddModule(ui);

	// Renderer last!
	AddModule(renderer3D);
	
}

Application::~Application()
{
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end())
	{
		delete (*item);
		item++;
	}
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules

	std::list<Module*>::iterator item = list_modules.begin();

	while(item != list_modules.end() && ret == true)
	{
		ret = (*item)->Init();
		item++;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Start();
		item++;
	}

	ms_timer.Start();
	max_fps = FPS_LOG_SIZE;

	return ret;
}

// ---------------------------------------------
void Application::PrepareUpdate()
{
	dt = (float)ms_timer.Read() / 1000.0f;
	fps.push_back(1.0f / dt);
	if (fps.size() > FPS_LOG_SIZE)
	{
		fps.erase(fps.begin());
	}
	ms.push_back(ms_timer.Read());
	if (ms.size() > FPS_LOG_SIZE)
	{
		ms.erase(ms.begin());
	}
	ms_timer.Start();
}

// ---------------------------------------------
void Application::FinishUpdate()
{
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	PrepareUpdate();
	
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->PreUpdate(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->Update(dt);
		item++;
	}

	item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->PostUpdate(dt);
		item++;
	}

	FinishUpdate();
	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	std::list<Module*>::iterator item = list_modules.begin();

	while (item != list_modules.end() && ret == true)
	{
		ret = (*item)->CleanUp();
		item++;
	}

	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.push_back(mod);
}

void Application::RequestBrowser(const char* URL)
{
	ShellExecuteA(NULL, "open", URL, NULL, NULL, SW_SHOWNORMAL);
}

void Application::ConsoleLog(const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s", tmp_string);
	OutputDebugString(tmp_string2);

	//Implementation
	const char* log_str = tmp_string2;
	vector_log.push_back(log_str);
}