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
	std::string empty_str = "";
	for (int i = 0; i < 13; i++)
	{
		mTiles.emplace_back(std::vector<GridLayer>{});
		for (int j = 0; j < 18; j++)
		{
			SDL_Rect place = { mX + (j * 50), mY + (i * 50), 50, 50 };
			GridTile* gTile1 = new GridTile(mProgram, place, path, 1);
			GridTile* gTile2 = new GridTile(mProgram, place, empty_str, 2);
			GridTile* gTile3 = new GridTile(mProgram, place, empty_str, 3);
			GridLayer gLayer = { gTile1, gTile2, gTile3 };
			mTiles[i].push_back(gLayer);
		}
	}
}

void Grid::Draw(int mouseX, int mouseY, int layer)
{
	for (int i = 0; i < mTiles.size(); i++)
	{
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			GridTile* gTile = nullptr;
			switch (layer)
			{
			case 1:
				gTile = mTiles[i][j].l1tile;
				break;
			case 2:
				gTile = mTiles[i][j].l2tile;
				break;
			case 3:
				gTile = mTiles[i][j].l3tile;
				break;
			}
			if (gTile && gTile->CheckBounds(mouseX, mouseY))
			{
				gTile->Draw(mProgram->GetSelectedTexture());
				gTile->setTextureName(mProgram->GetSelectedTextureName());
			}
		}
	}
}

void Grid::getGridData()
{
	const std::string placeholder = "textures/gridtileplaceholder.png";
	for (int i = 0; i < mTiles.size(); i++)
	{
		std::cout << "\n";
		for (int j = 0; j < mTiles[i].size(); j++)
		{
			GridLayer l = mTiles[i][j];
			std::cout << "[";
			std::cout << l.l1tile->getTextureName();
			std::cout << ",";
			std::cout << l.l2tile->getTextureName();
			std::cout << ",";
			std::cout << l.l3tile->getTextureName();
			std::cout << "],";
		}
	}
	std::cout << "\n\n";
}