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
	virtual void ProcessMouseInput(int x, int y) { /* To implement in child class */ }
	virtual bool IsInBounds(int x, int y) { return false; }
protected:
	class Program* mProgram;
	std::vector<class Component*> mComponents;
};