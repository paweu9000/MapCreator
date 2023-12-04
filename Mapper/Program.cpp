#include "Program.h"
#include "Entity.h"
#include "SDL_image.h"
#include <algorithm>
#include "SpriteComponent.h"
#include "ButtonEntity.h"
#include <iostream>
#include <filesystem>
#include "TileBox.h"
#include "Tile.h"
#include "SelectedTile.h"

Program::Program()
	:mIsRunning(true)
	,mRenderer(nullptr)
	,mWindow(nullptr)
	,mSelectedTile(nullptr)
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

void Program::LoadTiles(TileBox* tilebox)
{
	const std::filesystem::path currentPath = std::filesystem::current_path();
	auto loadFiles = [this, &tilebox](const std::filesystem::path path, int layer) {
			if (std::filesystem::exists(path) && std::filesystem::is_directory(path)) {
				for (const auto& entry : std::filesystem::directory_iterator(path)) {
					std::string fileName = entry.path().filename().string();
					std::string filePath = entry.path().string();
					SDL_Texture* texture = GetTexture(filePath);
					mTextures.emplace(fileName, texture);
					tilebox->AddTile(fileName, layer);
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
	bool clicked = false;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			mIsRunning = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			clicked = true;
		}
	}
	int mouseX, mouseY;
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX && mouseY && clicked)
	{
		for (auto entity : mEntities)
		{
			entity->ProcessMouseInput(mouseX, mouseY);
			if (entity->IsInBounds(mouseX, mouseY))
			{
				Tile* t = dynamic_cast<Tile*>(entity);
				SelectedTile* sTile = new SelectedTile(this, mouseX, mouseY, t->getLayer());
				auto sprite = new SpriteComponent(sTile, 205 + t->getLayer(), { mouseX, mouseY, 50, 50 });
				std::string textureName = t->GetTextureName();
				std::string& ref = textureName;
				sprite->SetTexture(this->GetTexture(ref));
				mSelectedTile = sTile;
			}
		}
	}
	if (mSelectedTile)
	{
		mSelectedTile->SetCoordinates(mouseX, mouseY);
	}
}

void Program::UpdateProgram()
{
	for (auto e : mEntities)
	{
		e->UpdateComponents();
	}
}

void Program::GenerateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 0);
	SDL_RenderClear(mRenderer);
	for (auto sprite : mSprites)
	{
		if (sprite->GetVisibility())
		{
			sprite->Draw(mRenderer);
		}
	}
	SDL_RenderPresent(mRenderer);
}

void Program::LoadData()
{
	SDL_Rect r{ 0, 0, 64, 64 };
	ButtonEntity* exitButton = new ButtonEntity(this, "textures/exit_button.png", r);
	auto exitButtonAction = [this]() {
		Shutdown();
	};
	exitButton->SetAction(exitButtonAction);
	TileBox* tilebox = new TileBox(this);
	ButtonEntity* layer1Button = new ButtonEntity(this, "textures/layer1_button.png", { 1310, 34, 16, 16 });
	ButtonEntity* layer2Button = new ButtonEntity(this, "textures/layer2_button.png", { 1330, 34, 16, 16 });
	ButtonEntity* layer3Button = new ButtonEntity(this, "textures/layer3_button.png", { 1350, 34, 16, 16 });
	auto changeToLayer1 = [tilebox]() {
		tilebox->SetActiveLayer(TileBox::ActiveLayer::LAYER1);
	};
	auto changeToLayer2 = [tilebox]() {
		tilebox->SetActiveLayer(TileBox::ActiveLayer::LAYER2);
	};
	auto changeToLayer3 = [tilebox]() {
		tilebox->SetActiveLayer(TileBox::ActiveLayer::LAYER3);
	};
	layer1Button->SetAction(changeToLayer1);
	layer2Button->SetAction(changeToLayer2);
	layer3Button->SetAction(changeToLayer3);
	LoadTiles(tilebox);
}

void Program::AddSprite(SpriteComponent* sprite)
{
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

	mSprites.insert(iter, sprite);
}

void Program::RemoveSprite(SpriteComponent* sprite)
{
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