#ifndef __WINDOWMENUBAR__ 
#define __WINDOWMENUBAR__

#include "Window.h"

class WindowMenuBar : public Window
{
public: 
	WindowMenuBar();
	~WindowMenuBar();

	bool Start();
	bool Draw();
	bool CleanUp();

};


#endif