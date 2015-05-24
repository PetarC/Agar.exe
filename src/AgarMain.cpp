#include "../lib/Hydra Engine/Hydra.h"
using namespace Hydra;

#define GRID_X 15
#define GRID_Y 15

void drawGrid(int xPos, int yPos);

int main(int argc, char* argv[])
{
	HydraEngine* engine = HydraEngine::getInstance();
	engine->init();
	engine->setWTitle("Agar.exe, the free port of Agar.io");
	SDL_Renderer* renderer = engine->getRenderer();

	bool quit = false;
	while (!quit)
	{
		SDL_Event event;
		while (SDL_PollEvent(&event))
			if (event.type == SDL_QUIT)
				quit = true;

		Timer fps;
		fps.start();
		SDL_RenderClear(renderer);

		drawGrid(0, 0);
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
