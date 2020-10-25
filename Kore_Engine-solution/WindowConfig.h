#ifndef __WINDOWCONFIG__
#define __WINDOWCONFIG__

#include "Window.h"

class WindowConfig : public Window
{
	WindowConfig();
	~WindowConfig();

	bool Start();
	bool Draw();
	bool CleanUp();

};

#endif