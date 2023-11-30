#pragma once
#include "Entity.h"
#include "Program.h"
#include <string>
#include "SDL.h"

class Tile : public Entity
{
public:
	Tile(Program* program, const SDL_Rect rect, std::string fileName, int layer);
	int getLayer() const { return mLayer; }
	void setVisibility(bool visibility) { mVisible = visibility; }
	void UpdateComponents() override;
private:
	int mLayer;
	bool mVisible;
};