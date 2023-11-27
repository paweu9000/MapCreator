#pragma once
#include "Entity.h"
#include <string>
#include "SDL.h"

class ButtonEntity : public Entity
{
public:
	ButtonEntity(class Program* program, std::string filename, const SDL_Rect& rect);
};