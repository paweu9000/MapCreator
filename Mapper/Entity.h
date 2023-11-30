#pragma once
#include <vector>
#include "Component.h"

class Entity
{
public:
	Entity(class Program* program);
	~Entity();
	virtual void UpdateComponents()
	{
		for (auto component : mComponents)
		{
			component->Update();
		}
	}
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	Program* getProgram() const { return mProgram; }
protected:
	class Program* mProgram;
	std::vector<class Component*> mComponents;
};