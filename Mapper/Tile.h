#pragma once
#include "Entity.h"
#include "Program.h"

class Tile : public Entity
{
public:
	Tile(Program* program, const SDL_Rect& rect, int layer);
	int getLayer() const { return mLayer; }
private:
	int mLayer;
};