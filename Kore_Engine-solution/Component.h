#ifndef __COMPONENT__
#define __COMPONENT__


class Component
{
public:

	Component();
	virtual ~Component();

	virtual bool Update();
	virtual bool Draw();

public:

	enum Type
	{
		TRANSFORM,
		MESH,
		MATERIAL,
		NONE
	};

};

#endif