#include "../lib/Hydra Engine/Hydra.h"
#include "Absorbable.h"
#include "Cell.h"
#include "SuperCell.h"
using namespace Hydra;

#define GRID_X 20
#define GRID_Y 20

void drawGrid(int xPos, int yPos);

int main(int argc, char* argv[])
{
	srand(SDL_GetTicks());
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();
	engine->setWTitle("Agar.exe, the free port of Agar.io");
	SDL_Renderer* renderer = engine->getRenderer();


	vector<Cell*> cells;

	SuperCell playerCells;
	Cell cell(200);
	cells.push_back(&cell);
	playerCells.addCell(&cell);

	float vX = 0, vY = 0; //Viewer X and Y

	bool quit = false;
	while (!quit)
	{
		Timer fps;
		fps.start();

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				quit = true;
			if (event.key.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_SPACE)
				playerCells.split(&cells);
		}

		int mX, mY;
		SDL_GetMouseState(&mX, &mY);

		vX = playerCells.getCMassX(); //Viewer coordinates dependent on the supercell's center of mass
		vY = playerCells.getCMassY();
		playerCells.setAbTarget(mX + vX - (engine->getWXSize() / 2.f), mY + vY - (engine->getWYSize() / 2.f));
		playerCells.moveToTarget();

		//Graphics
		SDL_RenderClear(renderer);
		drawGrid(-vX, -vY);

		for (auto iter = cells.begin(); iter != cells.end(); iter++)
		{
			if (*iter == nullptr)
				continue;
			(*iter)->move();
			(*iter)->draw(renderer, vX - (engine->getWXSize() / 2.f), vY - (engine->getWYSize() / 2.f), 1);
		}

		SDL_RenderPresent(renderer);
		while (fps.getTime() < 16);
	}
	engine->shutdown();
}

void drawGrid(int xPos, int yPos)
{
	//Draw in the background, a dark grey color
	SDL_Rect rect;
	HydraEngine* engine = HydraEngine::getInstance();
	rect.x = 0; rect.y = 0;
	rect.w = engine->getWXSize(); rect.h = engine->getWYSize();
	SDL_SetRenderDrawColor(engine->getRenderer(), 39, 39, 39, 255);
	SDL_RenderFillRect(engine->getRenderer(), &rect);

	//Draw in the grid
	SDL_SetRenderDrawColor(engine->getRenderer(), 125, 125, 125, 255);
	for (int iX = -xPos / GRID_X; iX <= (engine->getWXSize() / GRID_X) + abs(xPos); iX++)
		SDL_RenderDrawLine(engine->getRenderer(), (iX * GRID_X) + xPos, 0, (iX * GRID_X) + xPos, engine->getWYSize());
	for (int iY = -yPos / GRID_Y; iY <= (engine->getWYSize() / GRID_Y) + abs(yPos); iY++)
		SDL_RenderDrawLine(engine->getRenderer(), 0, (iY * GRID_Y) + yPos, engine->getWXSize(), (iY * GRID_Y) + yPos);
}
