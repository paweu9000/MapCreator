#pragma once

class Component
{
public:
	Component(class Entity* owner, int updateOrder = 100);
	~Component();
	virtual void Update();
	int GetUpdateOrder() const { return mUpdateOrder; }
protected:
	// Update order of component
	int mUpdateOrder;
	class Entity* mOwner;
};