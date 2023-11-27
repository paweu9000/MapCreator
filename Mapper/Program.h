#pragma once
#include <SDL.h>

class Program
{
public:
	Program();
	bool Initialize();
	void RunLoop();
	void ProcessInput();
	void UpdateProgram();
	void GenerateOutput();
	void Shutdown();
private:
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
};