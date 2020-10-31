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

	Component(GameObject* GameObj, Type type);
	virtual ~Component();

	virtual bool Update();
	virtual bool Draw();

public:

	GameObject* GameObj;
	Type type;
	
};

#endif