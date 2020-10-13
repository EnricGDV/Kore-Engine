#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Globals.h"


class Window
{
public:

	Window();
	virtual ~Window();

	virtual bool Start();
	virtual bool Draw();
	virtual update_status PreUpdate(float dt);
	virtual update_status PostUpdate(float dt);
	virtual bool CleanUp();

public:
	bool active;
};

#endif // !__WINDOW_H__

