#pragma once
#include <SDL.h>
#include <vector>
#include <unordered_map>
#include <string>

class Program
{
public:
	struct TileLayer
	{
		SDL_Texture* tile;
		int layer;
	};
	Program();
	bool Initialize();
	void RunLoop();
	void ProcessInput();
	void UpdateProgram();
	void GenerateOutput();
	void addEntity(class Entity* entity);
	void RemoveEntity(class Entity* entity);
	void AddSprite(class SpriteComponent* sprite);
	void RemoveSprite(class SpriteComponent* sprite);
	void LoadTiles();
	void LoadData();
	void Shutdown();
	SDL_Texture* GetTexture(std::string& filename);
private:
	bool mIsRunning;
	SDL_Renderer* mRenderer;
	SDL_Window* mWindow;
	std::vector<class Entity*> mEntities;
	std::vector<class SpriteComponent*> mSprites;
	std::unordered_map<std::string, SDL_Texture*> mTextures;
	std::unordered_map<std::string, TileLayer> mTiles;
};