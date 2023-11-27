#pragma once
#include <vector>

class Entity
{
public:
	Entity(class Program* program);
	~Entity();
	void UpdateComponents();
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
	Program* getProgram() const { return mProgram; }
protected:
	class Program* mProgram;
	std::vector<class Component*> mComponents;
};