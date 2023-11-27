#include "Component.h"
#include "Entity.h"

Component::Component(Entity* entity, int updateOrder)
	:mOwner(entity)
	,mUpdateOrder(updateOrder)
{
	mOwner->AddComponent(this);
}

Component::~Component()
{
	mOwner->RemoveComponent(this);
}

void Component::Update()
{
}