#pragma once
#include <SDL.h>
#include <vector>

class Program
{
public:
	Program();
	bool Initialize();
	void RunLoop();
	void ProcessInput();
	void UpdateProgram();
	void GenerateOutput();
	void addEntity(class Entity* entity);
	void Shutdown();
private:
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	std::vector<class Entity*> mEntities;
};