#ifndef __WINDOWCONSOLE__
#define __WINDOWCONSOLE__

#include "Window.h"
#include <vector>


class WindowConsole : public Window
{
public:
	WindowConsole();
	~WindowConsole();

	bool Start();
	bool Draw();
	bool CleanUp();


	bool AutoScroll = true;
	bool ScrollToBottom = true;

};

#endif 