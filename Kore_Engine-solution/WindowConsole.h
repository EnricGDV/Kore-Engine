#ifndef __WINDOWCONSOLE__
#define __WINDOWCONSOLE__

#include "Window.h"
#include <vector>


class WindowConsole : public Window
{
	WindowConsole();
	~WindowConsole();

	bool Start();
	bool Draw();
	bool CleanUp();


};

#endif 