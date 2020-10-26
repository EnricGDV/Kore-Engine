#ifndef __WINDOWINSPECTOR__
#define __WINDOWINSPECTOR__

#include "Window.h"

class WindowInspector : public Window
{
public:
	WindowInspector();
	~WindowInspector();

	bool Start();
	bool Draw();
	bool CleanUp();
};

#endif