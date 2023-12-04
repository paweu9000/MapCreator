#pragma once
#include "Entity.h"

class SelectedTile : public Entity
{
public:
	SelectedTile(class Program* program, int x, int y, int layer);
	void UpdateComponents() override;
	void SetCoordinates(int x, int y) { mX = x-25; mY = y-25; }
private:
	int mX;
	int mY;
	int mLayer;
};