#ifndef __MODULEUI__
#define __MODULEUI__

#include "Module.h"
#include "Application.h"
#include "GameObject.h"

class ModuleUI : public Module
{
public:

	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	bool Init();
	bool Start();
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

private: 

	std::vector<GameObject*> UI_elements;
};

#endif