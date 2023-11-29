#include "Program.h"
#include "Entity.h"
#include "SDL_image.h"
#include <algorithm>
#include "SpriteComponent.h"
#include "ButtonEntity.h"
#include <iostream>
#include <filesystem>
#include "TileBox.h"

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
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		SDL_Log("Failed to initialize SDL_Image: %s", SDL_GetError());
	}

	LoadData();

	return true;
}

SDL_Texture* Program::GetTexture(std::string& filename)
{
	SDL_Texture* texture = nullptr;
	auto iter = mTextures.find(filename);
	if (iter != mTextures.end())
	{
		texture = iter->second;
	}
	else
	{
		SDL_Surface* surface = IMG_Load(filename.c_str());
		if (!surface)
		{
			SDL_Log("Failed to load texture file %s", filename);
			return nullptr;
		}

		texture = SDL_CreateTextureFromSurface(mRenderer, surface);
		SDL_FreeSurface(surface);
		if (!texture)
		{
			SDL_Log("Failed to convert surface to texture for %s", filename);
			return nullptr;
		}
		mTextures.emplace(filename, texture);
	}
	return texture;
}

void Program::LoadTiles()
{
	const std::filesystem::path currentPath = std::filesystem::current_path();
	auto loadFiles = [this](const std::filesystem::path path, int layer) {
			if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					std::string fileName = entry.path().filename().string();
					std::string filePath = entry.path().string();
					SDL_Texture* texture = GetTexture(filePath);
					Program::TileLayer newTile = { texture, layer };
					mTiles.emplace(fileName, newTile);
					std::cout << "Put tile " << fileName << "\n";
				}
			}
			else {
				std::cerr << "Directory not found: " << path << std::endl;
			}
		};
	const std::filesystem::path layer1Path = currentPath / "tiles" / "layer1";
	const std::filesystem::path layer2Path = currentPath / "tiles" / "layer2";
	const std::filesystem::path layer3Path = currentPath / "tiles" / "layer3";
	loadFiles(layer1Path, 1);
	loadFiles(layer2Path, 2);
	loadFiles(layer3Path, 3);
}

void Program::RemoveEntity(Entity* entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		mEntities.erase(iter);
	}
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
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(mRenderer);
	for (auto sprite : mSprites)
	{
		sprite->Draw(mRenderer);
	}
	SDL_RenderPresent(mRenderer);
}

void Program::LoadData()
{
	SDL_Rect r{ 0, 0, 64, 64 };
	ButtonEntity* button = new ButtonEntity(this, "textures/exit_button.png", r);
	TileBox* tilebox = new TileBox(this);
	LoadTiles();
}

void Program::AddSprite(SpriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->GetDrawOrder();
	auto iter = mSprites.begin();
	for (;
		iter != mSprites.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void Program::RemoveSprite(SpriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
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