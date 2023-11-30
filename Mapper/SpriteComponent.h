#pragma once
#include "Component.h"
#include "SDL.h"

class SpriteComponent : public Component
{
public:
	SpriteComponent(class Entity* entity, int drawOrder = 100, const SDL_Rect& rect = {0,0,0,0});
	~SpriteComponent();

	virtual void Draw(SDL_Renderer* renderer);
	virtual void SetTexture(SDL_Texture* texture);

	int GetDrawOrder() const { return mDrawOrder; }
	int GetTexHeight() const { return mTexHeight; }
	int GetTexWidth() const { return mTexWidth; }
	void setVisibility(bool visibility) { mVisible = visibility; }
	bool GetVisibility() const { return mVisible; }
protected:
	SDL_Texture* mTexture;
	const SDL_Rect mRect;
	int mDrawOrder;
	int mTexWidth;
	int mTexHeight;
	bool mVisible;
};