#include "Program.h"
#include "Entity.h"

Program::Program()
	:mIsRunning(true)
	,mRenderer(nullptr)
	,mWindow(nullptr)
{}

bool Program::Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
		return false;
	}
	mWindow = SDL_CreateWindow("Map Creator", 100, 100, 1600, 900, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to initialize window: %s", SDL_GetError());
		return false;
	}
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to initialize renderer: %s", SDL_GetError());
		return false;
	}
	return true;
}

void Program::RunLoop()
{
	while (mIsRunning)
	{
		ProcessInput();
		UpdateProgram();
		GenerateOutput();
	}
}

void Program::ProcessInput()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		}
	}
}

void Program::UpdateProgram()
{

}

void Program::GenerateOutput()
{

}

void Program::addEntity(Entity* entity)
{
	mEntities.emplace_back(entity);
}

void Program::Shutdown()
{
	SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}