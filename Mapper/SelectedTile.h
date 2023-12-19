#pragma once
#include "Entity.h"
#include <vector>
#include <string>

class SelectedTile : public Entity
{
public:
	SelectedTile(class Program* program, int x, int y, int layer, std::string tName);
	void UpdateComponents() override;
	void SetCoordinates(int x, int y) { mX = x-25; mY = y-25; }
	std::vector<Component*> GetComponents() { return mComponents; }
	int GetLayer() { return mLayer; }
	std::string getTextureName() const { return mTextureName; }
private:
	int mX;
	int mY;
	int mLayer;
	std::string mTextureName;
};