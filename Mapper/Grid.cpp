#include "Grid.h"
#include "GridTile.h"
#include <string>

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