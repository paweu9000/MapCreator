#pragma once
#include "Entity.h"
#include <vector>

class SelectedTile : public Entity
{
public:
	SelectedTile(class Program* program, int x, int y, int layer);
	void UpdateComponents() override;
	void SetCoordinates(int x, int y) { mX = x-25; mY = y-25; }
	std::vector<Component*> GetComponents() { return mComponents; }
	int GetLayer() { return mLayer; }
private:
	int mX;
	int mY;
	int mLayer;
};