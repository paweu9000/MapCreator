#pragma once
#include "Component.h"
#include "SDL.h"
#include <iostream>

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Entity* entity, int drawOrder = 100, SDL_Rect rect = {0,0,0,0});
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	void setVisibility(bool visibility) { mVisible = visibility; }
	bool GetVisibility() const { return mVisible; }
	void SetRect(SDL_Rect rect) { mRect = rect; }
	SDL_Texture* GetTexture() { return mTexture; }
protected:
	SDL_Texture* mTexture;
	SDL_Rect mRect;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mVisible;
};