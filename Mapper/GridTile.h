#pragma once
#include "Entity.h"
#include <SDL.h>
#include <string>

class GridTile : public Entity
{
public:
	GridTile(class Program* program, SDL_Rect rect, std::string& path, int layer);
	void SetScale(float scale) { mScale = scale; }
	float GetScale() const { return mScale; }
	bool CheckBounds(int x, int y);
	void Draw(SDL_Texture* texture);
private:
	float mScale;
	SDL_Rect mRect;
	int mLayer;
};