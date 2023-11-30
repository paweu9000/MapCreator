#include "Entity.h"
#include "Component.h"
#include "Program.h"
#include <algorithm>

Entity::Entity(Program* program)
	:mProgram(program)
{
	mProgram->addEntity(this);
}

Entity::~Entity()
{
	mProgram->RemoveEntity(this);
	while (!mComponents.empty())
	{
		delete mComponents.back();
	}
}

void Entity::AddComponent(Component* component)
{
	int mOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (; iter != mComponents.end(); ++iter)
	{
		if (mOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
}

void Entity::RemoveComponent(Component* component)
{
	auto iter = std::find(mComponents.begin(), mComponents.end(), component);
	if (iter != mComponents.end())
	{
		mComponents.erase(iter);
	}
}