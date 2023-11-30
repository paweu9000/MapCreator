#pragma once
#include "Entity.h"
#include <string>
#include "SDL.h"
#include <functional>

class ButtonEntity : public Entity
{
public:
	ButtonEntity(class Program* program, std::string filename, const SDL_Rect& rect);
	void SetAction(std::function<void()> action) { mAction = action; }
	void ExecuteAction() const { mAction(); }
	void ProcessMouseInput(int x, int y) override;
private:
	std::function<void()> mAction;
	SDL_Rect mRect;
};