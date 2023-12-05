#pragma once
#include "Entity.h"
#include <SDL.h>
#include <string>

class GridTile : public Entity
{
public:
	GridTile(class Program* program, SDL_Rect rect, std::string& path);
	void SetScale(float scale) { mScale = scale; }
	float GetScale() { return mScale; }
private:
	float mScale;
	SDL_Rect mRect;
};