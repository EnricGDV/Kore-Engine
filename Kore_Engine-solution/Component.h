#ifndef __COMPONENT__
#define __COMPONENT__


class GameObject;

enum Type
{
	TRANSFORM,
	MESH,
	MATERIAL,
	NONE
};

class Component
{
public:

	Component(GameObject* owner, Type type);
	virtual ~Component();

	virtual bool Enable();
	virtual bool Update();
	virtual bool Disable();

public:

	GameObject* owner;
	Type type;
	
	bool isActive = false;

};

#endif