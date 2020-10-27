#ifndef __WINDOWABOUT__
#define __WINDOWABOUT__

#include "Window.h"

class WindowAbout : public Window
{
public:

	WindowAbout();
	~WindowAbout();

	bool Start();
	bool Draw();
	bool CleanUp();

};

#endif