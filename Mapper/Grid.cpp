#include "Grid.h"
#include "GridTile.h"
#include <string>
#include "Program.h"
#include <iostream>

Grid::Grid(Program* program, int x, int y)
	:Entity(program)
	, mX(x)
	, mY(y)
{
	mScale = 1.0f;
	LoadData();
}

void Grid::LoadData()
{
	std::string path = "textures/gridtileplaceholder.png";
	for (int i = 0; i < 13; i++)
	{
		mTiles.push_back(std::vector<GridTile*>{});
		for (int j = 0; j < 18; j++)
		{
			SDL_Rect place = { mX + (j * 50), mY + (i * 50), 50, 50 };
			GridTile* gTile = new GridTile(mProgram, place, path);
			mTiles[i].push_back(gTile);
		}
	}
}

void Grid::Draw(int mouseX, int mouseY)
{
	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			GridTile* gTile = mTiles[i][j];
			if (gTile->CheckBounds(mouseX, mouseY))
			{
				gTile->Draw(mProgram->GetSelectedTexture());
			}
		}
	}
}