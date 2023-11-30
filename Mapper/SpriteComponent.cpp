#include "SpriteComponent.h"
#include "Entity.h"
#include "Program.h"
#include <iostream>

SpriteComponent::SpriteComponent(Entity* entity, int drawOrder, const SDL_Rect& rect)
	:Component(entity)
	,mTexture(nullptr)
	,mRect(rect)
	,mDrawOrder(drawOrder)
	,mTexWidth(0)
	,mTexHeight(0)
	,mVisible(true)
{
	mOwner->getProgram()->AddSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	mOwner->getProgram()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer)
{
	SDL_RenderCopy(renderer, mTexture, nullptr, &mRect);
}

void SpriteComponent::SetTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTexWidth, &mTexHeight);
}