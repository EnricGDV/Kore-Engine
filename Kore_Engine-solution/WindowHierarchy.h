#ifndef __WINDOWHIERARCHY__
#define __WINDOWHIERARCHY__

#include "Window.h"

class WindowHierarchy : public Window
{
public:
	WindowHierarchy();
	~WindowHierarchy();


	bool Start();
	bool Draw();
	bool CleanUp();
};

#endif